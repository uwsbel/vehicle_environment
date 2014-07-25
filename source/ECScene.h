/*
Author: Charles Ricchio

ECScene is designed to be a layer of abstraction from the Ogre lighting system, as well as a way of creating physics bodies for actual simulation
*/

#pragma once

#include <OGRE\Ogre.h>
#include <physics\ChSystem.h>

#include "ECBody.h"

namespace EnvironmentCore {

	class ECScene {

	public:

		ECScene(Ogre::SceneManager* SceneManager, chrono::ChSystem* System);
		~ECScene();

		////////
		//Lighting Abstration
		///////

		virtual void setAmbientLight(Ogre::ColourValue Color);
		virtual void setAmbientLight(float r, float g, float b);




		////////
		//Body Creation
		///////

		virtual ECBody& createBody();

		virtual void update();


	protected:

		Ogre::SceneManager* m_pSceneManager;

		chrono::ChSystem* m_pChSystem;


		////////
		//Body Management/Storage
		////////

		std::vector<ECBody*> m_ECBodies;

	private:



	};

}