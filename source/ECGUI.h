#pragma once

#include "EC_SDL_InputManager.h"
#include <OGRE\Ogre.h>
#include <OGRE\OgrePrerequisites.h>
#include <OGRE\Overlay\OgreOverlay.h>
#include <OGRE\Overlay\OgreOverlayContainer.h>
#include <OGRE\Overlay\OgreOverlayManager.h>

namespace EnvironmentCore {

	class ECGUI {

	public:

		ECGUI();
		~ECGUI();

		virtual void setActive(bool Active);

		virtual void createPanel(std::string Name = "");

	protected:

		Ogre::Overlay* m_pOverlay;

	private:



	};

}