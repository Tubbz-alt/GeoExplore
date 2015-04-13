/** 
 * @file    TEST_ImageTransformInvert.cpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#include <gtest/gtest.h>

// C++ Standard Libraries
#include <iostream>

// GeoExplore Libraries
#include <GeoExplore/image/MemoryResource.hpp>
#include <GeoExplore/image/Pixel_Types.hpp>
#include <GeoExplore/image/transforms/ImageTransformInvert.hpp>
#include <GeoExplore/io/opencv_utils/OpenCV_Utilities.hpp>


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
        
        if( (r/10) %2 == 0 && (c/10) % 2 == 0 ){
            (*gray_image)(r,c) = IMG::PixelGray_u8(255);
            (*rgb_image)(r,c)   = IMG::PixelRGB_u8(255,255,255);
        }
        else if((r/10) % 2 == 0 ){
            (*gray_image)(r,c) = IMG::PixelGray_u8(0);
            (*rgb_image)(r,c)   = IMG::PixelRGB_u8(255,0,0);
        }
        else if((c/10) % 2 == 0 ){
            (*gray_image)(r,c) = IMG::PixelGray_u8(0);
            (*rgb_image)(r,c)   = IMG::PixelRGB_u8(0,255,0);
        }
        else{
            (*gray_image)(r,c) = IMG::PixelGray_u8(255);
            (*rgb_image)(r,c)  = IMG::PixelRGB_u8(0,0,255);
        }

    }

    
    // Invert the image
    IMG::Invert_Image<IMG::PixelGray_u8>( gray_image, gray_image );
    IMG::Invert_Image<IMG::PixelRGB_u8>( rgb_image, rgb_image );


    // Validate the result
    for( int r=0; r<gray_image->Rows(); r++ )
    for( int c=0; c<gray_image->Cols(); c++ ){
        
        if( (r/10) %2 == 0 && (c/10) % 2 == 0 ){
            ASSERT_EQ( (*gray_image)(r,c), 0 );
            ASSERT_EQ( (*rgb_image)(r,c)[0], 0);
            ASSERT_EQ( (*rgb_image)(r,c)[1], 0);
            ASSERT_EQ( (*rgb_image)(r,c)[2], 0);
        }
        else if((r/10) % 2 == 0 ){
            ASSERT_EQ( (*gray_image)(r,c), 255 );
            ASSERT_EQ( (*rgb_image)(r,c)[0],   0);
            ASSERT_EQ( (*rgb_image)(r,c)[1], 255);
            ASSERT_EQ( (*rgb_image)(r,c)[2], 255);
        }
        else if((c/10) % 2 == 0 ){
            ASSERT_EQ( (*gray_image)(r,c), 255 );
            ASSERT_EQ( (*rgb_image)(r,c)[0], 255);
            ASSERT_EQ( (*rgb_image)(r,c)[1],   0);
            ASSERT_EQ( (*rgb_image)(r,c)[2], 255);
        }
        else{
            ASSERT_EQ( (*gray_image)(r,c), 0 );
            ASSERT_EQ( (*rgb_image)(r,c)[0], 255);
            ASSERT_EQ( (*rgb_image)(r,c)[1], 255);
            ASSERT_EQ( (*rgb_image)(r,c)[2],   0);
        }

    }


}

