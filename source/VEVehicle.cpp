#include "VEVehicle.h"

namespace VehicleEnvironment {

	VEVehicle::VEVehicle() {
		throttle = 0;
		steer = 0;
	}

	VEVehicle::VEVehicle(EnvironmentCore::EnvironmentCoreApplication* App) {
		setApp(App);
		throttle = 0;
		steer = 0;
	}

	VEVehicle::~VEVehicle() {

	}

	void VEVehicle::setApp(EnvironmentCore::EnvironmentCoreApplication* App) {
		m_pApp = App;
	}

}