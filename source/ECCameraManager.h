/*
Author: Charles Ricchio

Contains a managment class for easy manipulation of the camera. ECCameraManager doesn't actually manage any Ogre camera objects, 
but instead retains points in space and points to orient to in space for easy access for the actual camera object within ECApplication.
*/

#pragma once

#include <OGRE\Ogre.h>
#include <vector>

namespace EnvironmentCore {

	typedef struct ECCamera_t {
		float x, y, z;
		float wx, wy, wz;
		std::string name;

		void orient(float _x, float _y, float _z, float _wx, float _wy, float _wz) {
			x = _x;
			y = _y;
			z = _z;
			wx = _wx;
			wy = _wy;
			wz = _wz;
		}

		void operator() (float _x, float _y, float _z, float _wx, float _wy, float _wz) {
			orient(_x, _y, _z, _wx, _wy, _wz);
		}
	} ECCamera;

	class ECCameraManager {

	public:

		ECCameraManager();
		~ECCameraManager();

		virtual ECCamera* createCamera(std::string Name=( "Camera" + std::to_string( g_CameraCount ) ) );

		virtual ECCamera* getCamera(unsigned int iterator);

		virtual ECCamera* getCamera(std::string Name);

		virtual ECCamera* operator[] (unsigned int iterator);

		virtual ECCamera* operator[] (std::string Name);

	protected:

		std::vector<ECCamera*> m_CameraList;

		static unsigned int g_CameraCount;
	private:

	};

}