#include <ChOgre/Core/ChOgreApplication.h>
#include <cmath>

using namespace ChOgre;

int main(int argc, char** args) {
	ChOgreApplication app;
	
	app.createWindow("Test", 1280, 720, 0, false, false);

	ChOgreCamera* DebugCamera = app.getCameraManager()->createCamera("DebugCamera");

	DebugCamera->setPosition(50.0f, 20.0f, -50.0f);
	DebugCamera->lookAt(0.0f, 0.0f, 0.0f);
	app.getCameraManager()->makeActive(DebugCamera);

	app.timestep_max = 0.01;
	app.isRealTime = false;

	std::random_device l_rand;


	ChOgreBodySharedPtr Epsilon = app.getScene()->spawnSphere("Spheere", 1, chrono::ChVector<>(0, 5, 0), 3, false);
	Epsilon->getChBody()->SetInertiaXX(chrono::ChVector<>(
		((2.0 / 5.0)*Epsilon->getChBody()->GetMass() * 4.0 * 4.0),
		((2.0 / 5.0)*Epsilon->getChBody()->GetMass() * 4.0 * 4.0),
		((2.0 / 5.0)*Epsilon->getChBody()->GetMass() * 4.0 * 4.0)));

	ChOgreBodySharedPtr Alpha = app.getScene()->spawnBox("Boox", 1, chrono::ChVector<>(0, 0, 0), chrono::ChVector<>(50, 0.5, 50), chrono::ChQuaternion<>(), true);

	ChOgreLight& yeh = app.getScene()->createLight("Swag");
	yeh.setType(ChOgreLightTypes::LT_POINT);
	yeh.setPosition(0.0f, 100.0f, 0.0f);
	yeh.setDiffuseColour(1.0f, 1.0f, 1.0f);
	yeh.setSpecularColour(1.0f, 1.0f, 1.0f);
	yeh.setDirection(0.0f, 0.0f, 0.0f);
	yeh.setPowerScale(400.0f);

	app.getScene()->setSkyBox("sky");

	double throttle = 0;
	double steer = 0;
	typedef double angle;

	angle direction = 0;

	chrono::ChVector<> mod;
	const double deg_to_rad = std::_Pi / 180.0;

	ChOgreKeyboardCallback k;
	k.call = [&DebugCamera](scancode_t s, keycode_t k, const ChOgreKeyState& ks) -> void {
		if (k = SDLK_SPACE) {
			DebugCamera->orient(30, 30);
		} 
	};

	app.getInputManager()->addCallback(k);

	ChOgreApplication::ChOgreLoopCallFunc Loop = ChOgreFunc(void) {

		steer = app.getInputManager()->getWheelState().wheel.value * 0.25;
		throttle = app.getInputManager()->getWheelState().accelerator.value;
		

		direction += steer;
		if (direction > 360) {
			direction = 0;
		}
		else if (direction < 0) {
			direction = 360;
		}

		mod.x = std::cos(direction * deg_to_rad);
		mod.z = std::sin(direction * deg_to_rad);

		DebugCamera->setPosition(Epsilon->getChBody()->GetPos().x - (mod.x * 40), 20, Epsilon->getChBody()->GetPos().z - (mod.z * 40));
		DebugCamera->lookAt(Epsilon->getChBody()->GetPos().x, Epsilon->getChBody()->GetPos().y, Epsilon->getChBody()->GetPos().z);

		mod *= throttle;

		Epsilon->getChBody()->SetPos_dt(mod);
		return 0;
	};

	app.startLoop(Loop);

	return 0;
}