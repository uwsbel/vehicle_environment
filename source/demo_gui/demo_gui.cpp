#include <ChOgre/Core/ChOgreApplication.h>
#include <cmath>
#include <ChOgre/GUI/ChOgreGUIButton.h>

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

	auto button = app.getGUIManager()->createWidget<ChOgre::ChOgreGUIButton>(ChFloat3(0, 0, 0), ChFloat3(100, 20, 0));
	button->setColor(1.f, 1.f, 1.f);
	button->setFont("Arial");
	button->setText("Button");

	ChOgreBody& Epsilon = app.getScene()->spawnSphere("Spheere", 1, chrono::ChVector<>(0, 5, 0), 3, false);
	Epsilon->SetInertiaXX(chrono::ChVector<>(
		((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
		((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
		((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0)));

	ChOgreBody& Alpha = app.getScene()->spawnBox("Boox", 1, chrono::ChVector<>(0, 0, 0), chrono::ChVector<>(50, 0.5, 50), chrono::ChQuaternion<>(), true);

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

	bool mouse = false;

	angle direction = 0;

	chrono::ChVector<> mod;
	const double deg_to_rad = std::_Pi / 180.0;

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


		DebugCamera->x = Epsilon->GetPos().x - (mod.x * 40);
		DebugCamera->y = 20;
		DebugCamera->z = Epsilon->GetPos().z - (mod.z * 40);
		DebugCamera->wx = Epsilon->GetPos().x;
		DebugCamera->wy = Epsilon->GetPos().y;
		DebugCamera->wz = Epsilon->GetPos().z;

		app.setCamera(DebugCamera);

		mod *= throttle;

		Epsilon->SetPos_dt(mod);
		return 0;
	};

	app.startLoop(Loop);

	return 0;
}