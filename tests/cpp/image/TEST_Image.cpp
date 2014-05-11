/**
 * @file    TEST_Image.cpp
 * @author  Marvin Smith
 * @date    5/10/2014
*/
#include <gtest/gtest.h>

/// GeoExplore Library
#include <GeoExplore.hpp>

/**
 * Test the Image_ class functions using a Memory resource
*/
TEST( Image, Constructors ){

    /// Create a RAM Image
    GEO::Image<GEO::PixelRGB_u8> image01;
    
    // make sure the resource is empty
    ASSERT_EQ( image01.rows(), 0);
    ASSERT_EQ( image01.cols(), 0);

    
    FAIL();

}

