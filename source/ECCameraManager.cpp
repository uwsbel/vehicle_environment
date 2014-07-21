#include "ECCameraManager.h"

namespace EnvironmentCore {

	unsigned int ECCameraManager::g_CameraCount = 0;

	ECCameraManager::ECCameraManager(Ogre::SceneManager* SceneManager) {
		m_pSceneManager = SceneManager;
	}


	ECCameraManager::~ECCameraManager() {
		for (unsigned int i = 0; i < m_CameraList.size(); i++) {
			m_pSceneManager->getRootSceneNode()->removeAndDestroyChild(m_CameraList[i]->getName());
		}
	}

	ECCamera* ECCameraManager::createCamera(Ogre::String Name) {
		ECCamera* l_pCamera = m_pSceneManager->getRootSceneNode()->createChildSceneNode(Name);
		m_CameraList.push_back(l_pCamera);

		g_CameraCount = m_CameraList.size();

		return l_pCamera;
	}

	ECCamera* ECCameraManager::getCamera(unsigned int iterator) {
		return m_CameraList[iterator];
	}

	ECCamera* ECCameraManager::getCamera(Ogre::String Name) {
		for (unsigned int i = 0; i < m_CameraList.size(); i++) {
			if (m_CameraList[i]->getName() == Name) {
				return m_CameraList[i];
			}
		}
		return nullptr;
	}

	ECCamera* ECCameraManager::operator[] (unsigned int iterator) {
		return getCamera(iterator);
	}

	ECCamera* ECCameraManager::operator[] (Ogre::String Name) {
		return getCamera(Name);
	}

}