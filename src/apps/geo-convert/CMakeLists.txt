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

#--------------------#
#-    Find Boost    -#
#--------------------#
FIND_LIBRARY( Boost
                COMPONENTS
                    thread
                    system 
                    filesystem
                    regex
                REQUIRED
)
include_directories( ${Boost_INCLUDE_DIRS} )

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

