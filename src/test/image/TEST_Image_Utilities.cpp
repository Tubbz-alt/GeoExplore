/**
 * @file    TEST_Image_Utilities.cpp
 * @author  Marvin Smith
 * @date    3/28/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/image/Image.hpp"
#include "../../lib/image/Image_Utilities.hpp"
#include "../../lib/image/MemoryResource.hpp"
#include "../../lib/image/Pixel_Types.hpp"

using namespace GEO;

/**
 * Test the image Min/Max Method
*/
TEST( Image_Utilities, MinMax_invalid_image ){

    // Status
    Status status;

    IMG::PixelGray_df actual_min, actual_max;

    ASSERT_EQ( IMG::MinMax( IMG::Image<IMG::PixelGray_df>(), actual_min, actual_max ).Get_Status_Type(), StatusType::FAILURE );
    ASSERT_EQ( static_cast<int32_t>(IMG::MinMax( IMG::Image<IMG::PixelGray_df>(), actual_min, actual_max ).Get_Status_Reason()), static_cast<int32_t>(CoreStatusReason::UNINITIALIZED) );


}


/**
 * Test the Image Min/Max Method
*/
TEST( Image_Utilities, MinMax_valid_image ){

    // Create an image
    IMG::Image<IMG::PixelGray_df> image01( 100, 100 );
    IMG::Image<IMG::PixelRGB_u8>  image02( 100, 100 );

    // Iterate over the image
    for( int r=0; r<image01.Rows(); r++ )
    for( int c=0; c<image01.Cols(); c++ ){
        image01(r,c) = IMG::PixelGray_df( (rand() % 98 +1)/100.0 ); 
        image02(r,c) = IMG::PixelRGB_u8(  (rand() % 98 +1)/100.0,
                                          (rand() % 98 +1)/100.0,
                                          (rand() % 98 +1)/100.0); 
    }

    // Set the actual min and max
    image01(50, 5) = IMG::PixelGray_df(0);
    image01(5, 50) = IMG::PixelGray_df(100);
    image02(50, 5) = IMG::PixelRGB_u8(0, 100, 0);
    image02(5, 50) = IMG::PixelRGB_u8(100, 0, 100);

    // Compute range
    IMG::PixelGray_df min01, max01;
    IMG::PixelRGB_u8  min02, max02;

    ASSERT_EQ( IMG::MinMax( image01, min01, max01 ).Get_Status_Type(), StatusType::SUCCESS );
    ASSERT_EQ( IMG::MinMax( image02, min02, max02 ).Get_Status_Type(), StatusType::SUCCESS );
    
    // Check results
    ASSERT_NEAR( min01[0],   0, 0.0001 );
    ASSERT_NEAR( max01[0], 100, 0.0001 );
    ASSERT_NEAR( min02[0],   0, 0.0001 );
    ASSERT_NEAR( max02[0], 100, 0.0001 );
    ASSERT_NEAR( min02[1],   0, 0.0001 );
    ASSERT_NEAR( max02[1], 100, 0.0001 );
    ASSERT_NEAR( min02[2],   0, 0.0001 );
    ASSERT_NEAR( max02[2], 100, 0.0001 );

}


