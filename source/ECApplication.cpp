#include "ECApplication.h"

namespace EnvironmentCore {

	EnvironmentCoreApplication::EnvironmentCoreApplication() {
		m_pRoot = new Ogre::Root("", "", "EnvironmentCore.log");

		//NOTE: Probably terrible practice. Do better
		{
			typedef std::vector<Ogre::String> __Strings_t__;

			__Strings_t__ l_Plugins;

			l_Plugins.push_back("RenderSystem_GL");
			l_Plugins.push_back("Plugin_ParticleFX");
			l_Plugins.push_back("Plugin_CgProgramManager");
			l_Plugins.push_back("Plugin_OctreeSceneManager");
			//l_tPlugins.push_back("Plugin_PCZSceneManager");
			//l_tPlugins.push_back("Plugin_OctreeZone");
			//l_tPlugins.push_back("Plugin_BSPSceneManager");

			//NOTE: Again, this is straight from a tutorial, so this could probably be done better
			{
				__Strings_t__::iterator l_Iterator = l_Plugins.begin();
				__Strings_t__::iterator l_IteratorEnd = l_Plugins.end();

				for (l_Iterator; l_Iterator != l_IteratorEnd; l_Iterator++) {
					Ogre::String& l_PluginName = (*l_Iterator);

					bool l_IsInDebugMode = OGRE_DEBUG_MODE;

					if (l_IsInDebugMode) {
						l_PluginName.append("_d");
					}
					m_pRoot->loadPlugin(l_PluginName);
				}
			}
		}

		//NOTE: Just rewrite this entire function

		{
			const Ogre::RenderSystemList& l_RenderSystemList = m_pRoot->getAvailableRenderers();
			if (l_RenderSystemList.size() == 0) {
				logMessage("Sorry, no rendersystem was found.");
			}

			Ogre::RenderSystem* l_RenderSystem = l_RenderSystemList[0];
			m_pRoot->setRenderSystem(l_RenderSystem);
		}

		{
			m_pRoot->initialise(false, "", "");

			m_pSceneManager = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "MainSceneManager");

			m_pCameraManager = new ECCameraManager(m_pSceneManager);
		}

	}

	EnvironmentCoreApplication::~EnvironmentCoreApplication() {
		m_pInputManager->destroyInputObject(m_pKeyboard);
		m_pInputManager->destroyInputObject(m_pMouse);
		OIS::InputManager::destroyInputSystem(m_pInputManager);

		delete m_pCameraManager;
		m_pRoot->destroySceneManager(m_pSceneManager);
		closeWindow();
	}

	int EnvironmentCoreApplication::startLoop(std::function<int()> _func) {
		int l_run = 0;
		while (l_run == 0) {

			m_pKeyboard->capture();
			m_pMouse->capture();

			l_run = _func();

			m_pRenderWindow->update(false);
			m_pRenderWindow->swapBuffers();

			m_pRoot->renderOneFrame();

			Ogre::WindowEventUtilities::messagePump();

			if (m_pRenderWindow->isClosed()) {
				l_run++;
			}
		}
		return l_run;
	}

	Ogre::RenderWindow* EnvironmentCoreApplication::createWindow(Ogre::String Title, uint32_t Width, uint32_t Height, uint8_t FSAA_Level, bool VSync, bool Fullscreen) {
		Ogre::NameValuePairList l_Params;
		l_Params["FSAA"] = "0";
		if (VSync) {
			l_Params["vsync"] = "true";
		}
		else {
			l_Params["vsync"] = "false";
		}
		m_pRenderWindow = m_pRoot->createRenderWindow(Title, Width, Height, Fullscreen, &l_Params);

		m_pCamera = m_pSceneManager->createCamera("MainCamera");

		m_pViewport = m_pRenderWindow->addViewport(m_pCamera);
		m_pViewport->setAutoUpdated(true);
		m_pViewport->setBackgroundColour(Ogre::ColourValue(0.5f, 0.5f, 0.5f, 1.0f));

		m_pCamera->setAspectRatio(((float)(m_pViewport->getActualWidth()))/((float)(m_pViewport->getActualHeight())));
		m_pCamera->setNearClipDistance(1.5f);

		m_pRenderWindow->setActive(true);
		m_pRenderWindow->setAutoUpdated(false);


		{
			size_t l_WindowHandle = 0;
			m_pRenderWindow->getCustomAttribute("WINDOW", &l_WindowHandle);

			std::string l_WindowHandleString = "";

			{
				std::ostringstream l_WindowHndStr;
				l_WindowHndStr << l_WindowHandle;
				l_WindowHandleString = l_WindowHndStr.str();
			}

			OIS::ParamList l_SpecialParameters;
			l_SpecialParameters.insert(std::make_pair(std::string("WINDOW"), l_WindowHandleString));

			m_pInputManager = OIS::InputManager::createInputSystem(l_SpecialParameters);
			m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputManager->createInputObject(OIS::OISKeyboard, false));
			m_pMouse = static_cast<OIS::Mouse*>(m_pInputManager->createInputObject(OIS::OISMouse, false));

			const OIS::MouseState &l_InfoSouris = m_pMouse->getMouseState();
			l_InfoSouris.width = m_pRenderWindow->getWidth();
			l_InfoSouris.height = m_pRenderWindow->getHeight();
		}


		m_pRoot->clearEventTimes();

		return m_pRenderWindow;
	}

	void EnvironmentCoreApplication::setCamera(ECCamera* Camera) {
		Camera->attachObject(m_pCamera);
	}

	void EnvironmentCoreApplication::setVSync(bool VSync) {
		isVSyncEnabled = VSync;
		m_pRenderWindow->setVSyncEnabled(isVSyncEnabled);
		m_pRenderWindow->setVSyncInterval(60);
	}

	void EnvironmentCoreApplication::closeWindow() {
		if (m_pRenderWindow) {
			if (!m_pRenderWindow->isClosed()) {
				m_pSceneManager->destroyAllCameras();
				m_pSceneManager->destroyAllManualObjects();
				m_pSceneManager->destroyAllEntities();

				m_pRenderWindow->removeAllViewports();
				m_pRenderWindow->destroy();
			}
			delete m_pRenderWindow;
		}
	}

	ECCameraManager* EnvironmentCoreApplication::getCameraManager() {
		return m_pCameraManager;
	}

	OIS::InputManager* EnvironmentCoreApplication::getInputManager() {
		return m_pInputManager;
	}

	OIS::Mouse* EnvironmentCoreApplication::getMouse() {
		return m_pMouse;
	}

	OIS::Keyboard* EnvironmentCoreApplication::getKeyboard() {
		return m_pKeyboard;
	}

	void EnvironmentCoreApplication::logMessage(const Ogre::String& Message, Ogre::LogMessageLevel lml, bool maskDebug) {
		Ogre::LogManager::getSingleton().logMessage(Message, lml, maskDebug);
	}
}