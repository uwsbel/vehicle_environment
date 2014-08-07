#include "ECGUIManager.h"

namespace EnvironmentCore {

	ECGUIManager::ECGUIManager(Ogre::SceneManager* SceneManager, EC_SDL_InputManager* InputManager) {
		m_pInputManager = InputManager;
		m_pSceneManager = SceneManager;
		m_pOverlaySystem = new Ogre::OverlaySystem();
		SceneManager->addRenderQueueListener(m_pOverlaySystem);
		m_pOverlay = Ogre::OverlayManager::getSingleton().create("EnvironmentCoreGUI");
		setActive(true);
	}

	ECGUIManager::~ECGUIManager() {
		Ogre::OverlayManager::getSingleton().destroy(m_pOverlay);
		m_pSceneManager->removeRenderQueueListener(m_pOverlaySystem);
	}

	void ECGUIManager::setActive(bool Active) {
		if (Active) {
			m_pOverlay->show();
		}
		else {
			m_pOverlay->hide();
		}
	}

	void ECGUIManager::createPanel(std::string Name) {
		Ogre::OverlayContainer* _panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", Name));
		_panel->initialise();
		_panel->setPosition(0.0, 0.0);
		_panel->setDimensions(0.1, 0.1);
		//_panel->setColour(Ogre::ColourValue(1.0, 0.2, 0.0));
		_panel->setMaterialName("BaseWhite");
		m_pOverlay->add2D(_panel);
		setActive(true);
	}

	template <typename t>
	t* ECGUIManager::getElement(std::string Name) {
		for (unsigned int i = 0; i < m_ElementList.size(); i++) {
			if (m_ElementList[i]->getName() == Name) {
				return (t*)m_ElementList[i];
			}
		}
	}

}