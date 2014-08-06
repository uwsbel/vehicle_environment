#include "ECGUI.h"

namespace EnvironmentCore {

	ECGUI::ECGUI() {
		m_pOverlay = Ogre::OverlayManager::getSingleton().create("EnvironmentCoreGUI");
		setActive(true);
	}

	ECGUI::~ECGUI() {
		Ogre::OverlayManager::getSingleton().destroy(m_pOverlay);
	}

	void ECGUI::setActive(bool Active) {
		if (Active) {
			m_pOverlay->show();
		}
		else {
			m_pOverlay->hide();
		}
	}

	void ECGUI::createPanel(std::string Name) {
		Ogre::OverlayContainer* _panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", Name));
	}

}