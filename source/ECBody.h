#pragma once

#include <vector>

#include <OGRE\Ogre.h>

#include <physics\ChSystem.h>
#include <physics\ChBody.h>
#include <assets\ChVisualization.h>
#include <assets\ChBoxShape.h>
#include <assets\ChCapsuleShape.h>
#include <assets\ChConeShape.h>
#include <assets\ChCylinderShape.h>
#include <assets\ChEllipsoidShape.h>
#include <assets\ChRoundedBoxShape.h>
#include <assets\ChRoundedConeShape.h>
#include <assets\ChRoundedCylinderShape.h>
#include <assets\ChSphereShape.h>
#include <assets\ChTriangleMeshShape.h>

namespace EnvironmentCore {

	class ECBody {

	public:

		ECBody(Ogre::SceneManager* SceneManager, chrono::ChSystem* System);
		~ECBody();

		virtual void update();
		virtual void refresh();

		virtual chrono::ChSharedBodyPtr getChBody();

	protected:

		chrono::ChSharedBodyPtr m_pBody;

		std::vector<Ogre::SceneNode*> m_SceneNodes;

		Ogre::SceneManager* m_pSceneManager;
		chrono::ChSystem* m_pChSystem;

	private:



	};

}