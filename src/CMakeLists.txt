#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    3/15/2015
#
#    Purpose: Build the GeoExplore Project
#


#   Create the Library
add_subdirectory(lib)

#   Create the unit-tests
add_subdirectory(test)

#   Create the Applications
add_subdirectory(apps)

