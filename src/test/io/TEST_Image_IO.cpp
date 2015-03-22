/**
 * @file    TEST_Image_IO.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/image/Image.hpp"
#include "../../lib/image/MemoryResource.hpp"
#include "../../lib/image/Pixel_Types.hpp"
#include "../../lib/io/Image_IO.hpp"

using namespace GEO;

/**
 * Test the Read_Image method
*/
TEST( Image_IO, Read_Image_lena_rgb_u8_test_01 ){
    
    // Load the image
    IMG::Image<IMG::PixelRGB_u8> image;
    IO::Read_Image( "data/unit-tests/images/lenna.jpg", image );

    // Check image size
    ASSERT_EQ( image.Rows(), 512 );
    ASSERT_EQ( image.Cols(), 512 );

}

