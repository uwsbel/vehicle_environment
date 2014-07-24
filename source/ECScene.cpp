#include "ECScene.h"

namespace EnvironmentCore {

	ECScene::ECScene(Ogre::SceneManager* SceneManager, chrono::ChSystem* System) {
		m_pSceneManager = SceneManager;
		m_pChSystem = System;
	}

	ECScene::~ECScene() {

	}


	void ECScene::setAmbientLight(Ogre::ColourValue Color) {
		m_pSceneManager->setAmbientLight(Color);
	}

	void ECScene::setAmbientLight(float r, float g, float b) {
		m_pSceneManager->setAmbientLight(Ogre::ColourValue(r, g, b));
	}



	ECBody* ECScene::createBody() {
		ECBody* _ret = new ECBody(m_pSceneManager, m_pChSystem);
		return _ret;
	}
}