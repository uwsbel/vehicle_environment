#include <ChOgre/Core/ChOgreApplication.h>

using namespace ChOgre;

int main(int argc, char** args) {
	ChOgreApplication app;
	
	app.createWindow("Test", 1280, 720, 0, false, false);

	ChOgreCamera* DebugCamera = app.getCameraManager()->createCamera("DebugCamera");

	DebugCamera->orient(50.0f, 20.0f, -50.0f, 0.0f, 0.0f, 0.0f);

	app.setCamera(DebugCamera);

	app.timestep_max = 0.01;
	app.isRealTime = false;

	std::random_device l_rand;

	app.getScene()->setSkyBox("sky");

	ChOgreBody& Epsilon = app.getScene()->spawnSphere("Spheere", 1, chrono::ChVector<>(0, 20, 0), 3, false);
	Epsilon->SetInertiaXX(chrono::ChVector<>(
		((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
		((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
		((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0)));

	ChOgreBody& Alpha = app.getScene()->spawnBox("Boox", 1, chrono::ChVector<>(0, 0, 0), chrono::ChVector<>(10, 0.5, 10), chrono::ChQuaternion<>(), true);

	ChOgreLight& yeh = app.getScene()->createLight("Swag");
	yeh.setType(ChOgreLightTypes::LT_POINT);
	yeh.setPosition(0.0f, 100.0f, 0.0f);
	yeh.setDiffuseColour(1.0f, 1.0f, 1.0f);
	yeh.setSpecularColour(1.0f, 1.0f, 1.0f);
	yeh.setDirection(0.0f, 0.0f, 0.0f);
	yeh.setPowerScale(400.0f);

	bool spacebar_state = false;


	std::function<int()> Loop = [&]() {
		spacebar_state = app.getInputManager()->getKeyState(SDLK_SPACE).down;

		if (spacebar_state == true) {
			Epsilon->SetPos(chrono::ChVector<>(0, 20, 0));
		}

		return 0;
	};

	app.startLoop(Loop);

	return 0;
}