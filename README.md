vehicle_environment
===================




Dependencies
============

EnvironmentCore depends on Chrono, Ogre and SDL. This usually wouldn't be too tricky to setup, but the code is written in C++11, which causes problems
with Ogre. In order to build Ogre so it can be used with Visual Studio 2013, you need to

1. Clone the Ogredeps repository at https://bitbucket.org/cabalistic/ogredeps
2. Install the DirectX June 2010 SDK at http://www.microsoft.com/en-us/download/details.aspx?id=6812
3. Configure the Ogredeps CMake for Visual Studio 2013
4. Build and install it, and then rename the install folder to "Dependencies"
5. Clone the Ogre repository at https://bitbucket.org/sinbad/ogre/src/4578da5bf5b00fdf023b87e98099d647c5cb92ab?at=v1-9-0
6. Copy the "Dependencies" folder from before into the build directory you made for Ogre in CMake
7. Configure Ogre, build it, and then install it. All headers, libraries, and DLLs will be in the "sdk" folder in the build directory

For SDL, you can download development libraries at https://www.libsdl.org/download-2.0.php
For Chrono, you can get the repository at https://github.com/projectchrono/chrono