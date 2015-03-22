#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    3/15/2015
#
#    Purpose:  Build the Geo-Convert Application
#


#------------------------------#
#-    Set the Project Name    -#
#------------------------------#
PROJECT( Geo-Convert )

#  Set C++ 11
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall")


#------------------------------#
#-     Find GDAL Library      -#
#------------------------------#
find_package( GDAL REQUIRED )
include_directories( ${GDAL_INCLUDE_DIR} )


#------------------------------------------#
#-      Define Required Header Files      -#
#------------------------------------------#
set( GEOCONVERT_HEADERS
    Options.hpp
    CoordinateConversion.hpp
    ImageConversion.hpp
    Utilities.hpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GEOCONVERT_SOURCES
    main.cpp
    Options.cpp
    CoordinateConversion.cpp
    ImageConversion.cpp
    Utilities.cpp
)


#----------------------------------#
#-     Build the Application      -#
#----------------------------------#
include_directories(../../lib)

add_executable( geo-convert 
                ${GEOCONVERT_SOURCES}
                ${GEOCONVERT_HEADERS}
)

target_link_libraries( geo-convert
                GeoExplore
                ${CMAKE_THREAD_LIBS_INIT}
                ${Boost_LIBRARIES}
                ${GDAL_LIBRARY}
                ${OpenCV_LIBS}
)

