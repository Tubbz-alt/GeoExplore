/** 
 * @file    TEST_ImageTransformInvert.cpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#include <gtest/gtest.h>

// C++ Standard Libraries
#include <iostream>

// GeoExplore Libraries
#include "../../../lib/image/MemoryResource.hpp"
#include "../../../lib/image/Pixel_Types.hpp"
#include "../../../lib/image/transforms/ImageTransformInvert.hpp"
#include "../../../lib/io/opencv_utils/OpenCV_Utilities.hpp"


using namespace GEO;

/**
 * Test the invert image method.
*/
TEST( ImageTransformInvert, Invert_Image )
{
    // Create Checkerboard Image
    IMG::Image<IMG::PixelGray_u8>::ptr_t gray_image(new IMG::Image<IMG::PixelGray_u8>(300,300));
    IMG::Image<IMG::PixelRGB_u8>::ptr_t  rgb_image(new  IMG::Image<IMG::PixelRGB_u8>(300,300));

    for( int r=0; r<gray_image->Rows(); r++ )
    for( int c=0; c<gray_image->Cols(); c++ ){
        
        if( ((r/10) + (c/10)) % 2 == 0 ){
            (*gray_image)(r,c) = IMG::PixelGray_u8(255);
            (*rgb_image)(r,c)   = IMG::PixelRGB_u8(255,255,255);
        }
        else{
            (*gray_image)(r,c) = IMG::PixelGray_u8(0);
            (*rgb_image)(r,c)  = IMG::PixelRGB_u8(0,0,0);
        }

    }

    IO::OPENCV::View_Image( *gray_image, "Image" );
    IO::OPENCV::View_Image(  *rgb_image, "Image" );
    
    // Invert the image
    IMG::Invert_Image<IMG::PixelGray_u8>( gray_image, gray_image );
    IMG::Invert_Image<IMG::PixelRGB_u8>( rgb_image, rgb_image );

    IO::OPENCV::View_Image( *gray_image, "Image" );
    IO::OPENCV::View_Image(  *rgb_image, "Image" );
    FAIL();

}

