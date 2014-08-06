/*
Author: Charles Ricchio

This is the basic vehicle class, which all vehicles should inherit from
*/

#pragma once

#include "ECApplication.h"
#include "ECBody.h"

namespace VehicleEnvironment {

	class VEVehicle {

	public:

		VEVehicle();
		VEVehicle(EnvironmentCore::EnvironmentCoreApplication* App);
		~VEVehicle();

		virtual void setApp(EnvironmentCore::EnvironmentCoreApplication* App);
		virtual void build(chrono::ChVector<>& Pos) =0;
		virtual void update() = 0;
		virtual void reset(chrono::ChVector<>& Pos) =0;

		double throttle;
		double steer;

	protected:

		EnvironmentCore::EnvironmentCoreApplication* m_pApp;

	private:



	};

}