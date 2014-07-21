#pragma once

#include <OGRE\Ogre.h>
#include <OIS\OIS.h>

#include <memory>
#include <exception>
#include <thread>
#include <chrono>
#include <vector>
#include <random>

#include "ECCameraManager.h"


namespace EnvironmentCore {

	class EnvironmentCoreApplication {
	public:

		EnvironmentCoreApplication();
		~EnvironmentCoreApplication();

		virtual int startLoop(std::function<int()> PerFrame);
		virtual Ogre::RenderWindow* createWindow(Ogre::String Title, uint32_t Width, uint32_t Height, uint8_t FSAA_Level, bool VSync=false, bool Fullscreen=false);
		virtual void setCamera(ECCamera* Camera);
		virtual void setVSync(bool VSync);

		virtual void closeWindow();

		virtual ECCameraManager* getCameraManager();
		virtual OIS::InputManager* getInputManager();
		virtual OIS::Mouse* getMouse();
		virtual OIS::Keyboard* getKeyboard();

		static void logMessage(const Ogre::String& Message, Ogre::LogMessageLevel lml = Ogre::LML_NORMAL, bool maskDebug = false);

	protected:

		Ogre::Root* m_pRoot;
		Ogre::RenderWindow* m_pRenderWindow;
		Ogre::SceneManager* m_pSceneManager;
		Ogre::Viewport* m_pViewport;
		Ogre::Camera* m_pCamera;

		ECCameraManager* m_pCameraManager;

		OIS::InputManager* m_pInputManager;
		OIS::Mouse* m_pMouse;
		OIS::Keyboard* m_pKeyboard;

		bool isVSyncEnabled;

	private:



	};

}