#pragma once

#include <OGRE\Ogre.h>
#include <vector>

namespace EnvironmentCore {

	typedef Ogre::SceneNode ECCamera;

	class ECCameraManager {

	public:

		ECCameraManager(Ogre::SceneManager* SceneManager);
		~ECCameraManager();

		virtual ECCamera* createCamera(Ogre::String Name=( "Camera" + std::to_string( g_CameraCount ) ) );

		virtual ECCamera* getCamera(unsigned int iterator);

		virtual ECCamera* getCamera(Ogre::String Name);

		virtual ECCamera* operator[] (unsigned int iterator);

		virtual ECCamera* operator[] (Ogre::String Name);

	protected:

		Ogre::SceneManager* m_pSceneManager;

		std::vector<ECCamera*> m_CameraList;

		static unsigned int g_CameraCount;
	private:

	};

}