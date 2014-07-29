/*
Author: Charles Ricchio

An input manager based on SDL, as opposed to OIS. Will handle keyboard, mouse, and joystick input.
*/

#pragma once

#include <OGRE\Ogre.h>
#include <SDL.h>

#include <map>

namespace EnvironmentCore {

	typedef struct ECKeyState_t {

		bool down;
		double timestamp;

	} ECKeyState;

	typedef struct ECMouseState_t {

		ECKeyState left;
		ECKeyState right;
		ECKeyState middle;
		ECKeyState x1;
		ECKeyState x2;

		double x, y;

	} ECMouseState;;

	class EC_SDL_InputManager {

	public:

		EC_SDL_InputManager(Ogre::RenderWindow* renderWindow);
		~EC_SDL_InputManager();

		virtual void update();

		virtual void grabMouse(bool grab);

		virtual ECKeyState& getKeyState(SDL_Scancode scancode);
		virtual ECKeyState& getKeyState(SDL_Keycode keycode);

		virtual ECMouseState& getMouseState();

	protected:

		SDL_Window* m_pSDLWindow;

		std::map<SDL_Scancode, ECKeyState> m_KeyStates_scancode;
		std::map<SDL_Keycode, ECKeyState> m_KeyStates_keycode;

		ECMouseState m_MouseState;

	private:



	};

}