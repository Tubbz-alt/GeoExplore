/**
 * @file    TEST_OpenCV_Driver.cpp
 * @author  Marvin Smith
 * @date    5/14/2014
*/
#include <gtest/gtest.h>

/// GeoExplore
#include <GeoExplore.hpp>

/// OpenCV
#include <opencv2/core/core.hpp>


/**
 * Test the PixelType to OpenCV Type
*/
TEST( OpenCV_Driver, PixelType2OpenCVType ){

    ASSERT_EQ( GEO::IO::OPENCV::PixelType2OpenCVType<GEO::PixelRGB_d>(), CV_8UC3);

}

