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
		

		DebugCamera->orient(0.0f, 80.0f, 600.0f, 0.0f, 0.0f, 0.0f);
		

		app.setCamera(DebugCamera);



		EnvironmentCore::ECBody* Epsilon = app.getScene()->createBody();
		EnvironmentCore::ECBody* Gamma = app.getScene()->createBody();

		
		Epsilon->getChBody()->GetCollisionModel()->ClearModel();
		Epsilon->getChBody()->GetCollisionModel()->AddSphere(2, chrono::ChVector<>(0, 0, 0));

		chrono::ChSharedPtr<chrono::ChSphereShape> sphere(new chrono::ChSphereShape);
		sphere->GetSphereGeometry().rad = 2;
		sphere->Pos = chrono::ChVector<>(0, 0, 0);
		sphere->Rot = chrono::ChQuaternion<>(1, 0, 0, 0);

		Epsilon->getChBody()->GetCollisionModel()->BuildModel();

		Epsilon->getChBody()->SetCollide(true);
		Epsilon->getChBody()->SetBodyFixed(false);

		Epsilon->getChBody()->GetAssets().push_back(sphere);
		Epsilon->getChBody()->SetPos(chrono::ChVector<>(10, 20, 0));
		Epsilon->refresh();



		Gamma->getChBody()->GetCollisionModel()->ClearModel();
		Gamma->getChBody()->GetCollisionModel()->AddBox(20, 1, 20, chrono::ChVector<>(0, 0, 0));

		chrono::ChSharedPtr<chrono::ChBoxShape> box(new chrono::ChBoxShape);
		box->GetBoxGeometry().Size = chrono::ChVector<>(20, 1, 20);
		box->Pos = chrono::ChVector<>(0, 0, 0);
		box->Rot = chrono::ChQuaternion<>(1, 0, 0, 0);

		Gamma->getChBody()->GetCollisionModel()->BuildModel();

		Gamma->getChBody()->SetCollide(true);
		Gamma->getChBody()->SetBodyFixed(true);

		Gamma->getChBody()->GetAssets().push_back(box);
		Gamma->getChBody()->SetPos(chrono::ChVector<>(10, -20, 0));
		Gamma->refresh();

		

		std::random_device l_rand;

		Ogre::Light* yeh = app.getSceneManager()->createLight("Swag");
		yeh->setType(Ogre::Light::LT_POINT);
		yeh->setPosition(0.0f, 10.0f, 0.0f);
		yeh->setDiffuseColour(1.0f, 1.0f, 0.0f);
		yeh->setSpecularColour(1.0f, 1.0f, 0.0f);


		app.getScene()->setAmbientLight(1.0f, 1.0f, 1.0f);

		std::function<int()> Loop = [&]() {

			Epsilon->update();
			Gamma->update();

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
