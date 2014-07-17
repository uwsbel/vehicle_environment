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
				Ogre::LogManager::getSingleton().logMessage("Sorry, no rendersystem was found.");
			}

			Ogre::RenderSystem* l_RenderSystem = l_RenderSystemList[0];
			m_pRoot->setRenderSystem(l_RenderSystem);
		}

		{
			m_pRoot->initialise(false, "", "");
		}

	}

	EnvironmentCoreApplication::~EnvironmentCoreApplication() {
		closeWindow();
		delete m_pRoot;
	}

	int EnvironmentCoreApplication::startLoop(int(*_func)()) {
		int l_run = 0;
		while (l_run == 0) {
			l_run = (*_func)();
		}
		return l_run;
	}

	Ogre::RenderWindow* EnvironmentCoreApplication::createWindow(Ogre::String Title, uint32_t Width, uint32_t Height, uint8_t FSAA_Level, bool VSync, bool Fullscreen) {
		Ogre::NameValuePairList l_Params;
		l_Params["FSAA"] = "0";//std::to_string(FSAA_Level);
		if (VSync) {
			l_Params["vsync"] = "true";
		}
		else {
			l_Params["vsync"] = "false";
		}
		m_pRenderWindow = m_pRoot->createRenderWindow(Title, Width, Height, Fullscreen, &l_Params);
		return m_pRenderWindow;
	}


	void EnvironmentCoreApplication::closeWindow() {
		if (m_pRenderWindow) {
			if (!m_pRenderWindow->isClosed()) {
				m_pRenderWindow->destroy();
			}
			delete m_pRenderWindow;
		}
	}
}