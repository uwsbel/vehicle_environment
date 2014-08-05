#pragma once

#include "VEVehicle.h"

namespace VehicleEnvironment {

	class VESuspensionDemo : public VEVehicle {

	public:

		VESuspensionDemo();
		VESuspensionDemo(EnvironmentCore::EnvironmentCoreApplication* App);
		~VESuspensionDemo();

		virtual void build(chrono::ChVector<>& Pos);
		virtual void update();
		virtual void reset(chrono::ChVector<>& Pos);

		virtual chrono::ChVector<> getPos();
		virtual chrono::ChQuaternion<> getRot();

		double conic_tau; // the transmission ratio of the conic gears at the rear axle
		double gear_tau; // the actual tau of the gear
		double max_motor_torque; // the max torque of the motor [Nm];
		double max_motor_speed;	 // the max rotation speed of the motor [rads/s]

	protected:

		EnvironmentCore::ECBody* truss;

		EnvironmentCore::ECBody* spindleRF;
		EnvironmentCore::ECBody* wheelRF;

		chrono::ChSharedPtr<chrono::ChLinkLockRevolute> link_revoluteRF;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRFU1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRFU2;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRFL1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRFL2;
		chrono::ChSharedPtr<chrono::ChLinkSpring>   link_springRF;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRSTEER;

		EnvironmentCore::ECBody* spindleLF;
		EnvironmentCore::ECBody* wheelLF;

		chrono::ChSharedPtr<chrono::ChLinkLockRevolute> link_revoluteLF;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLFU1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLFU2;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLFL1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLFL2;
		chrono::ChSharedPtr<chrono::ChLinkSpring>   link_springLF;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLSTEER;

		EnvironmentCore::ECBody* spindleRB;
		EnvironmentCore::ECBody* wheelRB;

		chrono::ChSharedPtr<chrono::ChLinkLockRevolute> link_revoluteRB;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRBU1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRBU2;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRBL1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRBL2;
		chrono::ChSharedPtr<chrono::ChLinkSpring>   link_springRB;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRBlat;
		chrono::ChSharedPtr<chrono::ChLinkEngine>   link_engineL;

		EnvironmentCore::ECBody* spindleLB;
		EnvironmentCore::ECBody* wheelLB;

		chrono::ChSharedPtr<chrono::ChLinkLockRevolute> link_revoluteLB;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLBU1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLBU2;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLBL1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLBL2;
		chrono::ChSharedPtr<chrono::ChLinkSpring>   link_springLB;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLBlat;
		chrono::ChSharedPtr<chrono::ChLinkEngine>   link_engineR;

	private:



	};

}