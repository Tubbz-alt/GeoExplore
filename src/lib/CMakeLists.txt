#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/14/2014
#
#    Purpose:  Build script for the GeoExplore library.
#

#-----------------------------------------#
#-     Define Required CMake Version     -#
#-----------------------------------------#
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

# Configure C++11
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

#  Set the executable output path
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib )


#---------------------------------#
#-     Set the Project Name      -#
#---------------------------------#
PROJECT( Lib-Geo-Explore )


#------------------------------#
#-     Find GDAL Library      -#
#------------------------------#
find_package( GDAL REQUIRED )
include_directories( ${GDAL_INCLUDE_DIR} )

#--------------------------------#
#-     Find OpenCV Library      -#
#--------------------------------#
find_package( OpenCV REQUIRED )


#-----------------------#
#-     Find Boost      -#
#-----------------------#
find_package( Boost 
                COMPONENTS
                    system
                    filesystem
                REQUIRED )

#-----------------------------------------#
#-     Define Required Header Files      -#
#-----------------------------------------#

#   Config Module
set( GEOEXPLORE_CONFIG_HEADERS
    config/A_Command_Line_Parser.hpp
)


#   Core Module
set( GEOEXPLORE_CORE_HEADERS
    core/Enumerations.hpp
    core/Exceptions.hpp
    core/A_Size.hpp
    core/A_Status.hpp
    core/Status_Enumerations.hpp
)


#   Coordinate Module
set( GEOEXPLORE_COORDINATE_HEADERS
    coordinate/CoordinateBase.hpp
    coordinate/CoordinateGeographic.hpp
    coordinate/CoordinateUTM.hpp
)

#  DEM Module
set( GEOEXPLORE_DEM_HEADERS
    dem.hpp
    dem/A_DEM_IO_Driver_Base.hpp
    dem/A_DEM_IO_Driver_Flat.hpp
    dem/A_DEM_IO_Driver_SRTM.hpp
    dem/An_Elevation_Tile.hpp
    dem/DEM_IO_Driver_Types.hpp
    dem/DEM_Manager.hpp
)

#  Image Module
set( GEOEXPLORE_IMAGE_HEADERS
    image/BaseResource.hpp
    image/ChannelType.hpp
    image/DiskResource.hpp
    image/Image.hpp
    image/MemoryResource.hpp
    image/MetadataContainerBase.hpp
    image/MetadataContainer.hpp
    image/PixelBase.hpp
    image/PixelGray.hpp
    image/PixelRGB.hpp
    image/PixelRGBA.hpp
)

#  IO Module
set( GEOEXPLORE_IO_HEADERS
    io.hpp
    io/gdal_utils.hpp
    io/opencv_utils.hpp
    io/GDAL_Driver.hpp
    io/ImageDriverBase.hpp
    io/Image_IO.hpp
    io/OGR_Driver.hpp
    io/OpenCV_Driver.hpp
    io/gdal_utils/GDAL_Utilities.hpp
    io/opencv_utils/OpenCV_Utilities.hpp
)

#   Math Module
set( GEOEXPLORE_MATH_HEADERS
    math/A_Matrix.hpp
    math/A_Matrix_Eigen.hpp
    math/A_Rectangle.hpp
    math/A_Point.hpp
    math/A_Polygon.hpp
)


#  Thirdparty Module
set( GEOEXPLORE_THIRDPARTY_HEADERS
    thirdparty/pugixml/pugixml.hpp
    thirdparty/pugixml/pugiconfig.hpp
)


#   Utility Module
set( GEOEXPLORE_UTILITIES_HEADERS
    utilities.hpp
    utilities/FilesystemUtilities.hpp
    utilities/StringUtilities.hpp
)

#  Combine modules
set( GEOEXPLORE_HEADERS
    ${GEOEXPLORE_CONFIG_HEADERS}
    ${GEOEXPLORE_CORE_HEADERS}
    ${GEOEXPLORE_COORDINATE_HEADERS}
    ${GEOEXPLORE_DEM_HEADERS}
    ${GEOEXPLORE_IMAGE_HEADERS}
    ${GEOEXPLORE_IO_HEADERS}
    ${GEOEXPLORE_MATH_HEADERS}
    ${GEOEXPLORE_THIRDPARTY_HEADERS}
    ${GEOEXPLORE_UTILITIES_HEADERS}
)


#----------------------------------------#
#-     Define Required Source Files     -#
#----------------------------------------#

#    Config Module
set( GEOEXPLORE_CONFIG_SOURCES
    config/A_Command_Line_Parser.cpp
)


#    Core Module
set( GEOEXPLORE_CORE_SOURCES
    core/Enumerations.cpp
    core/Exceptions.cpp
    core/A_Status.cpp
)

#    Coordinate Module
set( GEOEXPLORE_COORDINATE_SOURCES
    coordinate/CoordinateBase.cpp
)

#   Dem Sources
set( GEOEXPLORE_DEM_SOURCES
    dem/DEM_IO_Driver_Types.cpp
    dem/DEM_Manager.cpp
    dem/A_DEM_IO_Driver_FLAT.cpp
    dem/A_DEM_IO_Driver_SRTM.cpp
)


#   Image Module
set( GEOEXPLORE_IMAGE_SOURCES
    image/ChannelType.cpp
    image/MetadataContainer.cpp
    image/MetadataContainerBase.cpp
)

#   IO Module
set( GEOEXPLORE_IO_SOURCES
    io/Image_IO.cpp
    io/NETPBM_Driver.cpp
    io/OGR_Driver.cpp
    io/gdal_utils/GDAL_Utilities.cpp
)

#  Math Modules
set( GEOEXPLORE_MATH_SOURCES
    math/A_Matrix_Eigen.cpp
)


#  Thirdparty Module
set( GEOEXPLORE_THIRDPARTY_SOURCES
    thirdparty/pugixml/pugixml.cpp
)


#   Utilities Module
set( GEOEXPLORE_UTILITIES_SOURCES
    utilities/FilesystemUtilities.cpp
    utilities/StringUtilities.cpp
)

#   Combine Modules
set( GEOEXPLORE_SOURCES
    ${GEOEXPLORE_CONFIG_SOURCES}
    ${GEOEXPLORE_CORE_SOURCES}
    ${GEOEXPLORE_COORDINATE_SOURCES}
    ${GEOEXPLORE_DEM_SOURCES}
    ${GEOEXPLORE_IMAGE_SOURCES}
    ${GEOEXPLORE_IO_SOURCES}
    ${GEOEXPLORE_MATH_SOURCES}
    ${GEOEXPLORE_THIRDPARTY_SOURCES}
    ${GEOEXPLORE_UTILITIES_SOURCES}
)

#-----------------------------------------#
#-      Generate the Shared Object       -#
#-----------------------------------------#
include_directories( ${PROJECT_BINARY_DIR}/include/ )

add_library( GeoExplore SHARED
             ${GEOEXPLORE_SOURCES}
             ${GEOEXPLORE_HEADERS}
)

target_link_libraries(
            GeoExplore
            ${Boost_LIBRARIES}
            ${GDAL_LIBRARY}
            ${OpenCV_LIBS}
            ${Boost_LIBRARIES}
)


