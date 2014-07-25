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
		

		DebugCamera->orient(0.0f, 1.0f, -15.0f, 0.0f, 0.0f, 0.0f);
		

		app.setCamera(DebugCamera);



		EnvironmentCore::ECBody& Epsilon = app.getScene()->createBody();
		EnvironmentCore::ECBody& Gamma = app.getScene()->createBody();

		Epsilon->GetCollisionModel()->ClearModel();
		Epsilon->GetCollisionModel()->AddSphere(1, chrono::ChVector<>(0, 0, 0));

		chrono::ChSharedPtr<chrono::ChSphereShape> sphere(new chrono::ChSphereShape);
		sphere->GetSphereGeometry().rad = 1;
		sphere->Pos = chrono::ChVector<>(0, 0, 0);
		sphere->Rot = chrono::ChQuaternion<>(1, 0, 0, 0);

		Epsilon->GetCollisionModel()->BuildModel();

		Epsilon->SetCollide(true);
		Epsilon->SetBodyFixed(false);

		Epsilon->GetAssets().push_back(sphere);
		Epsilon->SetPos(chrono::ChVector<>(0, 20, 0));
		Epsilon.refresh();



		Gamma->GetCollisionModel()->ClearModel();
		Gamma->GetCollisionModel()->AddBox(20, 0.1, 20, chrono::ChVector<>(0, 0, 0));

		chrono::ChSharedPtr<chrono::ChBoxShape> box(new chrono::ChBoxShape);
		box->GetBoxGeometry().Size = chrono::ChVector<>(20, 0.1, 20);
		box->Pos = chrono::ChVector<>(0, 0, 0);
		box->Rot = chrono::ChQuaternion<>(1, 0, 0, 0);

		Gamma->GetCollisionModel()->BuildModel();

		Gamma->SetCollide(true);
		Gamma->SetBodyFixed(true);

		Gamma->GetAssets().push_back(box);
		Gamma->SetPos(chrono::ChVector<>(0, 0, 0));
		Gamma.refresh();

		

		std::random_device l_rand;

		Ogre::Light* yeh = app.getSceneManager()->createLight("Swag");
		yeh->setType(Ogre::Light::LT_POINT);
		yeh->setPosition(0.0f, 10.0f, 0.0f);
		yeh->setDiffuseColour(1.0f, 1.0f, 0.0f);
		yeh->setSpecularColour(1.0f, 1.0f, 0.0f);

		Ogre::Light* yeh2 = app.getSceneManager()->createLight("Que");
		yeh2->setType(Ogre::Light::LT_POINT);
		yeh2->setPosition(50.0f, 50.0f, 50.0f);
		yeh2->setDiffuseColour(1.0f, 0.0f, 1.0f);
		yeh2->setSpecularColour(1.0f, 0.0f, 1.0f);

		Ogre::Light* yeh3 = app.getSceneManager()->createLight("Holo");
		yeh3->setType(Ogre::Light::LT_POINT);
		yeh3->setPosition(50.0f, 80.0f, -80.0f);
		yeh3->setDiffuseColour(0.0f, 1.0f, 1.0f);
		yeh3->setSpecularColour(0.0f, 1.0f, 1.0f);


		//app.getScene()->setAmbientLight(1.0f, 1.0f, 1.0f);

		std::function<int()> Loop = [&]() {

			Epsilon.update();
			Gamma.update();

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
