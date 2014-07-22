/*
Author: Charles Ricchio

ECScene is designed to be a layer of abstraction from the Ogre lighting system, as well as a way of creating physics bodies for actual simulation
*/

#pragma once

#include <OGRE\Ogre.h>

namespace EnvironmentCore {

	class ECScene {

	public:

		ECScene(Ogre::SceneManager* SceneManager);
		~ECScene();

		////////
		//Lighting Abstration
		///////

		virtual void setAmbientLight(Ogre::ColourValue Color);
		virtual void setAmbientLight(float r, float g, float b);




		////////
		//Body Creation
		///////



		////////
		//Body Management/Storage
		////////




	protected:

		Ogre::SceneManager* m_pSceneManager;

	private:



	};

}