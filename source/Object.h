#pragma once

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreLogManager.h>

#include <physics\CHsystem.h>
#include <physics\CHbody.h>
#include <assets\ChVisualization.h>

#include <vector>
#include <string>

namespace EnvironmentCore {

	class Object : public chrono::ChBody {

	public:
		Object();
		Object(std::string Name);
		~Object();
		
		enum assettypes_t { CONE, SPHERE, CYLINDER, BOX, CAPSULE, ELLIPSOID };

		virtual void setSceneManager(Ogre::SceneManager* SceneManager);
		virtual void setName(std::string Name);
		virtual void UpdateNodes();
		virtual void loadMesh(assettypes_t AssetType);
		virtual void removeMesh(Ogre::SceneNode* NodePtr);

		virtual std::string getName();
		virtual Ogre::SceneNode* getMesh(std::string Name);
		virtual Ogre::SceneManager* getSceneManagerPtr();

	protected:

		Ogre::SceneManager* m_pSceneManager;

		std::vector<Ogre::SceneNode*> m_SceneNodes;

		std::string m_Name;

	private:
	};

}