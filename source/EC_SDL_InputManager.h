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

		typedef struct __posState_t {
			double x, y;
			double xrel, yrel;
			double timestamp;
		} __posState;

		__posState position;

		typedef struct __wheelState_t {
			double x, y;
			double timestamp;
		} __wheelState;

		__wheelState wheel;

	} ECMouseState;

	typedef struct ECControllerState_t {

		typedef struct __axisState_t {
			double value;
			double timestamp;
		} __axisState;

		__axisState lstickx, lsticky;
		__axisState rstickx, rsticky;
		__axisState ltrigger, rtrigger;

		ECKeyState a, b, x, y;
		ECKeyState back, start;
		ECKeyState lstick, rstick;
		ECKeyState d_left, d_right, d_up, d_down;
		ECKeyState lbumper, rbumper;

	} ECControllerState;



	class EC_SDL_InputManager {

	public:

		EC_SDL_InputManager(Ogre::RenderWindow* renderWindow);
		~EC_SDL_InputManager();

		virtual void update();

		virtual void grabMouse(bool grab);

		virtual ECKeyState& getKeyState(SDL_Scancode scancode);
		virtual ECKeyState& getKeyState(SDL_Keycode keycode);

		virtual ECMouseState& getMouseState();

		virtual ECControllerState& getControllerState();

		double AxisThreshold;

	protected:

		SDL_Window* m_pSDLWindow;

		std::map<SDL_Scancode, ECKeyState> m_KeyStates_scancode;
		std::map<SDL_Keycode, ECKeyState> m_KeyStates_keycode;

		ECMouseState m_MouseState;
		ECControllerState m_ControllerState;
		
		SDL_Joystick* m_pController;

	private:



	};

}