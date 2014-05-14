/**
 * @file    TEST_ImageIO.cpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#include <gtest/gtest.h>

/// GeoExplore
#include <GeoExplore.hpp>

/**
 * Test the Compute driver function
*/
TEST( ImageIO, ComputeDriver ){

    /// Test the driver for GDAL-type images
    ASSERT_EQ( GEO::IO::compute_driver("/var/tmp/image.jpg"), GEO::ImageDriver::GDAL );
    
}

