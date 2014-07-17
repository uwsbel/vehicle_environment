#include <OGRE\Ogre.h>

#include <memory>
#include <exception>
//#include <thread>
//#include <chrono>
#include <vector>
#include <random>


namespace EnvironmentCore {

	class EnvironmentCoreApplication {
	public:

		EnvironmentCoreApplication();
		~EnvironmentCoreApplication();

		virtual int startLoop(int(*PerFrame)());
		virtual Ogre::RenderWindow* createWindow(Ogre::String Title, uint32_t Width, uint32_t Height, uint8_t FSAA_Level, bool VSync=false, bool Fullscreen=false);

		virtual void closeWindow();

	protected:

		Ogre::Root* m_pRoot;

		Ogre::RenderWindow* m_pRenderWindow;

	private:



	};

}