#include <random>
#include <chrono>

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
		EnvironmentCore::ECCamera* DebugCamera2 = app.getCameraManager()->createCamera("DebugCamera2");

		DebugCamera->orient(0.0f, 20.0f, 500.0f, 0.0f, 0.0f, 0.0f);
		DebugCamera2->orient(0.0f, 20.0f, -500.0f, 0.0f, 0.0f, 0.0f);

		app.setCamera(DebugCamera);

		std::random_device l_rand;

		Ogre::Light* yeh = app.getSceneManager()->createLight("Swag");
		yeh->setType(Ogre::Light::LT_POINT);
		yeh->setPosition(0.0f, 10.0f, 0.0f);
		yeh->setDiffuseColour(1.0f, 1.0f, 0.0f);
		yeh->setSpecularColour(1.0f, 1.0f, 0.0f);

		Ogre::Entity* sphere = app.getSceneManager()->createEntity("Sphere", "ninja.mesh");
		Ogre::SceneNode* sphereNode = app.getSceneManager()->getRootSceneNode()->createChildSceneNode("SphereNode");
		sphereNode->attachObject(sphere);

		std::chrono::system_clock cl;
		auto t1 = cl.now();

		std::function<int()> Loop = [&]() {
			
			auto t2 = cl.now() - t1;
			auto td = std::chrono::seconds(10);

			if (t2 > td) {
				app.setCamera(DebugCamera2);
			}

			float _l_r = (float)l_rand() / (float)l_rand.max();
			float _l_g = (float)l_rand() / (float)l_rand.max();
			float _l_b = (float)l_rand() / (float)l_rand.max();

			app.logMessage("r: " + std::to_string(_l_r) + " g: " + std::to_string(_l_g) + " b: " + std::to_string(_l_b));

			//app.getScene()->setAmbientLight(_l_r, _l_g, _l_b);

			app.logMessage("Frame");

			return 0;
		};

		

		app.startLoop(Loop);
		app.logMessage("end of the program");
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
