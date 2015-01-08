/*
Author: Charles Ricchio

Contains the prototype for a basic application. Manages things such as window creation, the camera and input.
*/

#pragma once

#include <OGRE\Ogre.h>

#include <physics\ChSystem.h>

#include <memory>
#include <exception>
#include <thread>
#include <chrono>
#include <vector>
#include <random>

#include "../ChOgre.h"

#include "../Input/ChOgre_SDLInputHandler.h"
#include "../Graphics/ChOgreCameraManager.h"
#include "../Graphics/ChOgreScene.h"
//#include "ECGUIManager.h"


namespace EnvironmentCore {

	class CHOGRE_DLL_TAG EnvironmentCoreApplication {
	public:

		EnvironmentCoreApplication();
		~EnvironmentCoreApplication();

		virtual int startLoop(std::function<int()> PerFrame);
		virtual Ogre::RenderWindow* createWindow(std::string Title, uint32_t Width, uint32_t Height, uint8_t FSAA_Level, bool VSync=false, bool Fullscreen=false);
		virtual void loadResourcePath(std::string Path, std::string Title="FileSystem");
		virtual void setCamera(ECCamera* Camera);
		virtual void setVSync(bool VSync);

		virtual void chronoThread();

		virtual void closeWindow();

		virtual ECCameraManager* getCameraManager();
		virtual ECScene* getScene();
		virtual EC_SDL_InputManager* getInputManager();
		//virtual ECGUIManager* getGUIManager();
		virtual Ogre::RenderWindow* getWindow();
		virtual Ogre::SceneManager* getSceneManager();
		virtual chrono::ChSystem* getChSystem();

		static void logMessage(const std::string& Message, Ogre::LogMessageLevel lml = Ogre::LML_NORMAL, bool maskDebug = false);

		double timestep_max;
		double timestep_min;
		double timestep;

		bool isRealTime;

		bool isRunning;

		bool WriteToFile;

	protected:

		Ogre::Root* m_pRoot;
		Ogre::RenderWindow* m_pRenderWindow;
		Ogre::SceneManager* m_pSceneManager;
		Ogre::Viewport* m_pViewport;
		Ogre::Camera* m_pCamera;

		chrono::ChSystem* m_pChSystem;

		std::thread m_ChronoThread;

		ECCameraManager* m_pCameraManager;
		ECScene* m_pScene;
		EC_SDL_InputManager* m_pInputManager;
		//ECGUIManager* m_pGUIManager;

		bool isVSyncEnabled;

	private:



	};

}