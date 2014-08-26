#pragma once

#include "VEVehicle.h"

namespace VehicleEnvironment {

	class VEHumvee : public VEVehicle {

	public:

		VEHumvee();
		VEHumvee(EnvironmentCore::EnvironmentCoreApplication* App);
		~VEHumvee();

		virtual void build(chrono::ChVector<>& Pos);
		virtual void update();
		virtual void reset(chrono::ChVector<>& Pos);

		virtual void shift(uint8_t gear);
		virtual void brake();

		virtual chrono::ChBody* getBody();
		virtual chrono::ChVector<> getPos();
		virtual chrono::ChQuaternion<> getRot();

	protected:

		EnvironmentCore::ECBody* chasis;

	private:



	};

}