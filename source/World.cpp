#include "World.h"
#include <assets\ChBoxShape.h>
#include <assets\ChCapsuleShape.h>
#include <assets\ChConeShape.h>
#include <assets\ChCylinderShape.h>
#include <assets\ChEllipsoidShape.h>
#include <assets\ChSphereShape.h>

namespace EnvironmentCore {

	World::World() {
		m_WorldTime = 0.0;
		m_TimeResolution = 0.01;
		setSceneManagerPtr(nullptr);
	}

	World::World(Ogre::SceneManager* SceneManagerPtr) {
		m_WorldTime = 0.0;
		m_TimeResolution = 0.01;
		setSceneManagerPtr(SceneManagerPtr);
	}

	World::~World() {
	}

	chrono::ChSharedPtr<Object> World::createObject() {
		chrono::ChSharedPtr<Object> _tObjectPtr(new Object);
		addObject(_tObjectPtr);
		return _tObjectPtr;
	}

	chrono::ChSharedPtr<Object> World::createObject(std::string Name) {
		chrono::ChSharedPtr<Object> _tObjectPtr = createObject();
		_tObjectPtr->setName(Name);
		return _tObjectPtr;
	}

	void World::setTimeResolution(double TimeResolution) {
		m_TimeResolution = TimeResolution;
	}

	void World::addObject(chrono::ChSharedPtr<Object> ObjectPtr) {
		m_Objects.push_back(ObjectPtr);
		
		std::vector<chrono::ChSharedPtr<chrono::ChAsset> > _tpAssetList = ObjectPtr->GetAssets();
		for (int i = 0; i < _tpAssetList.size(); i++) {
			if (_tpAssetList[i].IsType<chrono::ChBoxShape>()) {
				ObjectPtr->loadMesh(Object::BOX);
			}
			else if (_tpAssetList[i].IsType<chrono::ChCapsuleShape>()) {
				ObjectPtr->loadMesh(Object::CAPSULE);
			}
			else if (_tpAssetList[i].IsType<chrono::ChConeShape>()) {
				ObjectPtr->loadMesh(Object::CONE);
			}
			else if (_tpAssetList[i].IsType<chrono::ChCylinderShape>()) {
				ObjectPtr->loadMesh(Object::CONE);
			}
			else if (_tpAssetList[i].IsType<chrono::ChEllipsoidShape>()) {
				ObjectPtr->loadMesh(Object::CONE);
			}
			else if (_tpAssetList[i].IsType<chrono::ChSphereShape>()) {
				ObjectPtr->loadMesh(Object::SPHERE);
			}
		}
	}

	void World::removeObject(std::string Name) {
		for (int i = 0; i < m_Objects.size(); i++) {
			if (m_Objects[i]->getName() == Name) {
				m_System.RemoveBody(m_Objects[i]);
				m_Objects[i] = m_Objects.back();
				m_Objects.pop_back();
			}
		}
	}

	void World::removeObject(chrono::ChSharedPtr<Object> ObjectPtr) {
		for (int i = 0; i < m_Objects.size(); i++) {
			if (m_Objects[i] == ObjectPtr) {
				m_System.RemoveBody(m_Objects[i]);
				m_Objects[i] = m_Objects.back();
				m_Objects.pop_back();
			}
		}
	}

	void World::setSceneManagerPtr(Ogre::SceneManager* SceneManagerPtr) {
		m_pSceneManager = SceneManagerPtr;
	}

	void World::Update() {
		m_WorldTime += m_TimeResolution;

		for (int i = 0; i < m_Objects.size(); i++) {
			if (m_Objects[i] != nullptr) {
				m_Objects[i]->UpdateNodes();
			}
		}

		m_System.DoFrameDynamics(m_WorldTime);
	}


	bool World::getObject(std::string Name, chrono::ChSharedPtr<Object>& out_ObjectPtr) {
		
		for (int i = 0; i < m_Objects.size(); i++) {
			if (m_Objects[i]->getName() == Name) {
				out_ObjectPtr = m_Objects[i];
				return true;
			}
		}
		return false;
	}

	double World::getWorldTime() {
		return m_WorldTime;
	}

	double World::getTimeResolution() {
		return m_TimeResolution;
	}

	chrono::ChSystem* World::getChronoSystemPtr() {
		return &m_System;
	}

	Ogre::SceneManager* World::getSceneManagerPtr() {
		return m_pSceneManager;
	}
}