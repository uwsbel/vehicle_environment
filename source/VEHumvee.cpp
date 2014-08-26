#include "VEHumvee.h"

namespace VehicleEnvironment {

	VEHumvee::VEHumvee() {

	}

	VEHumvee::VEHumvee(EnvironmentCore::EnvironmentCoreApplication* App) : VEVehicle(App) {

	}

	VEHumvee::~VEHumvee() {

	}

	void VEHumvee::build(chrono::ChVector<>& Pos) {

	}

	void VEHumvee::update() {

	}

	void VEHumvee::reset(chrono::ChVector<>& Pos) {

	}

	void VEHumvee::shift(uint8_t Gear) {

	}

	void VEHumvee::brake() {

	}

	chrono::ChBody* VEHumvee::getBody() {
		return chasis->getChBody().get_ptr();
	}

	chrono::ChVector<> VEHumvee::getPos() {
		return chasis->getChBody()->GetPos();
	}

	chrono::ChQuaternion<> VEHumvee::getRot() {
		return chasis->getChBody()->GetRot();
	}

}