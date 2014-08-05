#include <random>
#include <chrono>
#include <cmath>

#include "ECApplication.h"
#include "VESuspensionDemo.h"

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
		app.createWindow("Test", 1280, 720, 0, false, false);

		EnvironmentCore::ECCamera* DebugCamera = app.getCameraManager()->createCamera("DebugCamera");
		
		DebugCamera->orient(50.0f, 20.0f, -50.0f, 0.0f, 0.0f, 0.0f);

		app.setCamera(DebugCamera);

		app.timestep_max = 0.01;
		app.isRealTime = true;

		std::random_device l_rand;

		

		VehicleEnvironment::VESuspensionDemo car;
		car.setApp(&app);
		car.build(chrono::ChVector<>(0, 0, 0));



		EnvironmentCore::ECBody& Epsilon = app.getScene()->spawnSphere("Spheere", 1, chrono::ChVector<>(10, 10, 20), 4);
		Epsilon->SetInertiaXX(chrono::ChVector<>(
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0)));

		EnvironmentCore::ECBody& Epsilon1 = app.getScene()->spawnSphere("Spheere1", 1, chrono::ChVector<>(30, 10, 20), 4);
		Epsilon1->SetInertiaXX(chrono::ChVector<>(
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0)));

		EnvironmentCore::ECBody& Epsilon2 = app.getScene()->spawnSphere("Spheere2", 1, chrono::ChVector<>(0, 10, 20), 4);
		Epsilon2->SetInertiaXX(chrono::ChVector<>(
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0)));

		/*EnvironmentCore::ECBody& Epsilon3 = app.getScene()->spawnSphere("Spheere3", 1, chrono::ChVector<>(50, 10, 50), 4);
		Epsilon2->SetInertiaXX(chrono::ChVector<>(
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0)));

		EnvironmentCore::ECBody& Epsilon4 = app.getScene()->spawnBox("Spheere4", 10, chrono::ChVector<>(-20, 10, -70), chrono::ChVector<>(4, 4, 4));
		Epsilon2->SetInertiaXX(chrono::ChVector<>(
			((1.0 / 12.0)*Epsilon->GetMass() * (16.0 + 16.0)),
			((1.0 / 12.0)*Epsilon->GetMass() * (16.0 + 16.0)),
			((1.0 / 12.0)*Epsilon->GetMass() * (16.0 + 16.0))));*/

		EnvironmentCore::ECBody& Gamma = app.getScene()->spawnBox("Platform", 1.0, chrono::ChVector<>(0, -10, 0), chrono::ChVector<>(500, 0.5, 500), chrono::ChQuaternion<>(1, 0, 0, 0), true);
		Gamma->SetFriction(20);
		EnvironmentCore::ECBody& Gamma1 = app.getScene()->spawnBox("Platform1", 1.0, chrono::ChVector<>(1000, -10, 0), chrono::ChVector<>(500, 0.5, 500), chrono::ChQuaternion<>(1, 0, 0, 0), true);
		Gamma1->SetFriction(20);
		EnvironmentCore::ECBody& Gamma2 = app.getScene()->spawnBox("Platform2", 1.0, chrono::ChVector<>(-1000, -10, 0), chrono::ChVector<>(500, 0.5, 500), chrono::ChQuaternion<>(1, 0, 0, 0), true);
		Gamma2->SetFriction(20);
		EnvironmentCore::ECBody& Gamma3 = app.getScene()->spawnBox("Platform3", 1.0, chrono::ChVector<>(0, -10, 1000), chrono::ChVector<>(500, 0.5, 500), chrono::ChQuaternion<>(1, 0, 0, 0), true);
		Gamma3->SetFriction(20);
		EnvironmentCore::ECBody& Gamma4 = app.getScene()->spawnBox("Platform4", 1.0, chrono::ChVector<>(0, -10, -1000), chrono::ChVector<>(500, 0.5, 500), chrono::ChQuaternion<>(1, 0, 0, 0), true);
		Gamma4->SetFriction(20);

		EnvironmentCore::ECBody& Building = app.getScene()->spawnBox("Building1", 50000, chrono::ChVector<>(0, 490, 100), chrono::ChVector<>(20, 500, 20), chrono::ChQuaternion<>(1, 0, 0, 0), true);

		/*EnvironmentCore::ECBody& Theta = app.getScene()->spawnEllipsoid("Theta", 1.0, chrono::ChVector<>(0, 30, 0), chrono::ChVector<>(2, 5, 2));
		Theta->SetInertiaXX(chrono::ChVector<>(
			((1.0 / 5.0)*Theta->GetMass() * (std::pow(1, 2) + std::pow(1, 2.5))),
			((1.0 / 5.0)*Theta->GetMass() * (std::pow(1, 2) + std::pow(1, 2.5))),
			((1.0 / 5.0)*Theta->GetMass() * (std::pow(1, 2) + std::pow(1, 2)))));

		EnvironmentCore::ECBody& Alpha = app.getScene()->spawnBox("Boox", 100, chrono::ChVector<>(0, 100, 0), chrono::ChVector<>(2, 2, 2));
		Alpha->SetInertiaXX(chrono::ChVector<>( 
			((1.0 / 12.0)*Alpha->GetMass() * 8.0),
			((1.0 / 12.0)*Alpha->GetMass() * 8.0),
			((1.0 / 12.0)*Alpha->GetMass() * 8.0) ));

		EnvironmentCore::ECBody& Omega = app.getScene()->spawnCylinder("Coone", 3, chrono::ChVector<>(0, 200, 0), chrono::ChVector<>(2, 5, 2));
		Omega->SetInertiaXX(chrono::ChVector<>(
			((1.0 / 12.0)*Omega->GetMass() * 37.0),
			((1.0 / 12.0)*Omega->GetMass() * 37.0),
			((1.0 / 2.0)*Omega->GetMass() * 4.0)));

		for (int i = 0; i < 200; i++) {
			EnvironmentCore::ECBody& Beta = app.getScene()->spawnSphere("", 1, chrono::ChVector<>(((double)l_rand() / (double)l_rand.max()) * 10, 20 + (i * 5), ((double)l_rand() / (double)l_rand.max()) * 10), 1);
			Beta->SetInertiaXX(chrono::ChVector<>(
				((2.5 / 5.0)*Epsilon->GetMass() * 1.0),
				((2.0 / 5.0)*Epsilon->GetMass() * 1.0),
				((2.0 / 5.0)*Epsilon->GetMass() * 1.0)));
		}*/

		EnvironmentCore::ECBody& Mesh_Test = app.getScene()->spawnMesh("Mesh", 1.0, chrono::ChVector<>(0, 10, 0), chrono::ChQuaternion<>(1, 0, 0, 0), "ninja.mesh", true);


		EnvironmentCore::ECLight& yeh = app.getScene()->createLight("Swag");
		yeh.setType(EnvironmentCore::ECLightTypes::LT_POINT);
		yeh.setPosition(0.0f, 100.0f, 0.0f);
		yeh.setDiffuseColour(1.0f, 1.0f, 0.0f);
		yeh.setSpecularColour(1.0f, 1.0f, 0.0f);
		yeh.setDirection(0.0f, 0.0f, 0.0f);
		yeh.setPowerScale(400.0f);

		EnvironmentCore::ECLight& yeh2 = app.getScene()->createLight("Que");
		yeh2.setType(EnvironmentCore::ECLightTypes::LT_POINT);
		yeh2.setPosition(500.0f, 500.0f, 500.0f);
		yeh2.setDiffuseColour(1.0f, 0.0f, 1.0f);
		yeh2.setSpecularColour(1.0f, 0.0f, 1.0f);
		yeh2.setDirection(0.0f, 0.0f, 0.0f);
		yeh2.setPowerScale(400.0f);

		EnvironmentCore::ECLight& yeh3 = app.getScene()->createLight("Holo");
		yeh3.setType(EnvironmentCore::ECLightTypes::LT_POINT);
		yeh3.setPosition(500.0f, 800.0f, -800.0f);
		yeh3.setDiffuseColour(0.0f, 1.0f, 1.0f);
		yeh3.setSpecularColour(0.0f, 1.0f, 1.0f);
		yeh3.setDirection(0.0f, 0.0f, 0.0f);
		yeh3.setPowerScale(400.0f);

		EnvironmentCore::ECLight& follow = app.getScene()->createLight("Follow");
		follow.setType(EnvironmentCore::ECLightTypes::LT_POINT);
		follow.setDiffuseColour(1.0f, 1.0f, 1.0f);
		follow.setSpecularColour(1.0f, 1.0f, 1.0f);


		chrono::ChVector<> direction = chrono::ChVector<>(0, 0, 5);
		chrono::ChQuaternion<> dirRot = car.getRot();
		dirRot.Normalize();
		direction = dirRot.Rotate(chrono::ChVector<>(0, 0, 5));

		chrono::ChVector<> camera_pos;
		chrono::ChVector<> camera_tpos;
		chrono::ChVector<> look_at;
		chrono::ChVector<> camera_vel;

		//app.getScene()->setAmbientLight(1.0f, 1.0f, 1.0f);

		std::chrono::high_resolution_clock l_time;
		auto l_start = l_time.now();

		double throttle = 0; // actual value 0...1 of gas throttle.
		double conic_tau = 10; // the transmission ratio of the conic gears at the rear axle
		double gear_tau = 0.5; // the actual tau of the gear
		double max_motor_torque = 30; // the max torque of the motor [Nm];
		double max_motor_speed = 100;	 // the max rotation speed of the motor [rads/s]

		bool db = true;
		bool db2 = true;

		unsigned int deleteSpheres = 0;

		app.getChSystem()->SetIterLCPmaxItersSpeed(20);

		std::function<int()> Loop = [&]() {

			if ((app.getInputManager()->getMouseState().right.down || app.getInputManager()->getControllerState().b.down) && db) {
				EnvironmentCore::ECBody& Alpha = app.getScene()->spawnSphere("Boox", 50, chrono::ChVector<>(car.getPos().x, car.getPos().y + 3, car.getPos().z), 0.1);
				Alpha->SetInertiaXX(chrono::ChVector<>(
					((2.0 / 5.0)*Alpha->GetMass() * 0.3 * 0.3),
					((2.0 / 5.0)*Alpha->GetMass() * 0.3 * 0.3),
					((2.0 / 5.0)*Alpha->GetMass() * 0.3 * 0.3)));

				auto dir = car.getRot().Rotate(chrono::ChVector<>(0, 0, 1));

				Alpha->SetPos_dt(dir * 125);

				db = false;
			}

			if (!app.getInputManager()->getMouseState().right.down && !app.getInputManager()->getControllerState().b.down) {
				db = true;
			}

			deleteSpheres++;

			if (deleteSpheres > 500) {
				app.getScene()->removeBody("Boox");
				deleteSpheres = 0;
			}


			if (app.getInputManager()->getControllerState().rbumper.down && db2) {
				app.getInputManager()->runHapticRumble(1.0f, 1);
				db2 = false;
			}
			if (!app.getInputManager()->getControllerState().rbumper.down) {
				db2 = true;
			}

			double steer = 0.05*((double)((double)INT_MAX * -1.0 * app.getInputManager()->getControllerState().lstickx.value));

			if (steer > 0.1) {
				steer = 0.1;
			}
			else if (steer < -0.1) {
				steer = -0.1;
			}

			car.steer = steer;

			if (app.getInputManager()->getKeyState(SDL_SCANCODE_W).down || (app.getInputManager()->getControllerState().rtrigger.value > 0.50) || (app.getInputManager()->getControllerState().ltrigger.value > 0.50)) {
				throttle = 40 * (app.getInputManager()->getControllerState().rtrigger.value - app.getInputManager()->getControllerState().ltrigger.value);
			}
			else {
				throttle = 0;
			}

			if (app.getInputManager()->getKeyState(SDL_SCANCODE_ESCAPE).down || app.getInputManager()->getControllerState().back.down) {
				return 1;
			}

			car.throttle = throttle;

			car.update();


			follow.setDiffuseColour(1.0f, 1.0f, 1.0f);
			follow.setSpecularColour(1.0f, 1.0f, 1.0f);


			dirRot = car.getRot();
			dirRot.Normalize();
			direction = dirRot.Rotate(chrono::ChVector<>(0, 0, -20));

			look_at = car.getPos();
			camera_tpos = (car.getPos() + direction);

			auto camera_dpos = camera_tpos - camera_pos;

			auto fSpring = (camera_dpos * 200) - (camera_vel * 200);

			auto cam_accel = fSpring / 5;

			camera_vel = camera_vel + cam_accel * app.timestep;

			camera_pos = camera_pos + camera_vel * app.timestep + 0.5 * cam_accel * app.timestep * app.timestep;
			

			DebugCamera->orient(camera_pos.x, camera_pos.y + 10, camera_pos.z, look_at.x, look_at.y+6, look_at.z);
			app.setCamera(DebugCamera);

			follow.setPosition(car.getPos().x, car.getPos().y + 10, car.getPos().z + 14);


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
