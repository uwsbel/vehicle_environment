#if defined(_WIN32) || defined(WIN32)

#include <windows.h>

#endif

#include <string>
#include "EC_SDL_InputManager.h"

namespace EnvironmentCore {

	EC_SDL_InputManager::EC_SDL_InputManager(Ogre::RenderWindow* renderWindow) {

		if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO) != 0) {
			Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "\n\nCould not initialize SDL: " + std::string(SDL_GetError()) + "\n\n");
		}

#if defined(_WIN32) || defined(WIN32)

		HWND windowHnd = 0;

		// Get window handle
		renderWindow->getCustomAttribute("WINDOW", &windowHnd);

		m_pSDLWindow = SDL_CreateWindowFrom(windowHnd);

		if (m_pSDLWindow == nullptr) {
			Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "\n\nCould make SDL window: " + std::string(SDL_GetError()) + "\n\n");
		}

#endif



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
				Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Key press ; Scanecode: " + std::to_string(_event.key.keysym.scancode) + " Keycode: " + std::to_string(_event.key.keysym.sym));
#endif
			}
			else if (_event.type == SDL_KEYUP) {
				m_KeyStates_scancode[_event.key.keysym.scancode].down = false;
				m_KeyStates_scancode[_event.key.keysym.scancode].timestamp = (double)(_event.key.timestamp) / 1000.0;
				m_KeyStates_keycode[_event.key.keysym.sym].down = false;
				m_KeyStates_keycode[_event.key.keysym.sym].timestamp = (double)(_event.key.timestamp) / 1000.0;
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

}