#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    3/27/2015
#    
#    Purpose:  Build script for the Geo-Render-Utility
#


#  Set C++ 11
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

#  Set the executable output path
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib )


#--------------------------------#
#-     Find GLFW 3 Library      -#
#--------------------------------#
find_package( glfw3 REQUIRED )
if( EXISTS ${GLFW3_LIBRARY} )
    
    LIST(APPEND GLFW_LIBRARY_LIST ${GLFW3_LIBRARY})

    if(APPLE)
        MESSAGE("Finding Mac GLFW Libraries")
    elseif(UNIX)
        
        #  Find X11
        FIND_PACKAGE(X11 REQUIRED)
        LIST(APPEND GLFW_LIBRARY_LIST ${X11_LIBRARIES})
    endif()
endif()


#--------------------------------#
#-     Find OpenCV Library      -#
#--------------------------------#
find_package( OpenCV REQUIRED )

#-----------------------------------#
#-     Find C++ Thread Library     -#
#-----------------------------------#
find_package( Threads )

#------------------------------#
#-     Find GDAL Library      -#
#------------------------------#
find_package( GDAL REQUIRED )
include_directories( ${GDAL_INCLUDE_DIR} )

#------------------------------------#
#-  Find OpenGL Libraries (Drivers) -#
#------------------------------------#
find_package( OpenGL REQUIRED )

#-------------------------------------------#
#-  Find OpenGL Extension Wrangler (GLEW)  -#
#-------------------------------------------#
find_package( GLEW REQUIRED )
include_directories( ${GLEW_INCLUDE_DIR})

#------------------------------------------#
#-      Define Required Header Files      -#
#------------------------------------------#
set( GEO_RENDER_UTILITY_HEADERS
    core/Configuration_Options.hpp
    core/Data_Container.hpp
    gl_utils/OpenGL_Utilities.hpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GEO_RENDER_UTILITY_SOURCES
    geo-render-utility.cpp
    core/Configuration_Options.cpp
    core/Data_Container.cpp
    gl_utils/OpenGL_Utilities.cpp
)

#---------------------------------#
#-     Build the Application     -#
#---------------------------------#
include_directories( ../../lib )

add_executable( geo-render-utility
                ${GEO_RENDER_UTILITY_SOURCES}
                ${GEO_RENDER_UTILITY_HEADERS}
)

target_link_libraries( geo-render-utility
                GeoExplore
                ${CMAKE_THREAD_LIBS_INIT}
                ${Boost_LIBRARIES}
                ${GDAL_LIBRARY}
                ${OpenCV_LIBS}
                GLEW
                ${GLFW_LIBRARY_LIST}
                pthread
                ${OPENGL_LIBRARIES}
)

