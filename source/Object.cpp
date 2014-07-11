#include "Object.h"

namespace EnvironmentCore {

	Object::Object() {
		setName("");
		setSceneManager(nullptr);
	}

	Object::Object(std::string Name) {
		setName(Name);
		setSceneManager(nullptr);
	}

	Object::~Object() {
	}

	void Object::setSceneManager(Ogre::SceneManager* SceneManagerPtr) {
		m_pSceneManager = SceneManagerPtr;
	}

	void Object::setName(std::string Name) {
		m_Name = Name;
	}

	void Object::UpdateNodes() {
		std::vector<chrono::ChSharedPtr<chrono::ChAsset> > _tpAssetList = GetAssets();
		for (int i = 0; i < _tpAssetList.size(); i++) {
			if (_tpAssetList[i].IsType<chrono::ChVisualization>()) {
				chrono::ChVector<> _pos = ((chrono::ChVisualization*)_tpAssetList[i].get_ptr())->Pos;
				m_SceneNodes[i]->setPosition(_pos.x, _pos.y, _pos.z);
			}
		}
		Update();
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string Object::getName() {
		return m_Name;
	}

	Ogre::SceneNode* Object::getMesh(std::string Name) {
		for (int i = 0; i < m_SceneNodes.size(); i++) {
			if (m_SceneNodes[i]->getName() == Name) {
				return m_SceneNodes[i];
			}
		}
	}

	Ogre::SceneManager* Object::getSceneManagerPtr() {
		return m_pSceneManager;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void Object::loadMesh(assettypes_t AssetType) {
		std::string _tName;
		Ogre::SceneNode* _tpSceneNode;
		Ogre::Entity* _tpEntity;
		switch (AssetType) {
		case BOX: {
			_tName = "box"+std::to_string((long long)m_SceneNodes.size());
			_tpSceneNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(_tName);
			_tpEntity = m_pSceneManager->createEntity(_tName, "assets/models/box.obj");
				  }; break;
		case CAPSULE: {
			_tName = "capsule"+std::to_string((long long)m_SceneNodes.size());
			_tpSceneNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(_tName);
			_tpEntity = m_pSceneManager->createEntity(_tName, "assets/models/capsule.obj");
			  }; break;
		case CONE: {
			_tName = "cone"+std::to_string((long long)m_SceneNodes.size());
			_tpSceneNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(_tName);
			_tpEntity = m_pSceneManager->createEntity(_tName, "assets/models/cone.obj");
				   }; break;
		case CYLINDER: {
			_tName = "cylinder"+std::to_string((long long)m_SceneNodes.size());
			_tpSceneNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(_tName);
			_tpEntity = m_pSceneManager->createEntity(_tName, "assets/models/cylinder.obj");
					   }; break;
		case ELLIPSOID: {
			_tName = "ellipsoid"+std::to_string((long long)m_SceneNodes.size());
			_tpSceneNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(_tName);
			_tpEntity = m_pSceneManager->createEntity(_tName, "assets/models/ellipsoid.obj");
						}; break;
		case SPHERE: {
			_tName = "sphere"+std::to_string((long long)m_SceneNodes.size());
			_tpSceneNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(_tName);
			_tpEntity = m_pSceneManager->createEntity(_tName, "assets/models/sphere.obj");
					 }; break;
		}

		_tpSceneNode->attachObject(_tpEntity);

		m_SceneNodes.push_back(_tpSceneNode);
	}

	void Object::removeMesh(Ogre::SceneNode* NodePtr) {
		for (int i = 0; i < m_SceneNodes.size(); i++) {
			if (m_SceneNodes[i] == NodePtr) {
				m_pSceneManager->getRootSceneNode()->removeChild(NodePtr);
				m_SceneNodes[i] = m_SceneNodes.back();
				m_SceneNodes.pop_back();
			}
		}
	}

}