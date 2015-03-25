#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    3/15/2015
#
#    Purpose:  Build the GeoExplore Project
#


#  Define the required CMake Version
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

#----------------------------#
#-        Allow C++ 11x     -#
#----------------------------#
SET(CMAKE_CXX_FLAGS "-std=c++11")


#----------------------------------------#
#-     Add 3rd Party Cmake Modules      -#
#----------------------------------------#
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

#-------------------------------#
#-     Set the Project Name    -#
#-------------------------------#
PROJECT( Geo-Explore )


#---------------------#
#-    Find Eigen3    -#
#---------------------#
FIND_PACKAGE( Eigen3 )

if( EIGEN3_FOUND )
    message("Eigen3 Found")
    message("Eigen3 Include: ${EIGEN3_INCLUDE_DIR}")
    include_directories( ${EIGEN3_INCLUDE_DIR})
else()
    message("Eigen3 Not Found")
endif()


#-------------------#
#-    Find Boost   -#
#-------------------#
find_package( Boost 
                COMPONENTS
                    thread
                    system
                    filesystem
                    regex
                REQUIRED
)
include_directories(${Boost_INCLUDE_DIRS})
if( NOT ${Boost_FOUND} )
    MESSAGE( FATAL_ERROR "Unable to find Boost Libraries.")
endif()
MESSAGE("Boost Include Directory: ${Boost_INCLUDE_DIRS}")


#------------------------------------#
#-     Build GeoExplore Project     -#
#------------------------------------#
add_subdirectory(src)

