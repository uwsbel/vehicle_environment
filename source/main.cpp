#include "ECApplication.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char *argv[])
#endif
{
	try {
		EnvironmentCore::EnvironmentCoreApplication app;
		app.createWindow("Test", 800, 600, 0, false, false);

		EnvironmentCore::ECCamera* DebugCamera = app.getCameraManager()->createCamera("DebugCamera");

		DebugCamera->setPosition(Ogre::Vector3(0, 10, 500));
		DebugCamera->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);
		app.setCamera(DebugCamera);

		std::function<int()> Loop = [&]() {
			if (app.getKeyboard()->isKeyDown(OIS::KC_ESCAPE)) {
				return 0;
			}

			app.logMessage("Frame");

			return 0;
		};

		app.startLoop(Loop);
		app.logMessage("end of the program");
		Ogre::LogManager::getSingleton().logMessage("Haw");
	}
	catch (Ogre::Exception &e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured: " <<
		e.getFullDescription().c_str() << std::endl;
#endif
	}
	return 0;
}
