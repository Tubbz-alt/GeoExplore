#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    3/15/2015
#
#    Purpose:  Build the GeoExplore Library
#


#------------------------------#
#-    Set the Project Name    -#
#------------------------------#
PROJECT( Geo-Explore-Unit-Tests )

#  Set C++ 11
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

#  Set the executable output path
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../bin )
set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/../../lib )

#------------------------------#
#-     Find GDAL Library      -#
#------------------------------#
find_package( GDAL REQUIRED )
include_directories( ${GDAL_INCLUDE_DIR} )


#------------------------------------------#
#-      Define Required Header Files      -#
#------------------------------------------#
set( GEOEXPLORE_TEST_HEADERS
)

#---------------------------------------------------#
#-       Define the Config Module Test Files       -#
#---------------------------------------------------#
set( GEOEXPLORE_CONFIG_MODULE_TESTS
    config/TEST_A_Command_Line_Parser.cpp
)


#-------------------------------------------------------#
#-       Define the Coordinate Module Test Files       -#
#-------------------------------------------------------#
set( GEOEXPLORE_COORDINATE_MODULE_TESTS
    coordinate/TEST_CoordinateGeographic.cpp
    coordinate/TEST_CoordinateUTM.cpp
)


#-------------------------------------------------#
#-       Define the Core Module Test Files       -#
#-------------------------------------------------#
set( GEOEXPLROE_CORE_MODULE_TESTS
    core/TEST_A_Status.cpp
    core/TEST_Enumerations.cpp
    core/TEST_Status_Enumerations.cpp
)


#------------------------------------------------#
#-       Define the DEM Module Test Files       -#
#------------------------------------------------#
set( GEOEXPLORE_DEM_MODULE_TESTS
    dem/TEST_A_DEM_IO_Driver_Flat.cpp
    dem/TEST_A_DEM_IO_Driver_SRTM.cpp
    dem/TEST_An_Elevation_Tile.cpp
    dem/TEST_DEM_IO_Driver_Types.cpp
    dem/TEST_DEM_Manager.cpp
    dem/TEST_SRTM_Utilities.cpp
)


#-------------------------------------------------#
#-    Define the Filesystem Module Test Files    -#
#-------------------------------------------------#
set( GEOEXPLORE_FILESYSTEM_MODULE_TESTS 
    filesystem/TEST_FilesystemPath.cpp
    filesystem/TEST_PathFormatType.cpp
)

#----------------------------------------------#
#-     Define the Math Module Test Files      -#
#----------------------------------------------#
set( GEOEXPLORE_MATH_MODULE_TESTS
    math/TEST_A_Matrix_Eigen.cpp
    math/TEST_A_Point.cpp
    math/TEST_A_Polygon.cpp
    math/TEST_A_Rectangle.cpp
    math/TEST_Common_Equations.cpp
    math/TEST_Matrix_Conversions.cpp
)

#------------------------------------------------#
#-      Define the Image Module Test Files      -#
#------------------------------------------------#
set( GEOEXPLORE_IMAGE_MODULE_TESTS
    image/TEST_ChannelType.cpp
    image/TEST_Image.cpp
    image/TEST_Image_Utilities.cpp
    image/TEST_Interpolation.cpp
    image/TEST_MemoryResource.cpp
    image/TEST_PixelGray.cpp
    image/TEST_PixelRGB.cpp
    image/TEST_PixelRGBA.cpp
    image/transforms/TEST_ImageTransformColorMap.cpp
    image/transforms/TEST_ImageTransformInvert.cpp
    image/transforms/TEST_ImageTransformNormalize.cpp
)


#------------------------------------------#
#-       Define the IO Module Tests       -#
#------------------------------------------#
set( GEOEXPLORE_IO_MODULE_TESTS 
    io/TEST_GDAL_Driver.cpp
    io/TEST_Image_IO.cpp
    io/TEST_OpenCV_Driver.cpp
)

#------------------------------------------#
#-       Define the Utility Module Tests  -#
#------------------------------------------#
set( GEOEXPLORE_UTILITY_MODULE_TESTS
    utilities/TEST_FilesystemUtilities.cpp
    utilities/TEST_StringUtilities.cpp
    utilities/TEST_System_Utilities.cpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GEOEXPLORE_TEST_SOURCES
    geo-explore-unit-tests.cpp
    Unit_Testing_Only/Coordinate_Test_Harness.cpp
    Unit_Testing_Only/Coordinate_Test_Harness.hpp
    ${GEOEXPLORE_CONFIG_MODULE_TESTS}
    ${GEOEXPLORE_COORDINATE_MODULE_TESTS}
    ${GEOEXPLORE_CORE_MODULE_TESTS}
    ${GEOEXPLORE_DEM_MODULE_TESTS}
    ${GEOEXPLORE_FILESYSTEM_MODULE_TESTS}
    ${GEOEXPLORE_MATH_MODULE_TESTS}
    ${GEOEXPLORE_IMAGE_MODULE_TESTS}
    ${GEOEXPLORE_IO_MODULE_TESTS}
    ${GEOEXPLORE_UTILITY_MODULE_TESTS}
)


#-------------------------------------#
#-      Define GoogleTest Files      -#
#-------------------------------------#
set( GOOGLETEST_SOURCES 

)
set( GOOGLETEST_HEADERS
    googletest/include/gtest/gtest.h
    googletest/include/gtest/gtest-death-test.h
    googletest/include/gtest/gtest-message.h
    googletest/include/gtest/gtest-param-test.h
    googletest/include/gtest/gtest-printers.h
    googletest/include/gtest/gtest_pred_impl.h
    googletest/include/gtest/gtest_prod.h
    googletest/include/gtest/gtest-test-part.h
    googletest/include/gtest/gtest-typed-test.h
    googletest/include/gtest/internal/gtest-death-test-internal.h
    googletest/include/gtest/internal/gtest-filepath.h
    googletest/include/gtest/internal/gtest-internal.h
    googletest/include/gtest/internal/gtest-linked_ptr.h
    googletest/include/gtest/internal/gtest-param-util.h
    googletest/include/gtest/internal/gtest-param-util-generated.h
    googletest/include/gtest/internal/gtest-port.h
    googletest/include/gtest/internal/gtest-string.h
    googletest/include/gtest/internal/gtest-type-util.h
)
include_directories(googletest/include)

#----------------------------------#
#-     Build the Application      -#
#----------------------------------#
include_directories(../lib)

add_executable( geo-explore-unit-tests
                ${GEOEXPLORE_TEST_HEADERS}
                ${GEOEXPLORE_TEST_SOURCES}
                ${GOOGLETEST_SOURCES}
                ${GOOGLETEST_HEADERS}
)

target_link_libraries( geo-explore-unit-tests
                GeoExplore
                ${CMAKE_THREAD_LIBS_INIT}
                ${Boost_LIBRARIES}
                ${GDAL_LIBRARY}
                ${OpenCV_LIBS}
)

