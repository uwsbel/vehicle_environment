cmake_minimum_required(VERSION 2.8)
project(ChOgre)
#set path for local find modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(cmake/SBELUtils.cmake)
#enable_openmp_support()
find_package(OGRE REQUIRED)
find_package(CHRONO REQUIRED)
find_package(SDL REQUIRED)
# User specified path to ChronoEngine
#SET(CHRONO_INC           ""    CACHE   PATH    "Where is ChronoEngine Source located")
# User specified path to ChronoEngine Libraries
#SET(CHRONO_LIB_PATH           ""   CACHE    PATH    "Where is ChronoEngine Lib located")
# Find required Libraries
#FIND_LIBRARY(CHRONO_LIB NAMES ChronoEngine PATHS ${CHRONO_LIB_PATH} REQUIRED)

SET(LIBRARIES ${CHRONOENGINE_LIBRARIES} ${OGRE_LIBRARIES} ${SDL_LIBRARY})

include_directories(
    ${CHRONOENGINE_INCLUDES}
	${OGRE_INCLUDE_DIRS}
	${SDL_INCLUDE_DIR}
    "${CHRONOENGINE_INCLUDES}/collision" 
    "${CHRONOENGINE_INCLUDES}/collision/bullet" 
    )
	
ADD_SUBDIRECTORY(source/ChOgre)
ADD_SUBDIRECTORY(source/demo_vehicle)