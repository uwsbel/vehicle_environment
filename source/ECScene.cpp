/*
Author: Charles Ricchio

Contains the definitions for ECScene
*/

#include "ECScene.h"

namespace EnvironmentCore {

	ECScene::ECScene(Ogre::SceneManager* SceneManager, chrono::ChSystem* System) {
		m_pSceneManager = SceneManager;
		m_pChSystem = System;
		m_LowerLimit = 0;
	}

	ECScene::~ECScene() {
		for (unsigned int i = 0; i < m_ECBodies.size(); i++) {
			if (m_ECBodies[i]) {
				delete m_ECBodies[i];
			}
		}
	}


	void ECScene::setAmbientLight(Ogre::ColourValue Color) {
		m_pSceneManager->setAmbientLight(Color);
	}

	void ECScene::setAmbientLight(float r, float g, float b) {
		m_pSceneManager->setAmbientLight(Ogre::ColourValue(r, g, b));
	}



	ECBody& ECScene::createBody(std::string Name) {
		ECBody* _ret = new ECBody(m_pSceneManager, m_pChSystem);
		_ret->name = Name;
		m_ECBodies.push_back(_ret);
		return *_ret;
	}

	ECBody& ECScene::getBody(std::string Name) {
		ECBody* _ret = nullptr;
		for (unsigned int i = 0; i < m_ECBodies.size(); i++) {
			if (m_ECBodies[i]) {
				if (Name == m_ECBodies[i]->name) {
					_ret = m_ECBodies[i];
				}
			}
		}
		return *_ret;
	}

	void ECScene::removeBody(ECBody& Body) {
		for (unsigned int i = 0; i < m_ECBodies.size(); i++) {
			if (m_ECBodies[i]) {
				if (&Body == m_ECBodies[i]) {
					delete m_ECBodies[i];
					m_ECBodies[i] = m_ECBodies.back();
					m_ECBodies.pop_back();
				}
			}
		}
	}

	void ECScene::removeBody(std::string Name) {
		for (unsigned int i = 0; i < m_ECBodies.size(); i++) {
			if (m_ECBodies[i]) {
				if (Name == m_ECBodies[i]->name) {
					delete m_ECBodies[i];
					m_ECBodies[i] = m_ECBodies.back();
					m_ECBodies.pop_back();
				}
			}
		}
	}

	void ECScene::update() {
		for (unsigned int i = 0; i < m_ECBodies.size(); i++) {
			m_ECBodies[i]->update();
			if (m_ECBodies[i]->getChBody()->GetPos().y < m_LowerLimit && m_ECBodies[i]->deletable == true && m_LowerLimit < 0) {
				removeBody(*m_ECBodies[i]);
			}
		}
	}


	ECBody& ECScene::spawnBox(std::string Name,
		double mass,
		chrono::ChVector<>& position,
		chrono::ChVector<>& size,
		chrono::ChQuaternion<>& rotation,
		bool fixed) {

		ECBody& _ret = createBody(Name);

		chrono::ChSharedPtr<chrono::ChBoxShape> _box(new chrono::ChBoxShape);
		_box->GetBoxGeometry().Size = size;

		_ret->SetRot(rotation);
		_ret->SetPos(position);
		_ret->SetMass(mass);
		_ret->GetAssets().push_back(_box);

		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddBox(size.x, size.y, size.z);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(fixed);

		_ret.refresh();

		return _ret;
	}

	ECBody& ECScene::spawnCapsule(std::string Name) {

		ECBody& _ret = createBody(Name);

		return _ret;
	}

	ECBody& ECScene::spawnCone(std::string Name,
		double mass,
		chrono::ChVector<>& position,
		chrono::ChVector<>& size,
		chrono::ChQuaternion<>& rotation,
		bool fixed) {

		ECBody& _ret = createBody(Name);

		chrono::ChSharedPtr<chrono::ChConeShape> _cone(new chrono::ChConeShape);
		_cone->GetConeGeometry().rad = size;

		_ret->SetRot(rotation);
		_ret->SetPos(position);
		_ret->SetMass(mass);
		_ret->GetAssets().push_back(_cone);

		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddCone(size.x, size.z, size.y);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(fixed);

		_ret.refresh();

		return _ret;
	}

	ECBody& ECScene::spawnCylinder(std::string Name,
		double mass,
		chrono::ChVector<>& position,
		chrono::ChVector<>& size,
		chrono::ChQuaternion<>& rotation,
		bool fixed) {

		ECBody& _ret = createBody(Name);

		chrono::ChSharedPtr<chrono::ChCylinderShape> _cylinder(new chrono::ChCylinderShape);
		_cylinder->GetCylinderGeometry().rad = size.x;
		_cylinder->GetCylinderGeometry().p1 = chrono::ChVector<>(0, size.y, 0);
		_cylinder->GetCylinderGeometry().p2 = chrono::ChVector<>(0, 0, 0);

		_ret->SetRot(rotation);
		_ret->SetPos(position);
		_ret->SetMass(mass);
		_ret->GetAssets().push_back(_cylinder);

		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddCylinder(size.x, size.z, size.y);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(fixed);

		_ret.refresh();

		return _ret;
	}

	ECBody& ECScene::spawnEllipsoid(std::string Name,
		double mass,
		chrono::ChVector<>& position,
		chrono::ChVector<>& size,
		chrono::ChQuaternion<>& rotation,
		bool fixed) {

		ECBody& _ret = createBody(Name);

		chrono::ChSharedPtr<chrono::ChEllipsoidShape> _ellipsoid(new chrono::ChEllipsoidShape);
		_ellipsoid->GetEllipsoidGeometry().rad = size;

		_ret->SetRot(rotation);
		_ret->SetPos(position);
		_ret->SetMass(mass);
		_ret->GetAssets().push_back(_ellipsoid);

		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddEllipsoid(size.x, size.y, size.z);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(fixed);

		_ret.refresh();

		return _ret;
	}

	ECBody& ECScene::spawnSphere(std::string Name,
		double mass,
		chrono::ChVector<>& position,
		double radius,
		bool fixed) {

		ECBody& _ret = createBody(Name);

		chrono::ChSharedPtr<chrono::ChSphereShape> _sphere(new chrono::ChSphereShape);
		_sphere->GetSphereGeometry().rad = radius;

		_ret->SetPos(position);
		_ret->SetMass(mass);
		_ret->GetAssets().push_back(_sphere);

		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddSphere(radius);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(fixed);

		_ret.refresh();

		return _ret;
	}


	void ECScene::setLowerLimit(double limit) {
		m_LowerLimit = limit;
	}

	double ECScene::getLowerLimit() {
		return m_LowerLimit;
	}

}