cmake_minimum_required(VERSION 2.8)
project(vehicle_environment)
#set path for local find modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" "C:/Ogre/OgreSDK_vc10_v1-9-0/CMake")
include(cmake/SBELUtils.cmake)
#enable_openmp_support()
find_package(OGRE REQUIRED)
# User specified path to ChronoEngine
SET(CHRONO_INC           ""    CACHE   PATH    "Where is ChronoEngine Source located")
# User specified path to ChronoEngine Libraries
SET(CHRONO_LIB_PATH           ""   CACHE    PATH    "Where is ChronoEngine Lib located")
# Find required Libraries
FIND_LIBRARY(CHRONO_LIB NAMES ChronoEngine PATHS ${CHRONO_LIB_PATH} REQUIRED)

SET(LIBRARIES ${CHRONO_LIB} ${OGRE_LIBRARY_DBG} ${Boost_THREAD_LIBRARY_DEBUG})

include_directories(
    ${CHRONO_INC}
	${OGRE_INCLUDE_DIR}
	${Boost_INCLUDE_DIR}
    "${CHRONO_INC}/collision" 
    "${CHRONO_INC}/collision/bullet" 
    )
	SET(SOURCES source/main.cpp source/ECApplication.cpp source/ECApplication.h )
	ADD_EXECUTABLE(vehicle_environment ${SOURCES} )
	TARGET_LINK_LIBRARIES(vehicle_environment	${LIBRARIES})