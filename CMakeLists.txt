#/* 
#-----------------------------------------------------------------------------
#Filename:    tau/CMakeLists.txt
#-----------------------------------------------------------------------------
# CMake file for tau project
# Builds a static library (libtau.a) in either Debug/ or Release/
# Also builds two test executables:
#    simpleTest  - simple sanity for ability to link to boost unit tests
#    testTauOde  - main check of Tau functionality
#
#-----------------------------------------------------------------------------
#*/

cmake_minimum_required(VERSION 2.6.2)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(PROJECT_NAME "tau")
project(${PROJECT_NAME})

SET(PROJECT_VERSION 0.1 CACHE STRING "Tau Version Number")

#SET (CMAKE_MODULE_PATH "/usr/local/share/cmake/Modules")

set(Tau_SRC
    src/OdeRobot.cpp
    src/TauRobot.cpp
    src/robot.cpp
    src/tau.cpp
)

set(Tau_SimpleTest_SRC
    src/test/simpleTest.cpp
)

set(Tau_Test_SRC
    src/test/testTau.cpp
)

#####################################################################
# BOOST
#####################################################################
# Uses FindBoost.cmake, which has been buggy in the past.
# May need to place a new version into the project 
# directory (alongside this CMakeLists.txt)
# http://code.google.com/p/opennero/source/browse/trunk/cmake/FindBoost.cmake
#
#FIND_PACKAGE( Boost 1.40 COMPONENTS unit_test_framework program_options REQUIRED )
FIND_PACKAGE( Boost REQUIRED )
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    ADD_DEFINITIONS("-DHAS_BOOST")
ENDIF()

# ODE is not required, but needed for main tests
FIND_PACKAGE( ODE )
if(ODE_FOUND)
    INCLUDE_DIRECTORIES(${ODE_INCLUDE_DIR})
    ADD_DEFINITIONS("-DHAS_ODE")
    ADD_DEFINITIONS("-DdDOUBLE")
endif(ODE_FOUND)

# Headers live in src dir
INCLUDE_DIRECTORIES(src)

# Creates the static library for Tau
ADD_LIBRARY(${PROJECT_NAME} ${Tau_SRC})

# Builds a dummy test
ADD_EXECUTABLE( simpleTest ${Tau_SimpleTest_SRC} )
TARGET_LINK_LIBRARIES( simpleTest ${Boost_LIBRARIES} )

# Builds the main test executable
If(ODE_FOUND)
    ADD_EXECUTABLE( testTauOde ${Tau_Test_SRC} ${Tau_SRC} )
    TARGET_LINK_LIBRARIES( testTauOde ${Boost_LIBRARIES} ${PROJECT_NAME} ${ODE_LIBRARY})
endif(ODE_FOUND)


# Build doxygen documentation
OPTION(SHOULD_BUILD_TAU_DOCUMENTATION "Create doxygen html documentation" ON)
ADD_SUBDIRECTORY(doc)
