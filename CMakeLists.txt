#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    3/15/2015
#
#    Purpose:  Build the GeoExplore Project
#


#  Define the required CMake Version
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )


#-------------------------------#
#-     Set the Project Name    -#
#-------------------------------#
PROJECT( Geo-Explore )


#------------------------------------#
#-     Build GeoExplore Project     -#
#------------------------------------#
add_subdirectory(src)

