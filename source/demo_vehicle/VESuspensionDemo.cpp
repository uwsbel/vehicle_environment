#include "VESuspensionDemo.h"

namespace VehicleEnvironment {

	VESuspensionDemo::VESuspensionDemo() {

		truss = nullptr;
		spindleRF = nullptr;
		wheelRF = nullptr;
		spindleLF = nullptr;
		wheelLF = nullptr;
		spindleRB = nullptr;
		wheelRB = nullptr;
		spindleLB = nullptr;
		wheelLB = nullptr;

		//Right front wheel

		link_revoluteRF = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_distRFU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRFU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRFL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRFL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_springRF = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_distRSTEER = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);

		//Left front wheel

		link_revoluteLF = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_distLFU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLFU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLFL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLFL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_springLF = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_distLSTEER = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		
		//Right back wheel

		link_revoluteRB = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_engineR = chrono::ChSharedPtr<chrono::ChLinkEngine>(new chrono::ChLinkEngine);
		link_distRBU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRBU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRBL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRBL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_springRB = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_distRBlat = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		
		//Left back wheel

		link_revoluteLB = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_engineL = chrono::ChSharedPtr<chrono::ChLinkEngine>(new chrono::ChLinkEngine);
		link_distLBU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLBU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLBL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLBL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_springLB = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_distLBlat = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);

		conic_tau = 3.42; // the transmission ratio of the conic gears at the rear axle
		gear_tau = 2.97; // the actual tau of the gear
		max_motor_torque = 488; // the max torque of the motor [Nm];
		max_motor_speed = 37680;	 // the max rotation speed of the motor [rads/s]

		shift(1);
	}

	VESuspensionDemo::VESuspensionDemo(EnvironmentCore::EnvironmentCoreApplication* App) : VEVehicle(App) {

		truss = nullptr;
		spindleRF = nullptr;
		wheelRF = nullptr;
		spindleLF = nullptr;
		wheelLF = nullptr;
		spindleRB = nullptr;
		wheelRB = nullptr;
		spindleLB = nullptr;
		wheelLB = nullptr;

		//Right front wheel

		link_revoluteRF = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_distRFU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRFU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRFL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRFL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_springRF = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_distRSTEER = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);

		//Left front wheel

		link_revoluteLF = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_distLFU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLFU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLFL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLFL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_springLF = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_distLSTEER = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);

		//Right back wheel

		link_revoluteRB = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_engineR = chrono::ChSharedPtr<chrono::ChLinkEngine>(new chrono::ChLinkEngine);
		link_distRBU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRBU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRBL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRBL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_springRB = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_distRBlat = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);

		//Left back wheel

		link_revoluteLB = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_engineL = chrono::ChSharedPtr<chrono::ChLinkEngine>(new chrono::ChLinkEngine);
		link_distLBU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLBU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLBL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLBL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_springLB = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_distLBlat = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);

		build(chrono::ChVector<>(0, 10, 0));

		conic_tau = 10; // the transmission ratio of the conic gears at the rear axle
		gear_tau = 0.5; // the actual tau of the gear
		max_motor_torque = 30; // the max torque of the motor [Nm];
		max_motor_speed = 100;	 // the max rotation speed of the motor [rads/s]
	}

	VESuspensionDemo::~VESuspensionDemo() {

	}

	void VESuspensionDemo::build(chrono::ChVector<>& Pos) {
		double wheel_fric = .9;
		chrono::ChVector<> r;
		double chassis_mass = 140.0;
		double spindle_mass = 3.3;
		double wheel_mass = 1.8;
		r = chrono::ChVector<>(1.0, 0.5, 3)*.5;
		chrono::ChVector<> inertia_chassis (1 / 12.0 * chassis_mass * (r.y * r.y + r.z * r.z), 1 / 12.0 * chassis_mass * (r.x * r.x + r.z * r.z), 1 / 12.0 * chassis_mass * (r.x * r.x + r.y * r.y));;
		r = chrono::ChVector<>(0.1, 0.4, 0.4)*.5;
		chrono::ChVector<> inertia_spindle(1 / 12.0 * spindle_mass * (r.y * r.y + r.z * r.z), 1 / 12.0 * spindle_mass * (r.x * r.x + r.z * r.z), 1 / 12.0 * spindle_mass * (r.x * r.x + r.y * r.y));;
		r = chrono::ChVector<>(0.9, 0.3, 0.9)*0.5;
		chrono::ChVector<> inertia_wheel(1 / 5.0 * wheel_mass * (r.y * r.y + r.z * r.z), 1 / 5.0 * wheel_mass * (r.x * r.x + r.z * r.z), 1 / 5.0 * wheel_mass * (r.x * r.x + r.y * r.y));

		
		

		truss = &m_pApp->getScene()->spawnBox("Truss", chassis_mass, chrono::ChVector<>(0, 1, 0) + Pos, chrono::ChVector<>(1.0, 0.5, 3)*.5);
		truss->getChBody()->SetInertiaXX(inertia_chassis);
		truss->getChBody()->SetCollide(false);
		truss->deletable = false;

		spindleRF = &m_pApp->getScene()->spawnBox("SpindleRF", 33.0, chrono::ChVector<>(1.3, 1, 1) + Pos, chrono::ChVector<>(0.1, 0.4, 0.4)*.5);
		r = chrono::ChVector<>(0.1, 0.4, 0.4)*.5;
		spindleRF->getChBody()->SetInertiaXX(inertia_spindle);
		spindleRF->getChBody()->SetCollide(false);
		spindleRF->deletable = false;

		wheelRF = &m_pApp->getScene()->spawnEllipsoid("WheelRF", 18.0, chrono::ChVector<>(1.5, 1, 1) + Pos, chrono::ChVector<>(0.9, 0.3, 0.9)*0.5, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelRF->getChBody()->SetInertiaXX(inertia_wheel);
		wheelRF->getChBody()->SetFriction(wheel_fric);
		wheelRF->deletable = false;

		spindleLF = &m_pApp->getScene()->spawnBox("SpindleLF", 33.0, chrono::ChVector<>(-1.3, 1, 1) + Pos, chrono::ChVector<>(0.1, 0.4, 0.4)*.5);
		spindleLF->getChBody()->SetInertiaXX(inertia_spindle);
		spindleLF->getChBody()->SetCollide(false);
		spindleLF->deletable = false;

		wheelLF = &m_pApp->getScene()->spawnEllipsoid("WheelLF", 18.0, chrono::ChVector<>(-1.5, 1, 1) + Pos, chrono::ChVector<>(0.9, 0.3, 0.9)*0.5, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelLF->getChBody()->SetInertiaXX(inertia_wheel);
		wheelLF->getChBody()->SetFriction(wheel_fric);
		wheelLF->deletable = false;

		spindleRB = &m_pApp->getScene()->spawnBox("SpindleRB", 33.0, chrono::ChVector<>(1.3, 1, -1) + Pos, chrono::ChVector<>(0.1, 0.4, 0.4)*.5);
		spindleRB->getChBody()->SetInertiaXX(inertia_spindle);
		spindleRB->getChBody()->SetCollide(false);
		spindleRB->deletable = false;

		wheelRB = &m_pApp->getScene()->spawnEllipsoid("WheelRB", 18.0, chrono::ChVector<>(1.5, 1, -1) + Pos, chrono::ChVector<>(0.9, 0.3, 0.9)*0.5, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelRB->getChBody()->SetInertiaXX(inertia_wheel);
		wheelRB->getChBody()->SetFriction(wheel_fric);
		wheelRB->deletable = false;

		spindleLB = &m_pApp->getScene()->spawnBox("SpindleLB", 33.0, chrono::ChVector<>(-1.3, 1, -1) + Pos, chrono::ChVector<>(0.1, 0.4, 0.4)*.5);
		spindleLB->getChBody()->SetInertiaXX(inertia_spindle);
		spindleLB->getChBody()->SetCollide(false);
		spindleLB->deletable = false;

		wheelLB = &m_pApp->getScene()->spawnEllipsoid("WheelLB", 18.0, chrono::ChVector<>(-1.5, 1, -1) + Pos, chrono::ChVector<>(0.9, 0.3, 0.9)*0.5, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelLB->getChBody()->SetInertiaXX(inertia_wheel);
		wheelLB->getChBody()->SetFriction(wheel_fric);
		wheelLB->deletable = false;

		double spring_k_front = 23800;//9393;
		double spring_k_rear = 23800;//12750;
		//Right front wheel

		link_revoluteRF->Initialize(wheelRF->getChBody(), spindleRF->getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(1.5, 1, 1) + Pos, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		m_pApp->getChSystem()->AddLink(link_revoluteRF);

		link_distRFU1->Initialize(truss->getChBody(), spindleRF->getChBody(), false, chrono::ChVector<>(0.5, 1.2, 1.2) + Pos, chrono::ChVector<>(1.25, 1.2, 1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distRFU1);

		link_distRFU2->Initialize(truss->getChBody(), spindleRF->getChBody(), false, chrono::ChVector<>(0.5, 1.2, 0.8) + Pos, chrono::ChVector<>(1.25, 1.2, 1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distRFU2);

		link_distRFL1->Initialize(truss->getChBody(), spindleRF->getChBody(), false, chrono::ChVector<>(0.5, 0.8, 1.2) + Pos, chrono::ChVector<>(1.25, 0.8, 1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distRFL1);

		link_distRFL2->Initialize(truss->getChBody(), spindleRF->getChBody(), false, chrono::ChVector<>(0.5, 0.8, 0.8) + Pos, chrono::ChVector<>(1.25, 0.8, 1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distRFL2);

		link_springRF->Initialize(truss->getChBody(), spindleRF->getChBody(), false, chrono::ChVector<>(0.5, 1.2, 1.0) + Pos, chrono::ChVector<>(1.25, 0.8, 1) + Pos);
		link_springRF->Set_SpringK(spring_k_front);
		link_springRF->Set_SpringR(80);
		m_pApp->getChSystem()->AddLink(link_springRF);

		link_distRSTEER->Initialize(truss->getChBody(), spindleRF->getChBody(), false, chrono::ChVector<>(0.5, 1.21, 1.4) + Pos, chrono::ChVector<>(1.25, 1.21, 1.3) + Pos);
		m_pApp->getChSystem()->AddLink(link_distRSTEER);

		//Left front wheel

		link_revoluteLF->Initialize(wheelLF->getChBody(), spindleLF->getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(-1.5, 1, 1) + Pos, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		m_pApp->getChSystem()->AddLink(link_revoluteLF);

		link_distLFU1->Initialize(truss->getChBody(), spindleLF->getChBody(), false, chrono::ChVector<>(-0.5, 1.2, 1.2) + Pos, chrono::ChVector<>(-1.25, 1.2, 1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distLFU1);

		link_distLFU2->Initialize(truss->getChBody(), spindleLF->getChBody(), false, chrono::ChVector<>(-0.5, 1.2, 0.8) + Pos, chrono::ChVector<>(-1.25, 1.2, 1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distLFU2);

		link_distLFL1->Initialize(truss->getChBody(), spindleLF->getChBody(), false, chrono::ChVector<>(-0.5, 0.8, 1.2) + Pos, chrono::ChVector<>(-1.25, 0.8, 1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distLFL1);

		link_distLFL2->Initialize(truss->getChBody(), spindleLF->getChBody(), false, chrono::ChVector<>(-0.5, 0.8, 0.8) + Pos, chrono::ChVector<>(-1.25, 0.8, 1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distLFL2);

		link_springLF->Initialize(truss->getChBody(), spindleLF->getChBody(), false, chrono::ChVector<>(-0.5, 1.2, 1.0) + Pos, chrono::ChVector<>(-1.25, 0.8, 1) + Pos);
		link_springLF->Set_SpringK(spring_k_front);
		link_springLF->Set_SpringR(80);
		m_pApp->getChSystem()->AddLink(link_springLF);

		link_distLSTEER->Initialize(truss->getChBody(), spindleLF->getChBody(), false, chrono::ChVector<>(-0.5, 1.21, 1.4) + Pos, chrono::ChVector<>(-1.25, 1.21, 1.3) + Pos);
		m_pApp->getChSystem()->AddLink(link_distLSTEER);

		//Right back wheel

		link_revoluteRB->Initialize(wheelRB->getChBody(), spindleRB->getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(1.5, 1, -1) + Pos, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		m_pApp->getChSystem()->AddLink(link_revoluteRB);

		link_engineR->Initialize(wheelRB->getChBody(), truss->getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(1.5, 1, -1) + Pos, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		link_engineR->Set_shaft_mode(chrono::ChLinkEngine::ENG_SHAFT_CARDANO);
		link_engineR->Set_eng_mode(chrono::ChLinkEngine::ENG_MODE_TORQUE);
		m_pApp->getChSystem()->AddLink(link_engineR);

		link_distRBU1->Initialize(truss->getChBody(), spindleRB->getChBody(), false, chrono::ChVector<>(0.5, 1.2, -1.2) + Pos, chrono::ChVector<>(1.25, 1.2, -1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distRBU1);

		link_distRBU2->Initialize(truss->getChBody(), spindleRB->getChBody(), false, chrono::ChVector<>(0.5, 1.2, -0.8) + Pos, chrono::ChVector<>(1.25, 1.2, -1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distRBU2);

		link_distRBL1->Initialize(truss->getChBody(), spindleRB->getChBody(), false, chrono::ChVector<>(0.5, 0.8, -1.2) + Pos, chrono::ChVector<>(1.25, 0.8, -1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distRBL1);

		link_distRBL2->Initialize(truss->getChBody(), spindleRB->getChBody(), false, chrono::ChVector<>(0.5, 0.8, -0.8) + Pos, chrono::ChVector<>(1.25, 0.8, -1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distRBL2);

		link_springRB->Initialize(truss->getChBody(), spindleRB->getChBody(), false, chrono::ChVector<>(0.5, 1.2, -1.0) + Pos, chrono::ChVector<>(1.25, 0.8, -1) + Pos);
		link_springRB->Set_SpringK(spring_k_rear);
		link_springRB->Set_SpringR(80);
		m_pApp->getChSystem()->AddLink(link_springRB);

		link_distRBlat->Initialize(truss->getChBody(), spindleRB->getChBody(), false, chrono::ChVector<>(0.5, 1.21, -1.4) + Pos, chrono::ChVector<>(1.25, 1.21, -1.3) + Pos);
		m_pApp->getChSystem()->AddLink(link_distRBlat);

		//Left back wheel

		link_revoluteLB->Initialize(wheelLB->getChBody(), spindleLB->getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(-1.5, 1, -1) + Pos, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		m_pApp->getChSystem()->AddLink(link_revoluteLB);

		link_engineL->Initialize(wheelLB->getChBody(), truss->getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(-1.5, 1, -1) + Pos, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		link_engineL->Set_shaft_mode(chrono::ChLinkEngine::ENG_SHAFT_CARDANO);
		link_engineL->Set_eng_mode(chrono::ChLinkEngine::ENG_MODE_TORQUE);
		m_pApp->getChSystem()->AddLink(link_engineL);

		link_distLBU1->Initialize(truss->getChBody(), spindleLB->getChBody(), false, chrono::ChVector<>(-0.5, 1.2, -1.2) + Pos, chrono::ChVector<>(-1.25, 1.2, -1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distLBU1);

		link_distLBU2->Initialize(truss->getChBody(), spindleLB->getChBody(), false, chrono::ChVector<>(-0.5, 1.2, -0.8) + Pos, chrono::ChVector<>(-1.25, 1.2, -1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distLBU2);

		link_distLBL1->Initialize(truss->getChBody(), spindleLB->getChBody(), false, chrono::ChVector<>(-0.5, 0.8, -1.2) + Pos, chrono::ChVector<>(-1.25, 0.8, -1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distLBL1);

		link_distLBL2->Initialize(truss->getChBody(), spindleLB->getChBody(), false, chrono::ChVector<>(-0.5, 0.8, -0.8) + Pos, chrono::ChVector<>(-1.25, 0.8, -1) + Pos);
		m_pApp->getChSystem()->AddLink(link_distLBL2);

		link_springLB->Initialize(truss->getChBody(), spindleLB->getChBody(), false, chrono::ChVector<>(-0.5, 1.2, -1.0) + Pos, chrono::ChVector<>(-1.25, 0.8, -1) + Pos);
		link_springLB->Set_SpringK(spring_k_rear);
		link_springLB->Set_SpringR(80);
		m_pApp->getChSystem()->AddLink(link_springLB);

		link_distLBlat->Initialize(truss->getChBody(), spindleLB->getChBody(), false, chrono::ChVector<>(-0.5, 1.21, -1.4) + Pos, chrono::ChVector<>(-1.25, 1.21, -1.3) + Pos);
		m_pApp->getChSystem()->AddLink(link_distLBlat);
	}

	void VESuspensionDemo::update() {

		link_distRSTEER->SetEndPoint1Rel(chrono::ChVector<>(0.5 + steer, 0.21, 1.4));
		link_distLSTEER->SetEndPoint1Rel(chrono::ChVector<>(-0.5 + steer, 0.21, 1.4));

		double shaftspeed = (1.0 / conic_tau) * 0.5 *
			(link_engineL->Get_mot_rot_dt() + link_engineR->Get_mot_rot_dt());
		// The motorspeed is the shaft speed multiplied by gear ratio inversed:
		double motorspeed = (1.0 / gear_tau)*shaftspeed;
		// The torque depends on speed-torque curve of the motor: here we assume a
		// very simplified model a bit like in DC motors:
		double motortorque = max_motor_torque - motorspeed*(max_motor_torque / max_motor_speed);
		// Motor torque is linearly modulated by throttle gas value:
		motortorque = motortorque *  throttle;
		// The torque at motor shaft:
		double shafttorque = motortorque * (1.0 / gear_tau);
		// The torque at wheels - for each wheel, given the differential transmission,
		// it is half of the shaft torque  (multiplied the conic gear transmission ratio)
		double singlewheeltorque = 0.5 * shafttorque * (1.0 / conic_tau);
		// Set the wheel torque in both 'engine' links, connecting the wheels to the truss;
		if (chrono::ChFunction_Const* mfun = dynamic_cast<chrono::ChFunction_Const*>(link_engineL->Get_tor_funct()))
			mfun->Set_yconst(singlewheeltorque);
		if (chrono::ChFunction_Const* mfun = dynamic_cast<chrono::ChFunction_Const*>(link_engineR->Get_tor_funct()))
			mfun->Set_yconst(singlewheeltorque);
		//debug:print infos on screen:
		//GetLog() << "motor torque="<< motortorque<< "  speed=" << motorspeed << "  wheel torqe=" << singlewheeltorque <<"\n";
		// If needed, return also the value of wheel torque:

	}

	void VESuspensionDemo::reset(chrono::ChVector<>& Pos) {
		truss->getChBody()->SetPos(chrono::ChVector<>(0, 1, 0) + Pos);
		truss->getChBody()->SetRot(chrono::QUNIT);
		truss->getChBody()->SetPos_dt(chrono::ChVector<>(0, 0, 0));
		truss->getChBody()->SetRot_dt(chrono::QUNIT);

		spindleRF->getChBody()->SetPos(chrono::ChVector<>(1.3, 1, 1) + Pos);
		spindleRF->getChBody()->SetRot(chrono::QUNIT);
		spindleRF->getChBody()->SetPos_dt(chrono::ChVector<>(0, 0, 0));
		spindleRF->getChBody()->SetRot_dt(chrono::QUNIT);

		wheelRF->getChBody()->SetPos(chrono::ChVector<>(1.5, 1, 1) + Pos);
		wheelRF->getChBody()->SetRot(chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelRF->getChBody()->SetPos_dt(chrono::ChVector<>(0, 0, 0));
		wheelRF->getChBody()->SetRot_dt(chrono::QUNIT);

		spindleLF->getChBody()->SetPos(chrono::ChVector<>(-1.3, 1, 1) + Pos);
		spindleLF->getChBody()->SetRot(chrono::QUNIT);
		spindleLF->getChBody()->SetPos_dt(chrono::ChVector<>(0, 0, 0));
		spindleLF->getChBody()->SetRot_dt(chrono::QUNIT);

		wheelLF->getChBody()->SetPos(chrono::ChVector<>(-1.5, 1, 1) + Pos);
		wheelLF->getChBody()->SetRot(chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelLF->getChBody()->SetPos_dt(chrono::ChVector<>(0, 0, 0));
		wheelLF->getChBody()->SetRot_dt(chrono::QUNIT);

		spindleRB->getChBody()->SetPos(chrono::ChVector<>(1.3, 1, -1) + Pos);
		spindleRB->getChBody()->SetRot(chrono::QUNIT);
		spindleRB->getChBody()->SetPos_dt(chrono::ChVector<>(0, 0, 0));
		spindleRB->getChBody()->SetRot_dt(chrono::QUNIT);

		wheelRB->getChBody()->SetPos(chrono::ChVector<>(1.5, 1, -1) + Pos);
		wheelRB->getChBody()->SetRot(chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelRB->getChBody()->SetPos_dt(chrono::ChVector<>(0, 0, 0));
		wheelRB->getChBody()->SetRot_dt(chrono::QUNIT);

		spindleLB->getChBody()->SetPos(chrono::ChVector<>(-1.3, 1, -1) + Pos);
		spindleLB->getChBody()->SetRot(chrono::QUNIT);
		spindleLB->getChBody()->SetPos_dt(chrono::ChVector<>(0, 0, 0));
		spindleLB->getChBody()->SetRot_dt(chrono::QUNIT);

		wheelLB->getChBody()->SetPos(chrono::ChVector<>(-1.5, 1, -1) + Pos);
		wheelLB->getChBody()->SetRot(chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelLB->getChBody()->SetPos_dt(chrono::ChVector<>(0, 0, 0));
		wheelLB->getChBody()->SetRot_dt(chrono::QUNIT);
	}

	void VESuspensionDemo::shift(uint8_t gear) {
		switch (gear) {
		case 0: gear_tau = -3.38; break;
		case 1: gear_tau = 2.97; break;
		case 2: gear_tau = 2.07; break;
		case 3: gear_tau = 1.43; break;
		case 4: gear_tau = 1; break;
		case 5: gear_tau = 0.84; break;
		case 6: gear_tau = 0.56; break;
		}
		this->gear = gear;
	}

	void VESuspensionDemo::brake() {
		wheelRF->getChBody()->SetRot_dt(chrono::QUNIT);
		wheelLF->getChBody()->SetRot_dt(chrono::QUNIT);
		wheelRB->getChBody()->SetRot_dt(chrono::QUNIT);
		wheelLB->getChBody()->SetRot_dt(chrono::QUNIT);
	}

	chrono::ChSharedBodyPtr VESuspensionDemo::getChassis() {
		return truss->getChBody();
	}

	chrono::ChVector<> VESuspensionDemo::getPos() {
		return truss->getChBody()->GetPos();
	}

	chrono::ChQuaternion<> VESuspensionDemo::getRot() {
		return truss->getChBody()->GetRot();
	}

}