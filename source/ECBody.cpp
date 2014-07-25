
#include "ECBody.h"

namespace EnvironmentCore {

	ECBody::ECBody(Ogre::SceneManager* SceneManager, chrono::ChSystem* System) {
		m_pSceneManager = SceneManager;
		m_pChSystem = System;

		m_pBody = chrono::ChSharedBodyPtr(new chrono::ChBody);
		System->AddBody(m_pBody);
	}

	ECBody::~ECBody() {
		for (int i = 0; i < m_SceneNodes.size(); i++) {
			if (m_SceneNodes[i]) {
				m_pSceneManager->getRootSceneNode()->removeChild(m_SceneNodes[i]);
			}
		}
	}

	void ECBody::update() {
		std::vector<chrono::ChSharedPtr<chrono::ChAsset> > l_pAssetList = m_pBody->GetAssets();
		for (int i = 0; i < l_pAssetList.size(); i++) {
			if (l_pAssetList[i].IsType<chrono::ChVisualization>()) {
				chrono::ChVector<> _pos = ((chrono::ChVisualization*)l_pAssetList[i].get_ptr())->Pos;
				m_SceneNodes[i]->setPosition((_pos.x + m_pBody->GetPos().x), (_pos.y + m_pBody->GetPos().y), (_pos.z) + m_pBody->GetPos().z);
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
				l_pEntity = m_pSceneManager->createEntity("ninja.mesh");
			}
			else if (temp_asset.IsType<chrono::ChCapsuleShape>()) {
				
			}
			else if (temp_asset.IsType<chrono::ChConeShape>()) {
				
			}
			else if (temp_asset.IsType<chrono::ChCylinderShape>()) {
				
			}
			else if (temp_asset.IsType<chrono::ChEllipsoidShape>()) {
				
			}
			else if (temp_asset.IsType<chrono::ChSphereShape>()) {
				l_pEntity = m_pSceneManager->createEntity("ninja.mesh");
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