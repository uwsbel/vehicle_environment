#include "ECScene.h"

namespace EnvironmentCore {

	ECScene::ECScene(Ogre::SceneManager* SceneManager) {
		m_pSceneManager = SceneManager;
	}

	ECScene::~ECScene() {

	}


	void ECScene::setAmbientLight(Ogre::ColourValue Color) {
		m_pSceneManager->setAmbientLight(Color);
	}

	void ECScene::setAmbientLight(float r, float g, float b) {
		m_pSceneManager->setAmbientLight(Ogre::ColourValue(r, g, b));
	}

}