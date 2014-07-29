/*
Author: Charles Ricchio

Contains the definitions for ECBody
*/


#include "ECBody.h"

namespace EnvironmentCore {

	ECBody::ECBody(Ogre::SceneManager* SceneManager, chrono::ChSystem* System) {
		m_pSceneManager = SceneManager;
		m_pChSystem = System;

		m_pBody = chrono::ChSharedBodyPtr(new chrono::ChBody);
		System->AddBody(m_pBody);

		name = "";
		deletable = true;
	}

	ECBody::~ECBody() {
		for (int i = 0; i < m_SceneNodes.size(); i++) {
			if (m_SceneNodes[i]) {
				m_pSceneManager->getRootSceneNode()->removeChild(m_SceneNodes[i]);
			}
		}
		m_pChSystem->RemoveBody(m_pBody);
	}

	void ECBody::update() {
		std::vector<chrono::ChSharedPtr<chrono::ChAsset> > l_pAssetList = m_pBody->GetAssets();
		for (int i = 0; i < l_pAssetList.size(); i++) {
			if (l_pAssetList[i].IsType<chrono::ChVisualization>()) {
				chrono::ChVector<> _pos = ((chrono::ChVisualization*)l_pAssetList[i].get_ptr())->Pos;
				m_SceneNodes[i]->setPosition((_pos.x + m_pBody->GetPos().x), (_pos.y + m_pBody->GetPos().y), (_pos.z) + m_pBody->GetPos().z);


				chrono::ChQuaternion<> l_q;

				chrono::ChBoxShape* shape = (chrono::ChBoxShape*)l_pAssetList[i].get_ptr();
				l_q = m_pBody->GetRot() % shape->Rot.Get_A_quaternion();
				l_q.Normalize();

				double __w = l_q.e0;
				double __x = l_q.e1;
				double __y = l_q.e2;
				double __z = l_q.e3;
				m_SceneNodes[i]->setOrientation(__w, __x, __y, __z);
			}
		}
	}

	void ECBody::refresh() {
		for (int i = 0; i < m_SceneNodes.size(); i++) {
			if (m_SceneNodes[i]) {
				m_pSceneManager->getRootSceneNode()->removeChild(m_SceneNodes[i]);
			}
		}
		for (int i = 0; i < m_pBody->GetAssets().size(); i++) {
			chrono::ChSharedPtr<chrono::ChAsset> temp_asset = m_pBody->GetAssets().at(i);

			Ogre::SceneNode* l_pNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
			Ogre::Entity* l_pEntity = nullptr;

			if (temp_asset.IsType<chrono::ChBoxShape>()) {
				l_pEntity = m_pSceneManager->createEntity("box.mesh");
				chrono::ChBoxShape* shape = (chrono::ChBoxShape*)temp_asset.get_ptr();
				double _w = shape->GetBoxGeometry().Size.x;
				double _h = shape->GetBoxGeometry().Size.y;
				double _d = shape->GetBoxGeometry().Size.z;
				l_pNode->setScale((Ogre::Real)_w, (Ogre::Real)_h, (Ogre::Real)_d);

			}
			else if (temp_asset.IsType<chrono::ChCapsuleShape>()) {
				
			}
			else if (temp_asset.IsType<chrono::ChConeShape>()) {
				l_pEntity = m_pSceneManager->createEntity("cone.mesh");
				chrono::ChConeShape* shape = (chrono::ChConeShape*)temp_asset.get_ptr();
				double _r1 = shape->GetConeGeometry().rad.x;
				double _r2 = shape->GetConeGeometry().rad.z;
				double _h = shape->GetConeGeometry().rad.y;
				l_pNode->setScale((Ogre::Real)_r1, (Ogre::Real)_h, (Ogre::Real)_r2);
			}
			else if (temp_asset.IsType<chrono::ChCylinderShape>()) {
				l_pEntity = m_pSceneManager->createEntity("cylinder.mesh");
				chrono::ChCylinderShape* shape = (chrono::ChCylinderShape*)temp_asset.get_ptr();

				double _r1 = shape->GetCylinderGeometry().rad;
				double _h = (shape->GetCylinderGeometry().p1 - shape->GetCylinderGeometry().p2).Length();
				l_pNode->setScale((Ogre::Real)_r1, (Ogre::Real)_h, (Ogre::Real)_r1);
			}
			else if (temp_asset.IsType<chrono::ChEllipsoidShape>()) {
				l_pEntity = m_pSceneManager->createEntity("sphere.mesh");
				chrono::ChEllipsoidShape* shape = (chrono::ChEllipsoidShape*)temp_asset.get_ptr();

				double _rx = shape->GetEllipsoidGeometry().rad.x;
				double _ry = shape->GetEllipsoidGeometry().rad.y;
				double _rz = shape->GetEllipsoidGeometry().rad.z;
				l_pNode->setScale((Ogre::Real)_rx, (Ogre::Real)_ry, (Ogre::Real)_rz);
			}
			else if (temp_asset.IsType<chrono::ChSphereShape>()) {
				l_pEntity = m_pSceneManager->createEntity("sphere.mesh");
				double _r = chrono::static_cast_chshared<chrono::ChSphereShape>(temp_asset)->GetSphereGeometry().rad;
				l_pNode->setScale((Ogre::Real)_r, (Ogre::Real)_r, (Ogre::Real)_r);
			}

			l_pNode->attachObject(l_pEntity);
			m_SceneNodes.push_back(l_pNode);
		}
	}

	chrono::ChSharedBodyPtr ECBody::getChBody() {
		return m_pBody;
	}

	chrono::ChSharedBodyPtr ECBody::operator-> () {
		return getChBody();
	}

}