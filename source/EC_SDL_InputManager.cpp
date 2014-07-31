#if defined(_WIN32) || defined(WIN32)

#include <windows.h>

#endif

#include <string>
#include <climits>
#include "EC_SDL_InputManager.h"

#define INPUT_DEADZONE  ( ( 0.26 * (double)(0x7FFF) ) / (double)(SHRT_MAX) )

namespace EnvironmentCore {

	EC_SDL_InputManager::EC_SDL_InputManager(Ogre::RenderWindow* renderWindow) {

		if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_HAPTIC) != 0) {
			Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "\n\nCould not initialize SDL: " + std::string(SDL_GetError()) + "\n\n");
		}

#if defined(_WIN32) || defined(WIN32)

		HWND windowHnd = 0;

		// Get window handle
		renderWindow->getCustomAttribute("WINDOW", &windowHnd);

		m_pSDLWindow = SDL_CreateWindowFrom(windowHnd);

#endif

		if (m_pSDLWindow == nullptr) {
			Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "\n\nCould make SDL window: " + std::string(SDL_GetError()) + "\n\n");
		}

		m_pController = nullptr;

		int _nJoysticks = SDL_NumJoysticks();

		for (int i = 0; i < SDL_NumJoysticks(); ++i) {
			m_pController = SDL_JoystickOpen(i);
			if (m_pController) {
				break;
			}
			else {
				Ogre::LogManager::getSingleton().logMessage(Ogre::LML_CRITICAL, "Could not open gamecontroller " + std::to_string(i) + ": " + std::string(SDL_GetError()) + "\n");
			}
		}

		AxisThreshold = INPUT_DEADZONE;

	}

	EC_SDL_InputManager::~EC_SDL_InputManager() {

		SDL_Quit();

	}

	void EC_SDL_InputManager::update() {

		SDL_Event _event;
		while (SDL_PollEvent(&_event)) {
			if (_event.type == SDL_KEYDOWN) {
				m_KeyStates_scancode[_event.key.keysym.scancode].down = true;
				m_KeyStates_scancode[_event.key.keysym.scancode].timestamp = (double)(_event.key.timestamp) / 1000.0;
				m_KeyStates_keycode[_event.key.keysym.sym].down = true;
				m_KeyStates_keycode[_event.key.keysym.sym].timestamp = (double)(_event.key.timestamp) / 1000.0;
#ifdef _DEBUG
				Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Key press ; Scanecode: " + std::to_string(_event.key.keysym.scancode) + " Keycode: " + std::to_string(_event.key.keysym.sym) + "\n");
#endif
			}
			else if (_event.type == SDL_KEYUP) {
				m_KeyStates_scancode[_event.key.keysym.scancode].down = false;
				m_KeyStates_scancode[_event.key.keysym.scancode].timestamp = (double)(_event.key.timestamp) / 1000.0;
				m_KeyStates_keycode[_event.key.keysym.sym].down = false;
				m_KeyStates_keycode[_event.key.keysym.sym].timestamp = (double)(_event.key.timestamp) / 1000.0;
#ifdef _DEBUG
				Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Key release ; Scanecode: " + std::to_string(_event.key.keysym.scancode) + " Keycode: " + std::to_string(_event.key.keysym.sym) + "\n");
#endif
			}
			else if (_event.type == SDL_MOUSEBUTTONDOWN) {
				switch (_event.button.button) {
				case SDL_BUTTON_LEFT: m_MouseState.left.down = true; m_MouseState.left.timestamp = (double)(_event.button.timestamp) / 1000.0; break;
				case SDL_BUTTON_RIGHT: m_MouseState.right.down = true; m_MouseState.right.timestamp = (double)(_event.button.timestamp) / 1000.0; break;
				case SDL_BUTTON_MIDDLE: m_MouseState.middle.down = true; m_MouseState.middle.timestamp = (double)(_event.button.timestamp) / 1000.0; break;
				case SDL_BUTTON_X1: m_MouseState.x1.down = true; m_MouseState.x1.timestamp = (double)(_event.button.timestamp) / 1000.0; break;
				case SDL_BUTTON_X2: m_MouseState.x2.down = true; m_MouseState.x2.timestamp = (double)(_event.button.timestamp) / 1000.0; break;
				}
			}
			else if (_event.type == SDL_MOUSEBUTTONUP) {
				switch (_event.button.button) {
				case SDL_BUTTON_LEFT: m_MouseState.left.down = false; m_MouseState.left.timestamp = (double)(_event.button.timestamp) / 1000.0; break;
				case SDL_BUTTON_RIGHT: m_MouseState.right.down = false; m_MouseState.right.timestamp = (double)(_event.button.timestamp) / 1000.0; break;
				case SDL_BUTTON_MIDDLE: m_MouseState.middle.down = false; m_MouseState.middle.timestamp = (double)(_event.button.timestamp) / 1000.0; break;
				case SDL_BUTTON_X1: m_MouseState.x1.down = false; m_MouseState.x1.timestamp = (double)(_event.button.timestamp) / 1000.0; break;
				case SDL_BUTTON_X2: m_MouseState.x2.down = false; m_MouseState.x2.timestamp = (double)(_event.button.timestamp) / 1000.0; break;
				}
			}
			else if (_event.type == SDL_MOUSEMOTION) {
				m_MouseState.position.timestamp = (double)(_event.motion.timestamp) / 1000.0;

				m_MouseState.position.x = (double)(_event.motion.x) / (double)INT_MAX;
				m_MouseState.position.y = (double)(_event.motion.y) / (double)INT_MAX;
				m_MouseState.position.xrel = (double)(_event.motion.xrel) / (double)INT_MAX;
				m_MouseState.position.yrel = (double)(_event.motion.yrel) / (double)INT_MAX;

				if (_event.motion.state & SDL_BUTTON_LMASK) {
					m_MouseState.left.down = true;
				}
				else {
					m_MouseState.left.down = false;
				}

				if (_event.motion.state & SDL_BUTTON_RMASK) {
					m_MouseState.right.down = true;
				}
				else {
					m_MouseState.right.down = false;
				}

				if (_event.motion.state & SDL_BUTTON_MMASK) {
					m_MouseState.middle.down = true;
				}
				else {
					m_MouseState.middle.down = false;
				}

				if (_event.motion.state & SDL_BUTTON_X1MASK) {
					m_MouseState.x1.down = true;
				}
				else {
					m_MouseState.x1.down = false;
				}

				if (_event.motion.state & SDL_BUTTON_X2MASK) {
					m_MouseState.x2.down = true;
				}
				else {
					m_MouseState.x2.down = false;
				}

			}
			else if (_event.type == SDL_MOUSEWHEEL) {
				m_MouseState.wheel.timestamp = (double)(_event.wheel.timestamp) / 1000.0;
				m_MouseState.wheel.x = (double)(_event.wheel.x) / (double)INT_MAX;
				m_MouseState.wheel.y = (double)(_event.wheel.y) / (double)INT_MAX;
			}
			else if (_event.type == SDL_JOYAXISMOTION) {

				if (std::abs(((double)_event.jaxis.value / (double)SHRT_MAX)) > AxisThreshold ) {

					switch (_event.jaxis.axis) {
					case 0: m_ControllerState.lstickx.value = ((double)_event.jaxis.value / (double)SHRT_MAX); m_ControllerState.lstickx.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					case 1: m_ControllerState.lsticky.value = ((double)_event.jaxis.value / (double)SHRT_MAX); m_ControllerState.lsticky.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					case 2: m_ControllerState.rstickx.value = ((double)_event.jaxis.value / (double)SHRT_MAX); m_ControllerState.rstickx.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					case 3: m_ControllerState.rsticky.value = ((double)_event.jaxis.value / (double)SHRT_MAX); m_ControllerState.rsticky.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					case 4: m_ControllerState.ltrigger.value = ((double)_event.jaxis.value / (double)SHRT_MAX); m_ControllerState.ltrigger.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					case 5: m_ControllerState.rtrigger.value = ((double)_event.jaxis.value / (double)SHRT_MAX); m_ControllerState.rtrigger.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					}

				}
				else {

					switch (_event.jaxis.axis) {
					case 0: m_ControllerState.lstickx.value = 0; m_ControllerState.lstickx.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					case 1: m_ControllerState.lsticky.value = 0; m_ControllerState.lsticky.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					case 2: m_ControllerState.rstickx.value = 0; m_ControllerState.rstickx.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					case 3: m_ControllerState.rsticky.value = 0; m_ControllerState.rsticky.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					case 4: m_ControllerState.ltrigger.value = 0; m_ControllerState.ltrigger.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					case 5: m_ControllerState.rtrigger.value = 0; m_ControllerState.rtrigger.timestamp = (double)(_event.jaxis.timestamp) / 1000.0; break;
					}

				}

#ifdef _DEBUG
				if (((((double)_event.jaxis.value) / ((double)SHRT_MAX)) > INPUT_DEADZONE) || ((((double)_event.jaxis.value) / ((double)SHRT_MAX)) < -(INPUT_DEADZONE))) {
					Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Controller axis motion - Axis:" + std::to_string(_event.jaxis.axis) + "\n");
				}
#endif
			}
			else if (_event.type == SDL_JOYBUTTONDOWN) {

				switch (_event.jbutton.button) {
				case 0: m_ControllerState.d_up.down = true; m_ControllerState.d_up.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 1: m_ControllerState.d_down.down = true; m_ControllerState.d_down.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 2: m_ControllerState.d_left.down = true; m_ControllerState.d_left.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 3: m_ControllerState.d_right.down = true; m_ControllerState.d_right.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 4: m_ControllerState.start.down = true; m_ControllerState.start.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 5: m_ControllerState.back.down = true; m_ControllerState.back.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 6: m_ControllerState.lstick.down = true; m_ControllerState.lstick.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 7: m_ControllerState.rstick.down = true; m_ControllerState.rstick.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 8: m_ControllerState.lbumper.down = true; m_ControllerState.lbumper.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 9: m_ControllerState.rbumper.down = true; m_ControllerState.rbumper.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 10: m_ControllerState.a.down = true; m_ControllerState.a.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 11: m_ControllerState.b.down = true; m_ControllerState.b.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 12: m_ControllerState.x.down = true; m_ControllerState.x.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 13: m_ControllerState.y.down = true; m_ControllerState.y.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				}

#ifdef _DEBUG
				Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Controller button press - Button:" + std::to_string(_event.jbutton.button) + "\n");
#endif
			}
			else if (_event.type == SDL_JOYBUTTONUP) {

				switch (_event.jbutton.button) {
				case 0: m_ControllerState.d_up.down = false; m_ControllerState.d_up.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 1: m_ControllerState.d_down.down = false; m_ControllerState.d_down.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 2: m_ControllerState.d_left.down = false; m_ControllerState.d_left.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 3: m_ControllerState.d_right.down = false; m_ControllerState.d_right.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 4: m_ControllerState.start.down = false; m_ControllerState.start.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 5: m_ControllerState.back.down = false; m_ControllerState.back.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 6: m_ControllerState.lstick.down = false; m_ControllerState.lstick.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 7: m_ControllerState.rstick.down = false; m_ControllerState.rstick.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 8: m_ControllerState.lbumper.down = false; m_ControllerState.lbumper.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 9: m_ControllerState.rbumper.down = false; m_ControllerState.rbumper.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 10: m_ControllerState.a.down = false; m_ControllerState.a.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 11: m_ControllerState.b.down = false; m_ControllerState.b.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 12: m_ControllerState.x.down = false; m_ControllerState.x.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				case 13: m_ControllerState.y.down = false; m_ControllerState.y.timestamp = (double)(_event.jbutton.timestamp) / 1000.0; break;
				}

#ifdef _DEBUG
				Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Controller button release - Button:" + std::to_string(_event.jbutton.button) + "\n");
#endif
			}
			else if (_event.type == SDL_JOYDEVICEADDED) {
				if (_event.jdevice.which == 0) {
					if (m_pController) {
						SDL_JoystickClose(m_pController);
						m_pController = nullptr;
					}
					m_pController = SDL_JoystickOpen(0);
				}
			}
			else if (_event.type == SDL_JOYDEVICEREMOVED) {
				if (_event.jdevice.which == 0) {
					if (m_pController) {
						SDL_JoystickClose(m_pController);
						m_pController = nullptr;
					}
				}
			}
		}
	}

	void EC_SDL_InputManager::grabMouse(bool grab) {
		if (grab) {
			SDL_SetWindowGrab(m_pSDLWindow, SDL_TRUE);
		}
		else {
			SDL_SetWindowGrab(m_pSDLWindow, SDL_FALSE);
		}
	}

	ECKeyState& EC_SDL_InputManager::getKeyState(SDL_Scancode scancode) {
		return m_KeyStates_scancode[scancode];
	}

	ECKeyState& EC_SDL_InputManager::getKeyState(SDL_Keycode keycode) {
		return m_KeyStates_keycode[keycode];
	}

	ECMouseState& EC_SDL_InputManager::getMouseState() {
		return m_MouseState;
	}

	ECControllerState& EC_SDL_InputManager::getControllerState() {
		return m_ControllerState;
	}

}