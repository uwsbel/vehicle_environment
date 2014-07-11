#pragma once

#include "Object.h"

namespace EnvironmentCore {

	class World {
	public:
		World();
		World(Ogre::SceneManager* SceneManagerPtr);
		~World();

		virtual chrono::ChSharedPtr<Object> createObject();
		virtual chrono::ChSharedPtr<Object> createObject(std::string Name);
		virtual void setTimeResolution(double Resolution);
		virtual void addObject(chrono::ChSharedPtr<Object> ObjectPtr);
		virtual void removeObject(std::string Name);
		virtual void removeObject(chrono::ChSharedPtr<Object> ObjectPtr);
		virtual void setSceneManagerPtr(Ogre::SceneManager* SceneManagerPtr);
		virtual void Update();

		virtual bool getObject(std::string Name, chrono::ChSharedPtr<Object>& out_ObjectPtr);
		virtual double getWorldTime();
		virtual double getTimeResolution();
		virtual chrono::ChSystem* getChronoSystemPtr();
		virtual Ogre::SceneManager* getSceneManagerPtr();
	protected:
		std::vector<chrono::ChSharedPtr<Object> > m_Objects;

		double m_WorldTime;
		double m_TimeResolution;

		chrono::ChSystem m_System;
		Ogre::SceneManager* m_pSceneManager;
	private:
	};

}