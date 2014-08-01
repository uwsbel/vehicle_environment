#include <random>
#include <chrono>
#include <cmath>

#include "ECApplication.h"

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

		app.timestep = 0.01;

		std::random_device l_rand;

		EnvironmentCore::ECBody& truss = app.getScene()->spawnBox("Truss", 150.0, chrono::ChVector<>(0, 1, 0), chrono::ChVector<>(1.0, 0.5, 3)*.5);
		truss->SetInertiaXX(chrono::ChVector<>(4.8, 4.5, 1));
		truss.deletable = false;

		EnvironmentCore::ECBody& spindleRF = app.getScene()->spawnBox("SpindleRF", 8.0, chrono::ChVector<>(1.3, 1, 1), chrono::ChVector<>(0.1, 0.4, 0.4)*.5);
		spindleRF->SetInertiaXX(chrono::ChVector<>(0.2, 0.2, 0.2));
		spindleRF->SetCollide(false);
		spindleRF.deletable = false;

		EnvironmentCore::ECBody& wheelRF = app.getScene()->spawnEllipsoid("WheelRF", 3.0, chrono::ChVector<>(1.5, 1, 1), chrono::ChVector<>(0.9, 0.3, 0.9)*.5, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelRF->SetInertiaXX(chrono::ChVector<>(0.2, 0.2, 0.2));
		wheelRF->SetFriction(2.0);
		wheelRF.deletable = false;

		chrono::ChSharedPtr<chrono::ChLinkLockRevolute> link_revoluteRF;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRFU1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRFU2;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRFL1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRFL2;
		chrono::ChSharedPtr<chrono::ChLinkSpring>   link_springRF;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRSTEER;

		EnvironmentCore::ECBody& spindleLF = app.getScene()->spawnBox("SpindleLF", 8.0, chrono::ChVector<>(-1.3, 1, 1), chrono::ChVector<>(0.1, 0.4, 0.4)*.5);
		spindleLF->SetInertiaXX(chrono::ChVector<>(0.2, 0.2, 0.2));
		spindleLF->SetCollide(false);
		spindleLF.deletable = false;

		EnvironmentCore::ECBody& wheelLF = app.getScene()->spawnEllipsoid("WheelLF", 3.0, chrono::ChVector<>(-1.5, 1, 1), chrono::ChVector<>(0.9, 0.3, 0.9)*.5, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelLF->SetInertiaXX(chrono::ChVector<>(0.2, 0.2, 0.2));
		wheelLF->SetFriction(2.0);
		wheelLF.deletable = false;

		chrono::ChSharedPtr<chrono::ChLinkLockRevolute> link_revoluteLF;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLFU1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLFU2;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLFL1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLFL2;
		chrono::ChSharedPtr<chrono::ChLinkSpring>   link_springLF;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLSTEER;

		EnvironmentCore::ECBody& spindleRB = app.getScene()->spawnBox("SpindleRB", 8.0, chrono::ChVector<>(1.3, 1, -1), chrono::ChVector<>(0.1, 0.4, 0.4)*.5);
		spindleRB->SetInertiaXX(chrono::ChVector<>(0.2, 0.2, 0.2));
		spindleRB->SetCollide(false);
		spindleRB.deletable = false;

		EnvironmentCore::ECBody& wheelRB = app.getScene()->spawnEllipsoid("WheelRB", 3.0, chrono::ChVector<>(1.5, 1, -1), chrono::ChVector<>(0.9, 0.3, 0.9)*.5, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelRB->SetInertiaXX(chrono::ChVector<>(0.2, 0.2, 0.2));
		wheelRB->SetFriction(2.0);
		wheelRB.deletable = false;

		chrono::ChSharedPtr<chrono::ChLinkLockRevolute> link_revoluteRB;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRBU1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRBU2;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRBL1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRBL2;
		chrono::ChSharedPtr<chrono::ChLinkSpring>   link_springRB;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distRBlat;
		chrono::ChSharedPtr<chrono::ChLinkEngine>   link_engineL;

		EnvironmentCore::ECBody& spindleLB = app.getScene()->spawnBox("SpindleLB", 8.0, chrono::ChVector<>(-1.3, 1, -1), chrono::ChVector<>(0.1, 0.4, 0.4)*.5);
		spindleLB->SetInertiaXX(chrono::ChVector<>(0.2, 0.2, 0.2));
		spindleLB->SetCollide(false);
		spindleLB.deletable = false;

		EnvironmentCore::ECBody& wheelLB = app.getScene()->spawnEllipsoid("WheelLB", 3.0, chrono::ChVector<>(-1.5, 1, -1), chrono::ChVector<>(0.9, 0.3, 0.9)*.5, chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Z));
		wheelLB->SetInertiaXX(chrono::ChVector<>(0.2, 0.2, 0.2));
		wheelLB->SetFriction(2.0);
		wheelLB.deletable = false;

		chrono::ChSharedPtr<chrono::ChLinkLockRevolute> link_revoluteLB;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLBU1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLBU2;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLBL1;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLBL2;
		chrono::ChSharedPtr<chrono::ChLinkSpring>   link_springLB;
		chrono::ChSharedPtr<chrono::ChLinkDistance> link_distLBlat;
		chrono::ChSharedPtr<chrono::ChLinkEngine>   link_engineR;


		//Right front wheel

		link_revoluteRF = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_revoluteRF->Initialize(wheelRF.getChBody(), spindleRF.getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(1.5, 1, 1), chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		app.getChSystem()->AddLink(link_revoluteRF);

		link_distRFU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRFU1->Initialize(truss.getChBody(), spindleRF.getChBody(), false, chrono::ChVector<>(0.5, 1.2, 1.2), chrono::ChVector<>(1.25, 1.2, 1));
		app.getChSystem()->AddLink(link_distRFU1);

		link_distRFU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRFU2->Initialize(truss.getChBody(), spindleRF.getChBody(), false, chrono::ChVector<>(0.5, 1.2, 0.8), chrono::ChVector<>(1.25, 1.2, 1));
		app.getChSystem()->AddLink(link_distRFU2);

		link_distRFL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRFL1->Initialize(truss.getChBody(), spindleRF.getChBody(), false, chrono::ChVector<>(0.5, 0.8, 1.2), chrono::ChVector<>(1.25, 0.8, 1));
		app.getChSystem()->AddLink(link_distRFL1);

		link_distRFL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRFL2->Initialize(truss.getChBody(), spindleRF.getChBody(), false, chrono::ChVector<>(0.5, 0.8, 0.8), chrono::ChVector<>(1.25, 0.8, 1));
		app.getChSystem()->AddLink(link_distRFL2);

		link_springRF = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_springRF->Initialize(truss.getChBody(), spindleRF.getChBody(), false, chrono::ChVector<>(0.5, 1.2, 1.0), chrono::ChVector<>(1.25, 0.8, 1));
		link_springRF->Set_SpringK(28300);
		link_springRF->Set_SpringR(80);
		app.getChSystem()->AddLink(link_springRF);

		link_distRSTEER = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRSTEER->Initialize(truss.getChBody(), spindleRF.getChBody(), false, chrono::ChVector<>(0.5, 1.21, 1.4), chrono::ChVector<>(1.25, 1.21, 1.3));
		app.getChSystem()->AddLink(link_distRSTEER);

		//Left front wheel

		link_revoluteLF = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_revoluteLF->Initialize(wheelLF.getChBody(), spindleLF.getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(-1.5, 1, 1), chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		app.getChSystem()->AddLink(link_revoluteLF);

		link_distLFU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLFU1->Initialize(truss.getChBody(), spindleLF.getChBody(), false, chrono::ChVector<>(-0.5, 1.2, 1.2), chrono::ChVector<>(-1.25, 1.2, 1));
		app.getChSystem()->AddLink(link_distLFU1);

		link_distLFU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLFU2->Initialize(truss.getChBody(), spindleLF.getChBody(), false, chrono::ChVector<>(-0.5, 1.2, 0.8), chrono::ChVector<>(-1.25, 1.2, 1));
		app.getChSystem()->AddLink(link_distLFU2);

		link_distLFL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLFL1->Initialize(truss.getChBody(), spindleLF.getChBody(), false, chrono::ChVector<>(-0.5, 0.8, 1.2), chrono::ChVector<>(-1.25, 0.8, 1));
		app.getChSystem()->AddLink(link_distLFL1);

		link_distLFL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLFL2->Initialize(truss.getChBody(), spindleLF.getChBody(), false, chrono::ChVector<>(-0.5, 0.8, 0.8), chrono::ChVector<>(-1.25, 0.8, 1));
		app.getChSystem()->AddLink(link_distLFL2);

		link_springLF = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_springLF->Initialize(truss.getChBody(), spindleLF.getChBody(), false, chrono::ChVector<>(-0.5, 1.2, 1.0), chrono::ChVector<>(-1.25, 0.8, 1));
		link_springLF->Set_SpringK(28300);
		link_springLF->Set_SpringR(80);
		app.getChSystem()->AddLink(link_springLF);

		link_distLSTEER = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLSTEER->Initialize(truss.getChBody(), spindleLF.getChBody(), false, chrono::ChVector<>(-0.5, 1.21, 1.4), chrono::ChVector<>(-1.25, 1.21, 1.3));
		app.getChSystem()->AddLink(link_distLSTEER);

		//Right back wheel

		link_revoluteRB = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_revoluteRB->Initialize(wheelRB.getChBody(), spindleRB.getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(1.5, 1, -1), chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		app.getChSystem()->AddLink(link_revoluteRB);

		link_engineR = chrono::ChSharedPtr<chrono::ChLinkEngine>(new chrono::ChLinkEngine);
		link_engineR->Initialize(wheelRB.getChBody(), truss.getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(1.5, 1, -1), chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		link_engineR->Set_shaft_mode(chrono::ChLinkEngine::ENG_SHAFT_CARDANO);
		link_engineR->Set_eng_mode(chrono::ChLinkEngine::ENG_MODE_TORQUE);
		app.getChSystem()->AddLink(link_engineR);

		link_distRBU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRBU1->Initialize(truss.getChBody(), spindleRB.getChBody(), false, chrono::ChVector<>(0.5, 1.2, -1.2), chrono::ChVector<>(1.25, 1.2, -1));
		app.getChSystem()->AddLink(link_distRBU1);

		link_distRBU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRBU2->Initialize(truss.getChBody(), spindleRB.getChBody(), false, chrono::ChVector<>(0.5, 1.2, -0.8), chrono::ChVector<>(1.25, 1.2, -1));
		app.getChSystem()->AddLink(link_distRBU2);

		link_distRBL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRBL1->Initialize(truss.getChBody(), spindleRB.getChBody(), false, chrono::ChVector<>(0.5, 0.8, -1.2), chrono::ChVector<>(1.25, 0.8, -1));
		app.getChSystem()->AddLink(link_distRBL1);

		link_distRBL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRBL2->Initialize(truss.getChBody(), spindleRB.getChBody(), false, chrono::ChVector<>(0.5, 0.8, -0.8), chrono::ChVector<>(1.25, 0.8, -1));
		app.getChSystem()->AddLink(link_distRBL2);

		link_springRB = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_springRB->Initialize(truss.getChBody(), spindleRB.getChBody(), false, chrono::ChVector<>(0.5, 1.2, -1.0), chrono::ChVector<>(1.25, 0.8, -1));
		link_springRB->Set_SpringK(28300);
		link_springRB->Set_SpringR(80);
		app.getChSystem()->AddLink(link_springRB);

		link_distRBlat = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distRBlat->Initialize(truss.getChBody(), spindleRB.getChBody(), false, chrono::ChVector<>(0.5, 1.21, -1.4), chrono::ChVector<>(1.25, 1.21, -1.3));
		app.getChSystem()->AddLink(link_distRBlat);

		//Left back wheel

		link_revoluteLB = chrono::ChSharedPtr<chrono::ChLinkLockRevolute>(new chrono::ChLinkLockRevolute);
		link_revoluteLB->Initialize(wheelLB.getChBody(), spindleLB.getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(-1.5, 1, -1), chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		app.getChSystem()->AddLink(link_revoluteLB);

		link_engineL = chrono::ChSharedPtr<chrono::ChLinkEngine>(new chrono::ChLinkEngine);
		link_engineL->Initialize(wheelLB.getChBody(), truss.getChBody(),
			chrono::ChCoordsys<>(chrono::ChVector<>(-1.5, 1, -1), chrono::Q_from_AngAxis(chrono::CH_C_PI / 2, chrono::VECT_Y)));
		link_engineL->Set_shaft_mode(chrono::ChLinkEngine::ENG_SHAFT_CARDANO);
		link_engineL->Set_eng_mode(chrono::ChLinkEngine::ENG_MODE_TORQUE);
		app.getChSystem()->AddLink(link_engineL);

		link_distLBU1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLBU1->Initialize(truss.getChBody(), spindleLB.getChBody(), false, chrono::ChVector<>(-0.5, 1.2, -1.2), chrono::ChVector<>(-1.25, 1.2, -1));
		app.getChSystem()->AddLink(link_distLBU1);

		link_distLBU2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLBU2->Initialize(truss.getChBody(), spindleLB.getChBody(), false, chrono::ChVector<>(-0.5, 1.2, -0.8), chrono::ChVector<>(-1.25, 1.2, -1));
		app.getChSystem()->AddLink(link_distLBU2);

		link_distLBL1 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLBL1->Initialize(truss.getChBody(), spindleLB.getChBody(), false, chrono::ChVector<>(-0.5, 0.8, -1.2), chrono::ChVector<>(-1.25, 0.8, -1));
		app.getChSystem()->AddLink(link_distLBL1);

		link_distLBL2 = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLBL2->Initialize(truss.getChBody(), spindleLB.getChBody(), false, chrono::ChVector<>(-0.5, 0.8, -0.8), chrono::ChVector<>(-1.25, 0.8, -1));
		app.getChSystem()->AddLink(link_distLBL2);

		link_springLB = chrono::ChSharedPtr<chrono::ChLinkSpring>(new chrono::ChLinkSpring);
		link_springLB->Initialize(truss.getChBody(), spindleLB.getChBody(), false, chrono::ChVector<>(-0.5, 1.2, -1.0), chrono::ChVector<>(-1.25, 0.8, -1));
		link_springLB->Set_SpringK(28300);
		link_springLB->Set_SpringR(80);
		app.getChSystem()->AddLink(link_springLB);

		link_distLBlat = chrono::ChSharedPtr<chrono::ChLinkDistance>(new chrono::ChLinkDistance);
		link_distLBlat->Initialize(truss.getChBody(), spindleLB.getChBody(), false, chrono::ChVector<>(-0.5, 1.21, -1.4), chrono::ChVector<>(-1.25, 1.21, -1.3));
		app.getChSystem()->AddLink(link_distLBlat);





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

		EnvironmentCore::ECBody& Epsilon3 = app.getScene()->spawnSphere("Spheere3", 1, chrono::ChVector<>(50, 10, 50), 4);
		Epsilon2->SetInertiaXX(chrono::ChVector<>(
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0),
			((2.0 / 5.0)*Epsilon->GetMass() * 4.0 * 4.0)));

		EnvironmentCore::ECBody& Epsilon4 = app.getScene()->spawnBox("Spheere4", 10, chrono::ChVector<>(-20, 10, -70), chrono::ChVector<>(4, 4, 4));
		Epsilon2->SetInertiaXX(chrono::ChVector<>(
			((1.0 / 12.0)*Epsilon->GetMass() * (16.0 + 16.0)),
			((1.0 / 12.0)*Epsilon->GetMass() * (16.0 + 16.0)),
			((1.0 / 12.0)*Epsilon->GetMass() * (16.0 + 16.0))));

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

		EnvironmentCore::ECBody& Building = app.getScene()->spawnBox("Building1", 50000, chrono::ChVector<>(0, 240, 100), chrono::ChVector<>(20, 500, 20), chrono::ChQuaternion<>(1, 0, 0, 0), true);

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
		chrono::ChQuaternion<> dirRot = truss->GetRot();
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

		SDL_HapticEffect effect;
		memset(&effect, 0, sizeof(SDL_HapticEffect)); // 0 is safe default
		effect.type = SDL_HAPTIC_SINE;
		effect.periodic.direction.type = SDL_HAPTIC_POLAR; // Polar coordinates
		effect.periodic.direction.dir[0] = 18000; // Force comes from south
		effect.periodic.period = 1000; // 1000 ms
		effect.periodic.magnitude = 20000; // 20000/32767 strength
		effect.periodic.length = 5000; // 5 seconds long
		effect.periodic.attack_length = 1000; // Takes 1 second to get max strength
		effect.periodic.fade_length = 1000; // Takes 1 second to fade away

		app.getChSystem()->SetIterLCPmaxItersSpeed(20);

		std::function<int()> Loop = [&]() {

			if ((app.getInputManager()->getMouseState().right.down || app.getInputManager()->getControllerState().b.down) && db) {
				EnvironmentCore::ECBody& Alpha = app.getScene()->spawnSphere("Boox", 50, chrono::ChVector<>(truss->GetPos().x, truss->GetPos().y+3, truss->GetPos().z), 0.3);
				Alpha->SetInertiaXX(chrono::ChVector<>(
					((2.0 / 5.0)*Alpha->GetMass() * 0.3 * 0.3),
					((2.0 / 5.0)*Alpha->GetMass() * 0.3 * 0.3),
					((2.0 / 5.0)*Alpha->GetMass() * 0.3 * 0.3)));

				auto dir = truss->GetRot().Rotate(chrono::ChVector<>(0, 0, 1));

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

			if (app.getInputManager()->getControllerState().a.down) {
				auto dir = truss->GetRot().Rotate(chrono::ChVector<>(0, 0, 1));
				truss->SetPos_dt(chrono::ChVector<>(0, 5, 0) + (dir * 25));

				auto vert = truss->GetRot().Rotate(chrono::ChVector<>(0, 1, 0));

				vert = chrono::ChVector<>(0, 1, 0) * (app.getInputManager()->getControllerState().lsticky.value * 0.1);
				if (app.getInputManager()->getControllerState().lsticky.value > 0.50) {
					wheelRF->SetPos_dt(vert * 0.01);
					wheelLF->SetPos_dt(vert * 0.01);
				}
			}

			if (app.getInputManager()->getControllerState().rbumper.down && db2) {
				app.getInputManager()->runHapticRumble(1.0f, 1);
				db2 = false;
			}
			if (!app.getInputManager()->getControllerState().rbumper.down) {
				db2 = true;
			}

			double steer = 0.05*((double)((double)INT_MAX * -1.0 * app.getInputManager()->getControllerState().lstickx.value));

			if (steer > 0.1){
				steer = 0.1;
			}else if (steer < -.1){
				steer = -.1;
			}

			link_distRSTEER->SetEndPoint1Rel(chrono::ChVector<>(0.5 + steer, 0.21, 1.4));
			link_distLSTEER->SetEndPoint1Rel(chrono::ChVector<>(-0.5 + steer, 0.21, 1.4));

			if (app.getInputManager()->getKeyState(SDL_SCANCODE_W).down || (app.getInputManager()->getControllerState().rtrigger.value > 0.50) || (app.getInputManager()->getControllerState().ltrigger.value > 0.50)) {
				throttle = 40 * (app.getInputManager()->getControllerState().rtrigger.value - app.getInputManager()->getControllerState().ltrigger.value);
			}
			else {
				throttle = 0;
			}

			if (app.getInputManager()->getKeyState(SDL_SCANCODE_ESCAPE).down || app.getInputManager()->getControllerState().back.down) {
				return 1;
			}

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


			follow.setDiffuseColour((float)(motorspeed / max_motor_speed), (float)(motorspeed / max_motor_speed), (float)(motorspeed / max_motor_speed));
			follow.setSpecularColour((float)(motorspeed / max_motor_speed), (float)(motorspeed / max_motor_speed), (float)(motorspeed / max_motor_speed));


			dirRot = truss->GetRot();
			dirRot.Normalize();
			direction = dirRot.Rotate(chrono::ChVector<>(0, 0, -20));

			look_at = truss->GetPos();
			camera_tpos = (truss->GetPos() + direction);

			auto camera_dpos = camera_tpos - camera_pos;

			auto fSpring = (camera_dpos * 200) - (camera_vel * 200);

			auto cam_accel = fSpring / 5;

			camera_vel = camera_vel + cam_accel * app.timestep;

			camera_pos = camera_pos + camera_vel * app.timestep + 0.5 * cam_accel * app.timestep * app.timestep;
			

			DebugCamera->orient(camera_pos.x, camera_pos.y + 10, camera_pos.z, look_at.x, look_at.y+6, look_at.z);
			app.setCamera(DebugCamera);

			follow.setPosition(truss->GetPos().x, truss->GetPos().y + 10, truss->GetPos().z + 14);


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
