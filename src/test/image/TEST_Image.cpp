/**
 * @file    TEST_Image.cpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/image/Image.hpp>
#include <GeoExplore/image/MemoryResource.hpp>
#include <GeoExplore/image/Pixel_Types.hpp>

using namespace GEO;

/**
 * Test the Memory Image Constructors 
*/
TEST( Image, Memory_Resource_Constructors )
{

    // Create a set of images
    IMG::Image<IMG::PixelGray_u8> image_gray_u8(12,15);

    // Check the sizes
    ASSERT_EQ( image_gray_u8.Rows(), 12);
    ASSERT_EQ( image_gray_u8.Cols(), 15);

    // Check the values
    for( int r=0; r<image_gray_u8.Rows(); r++ )
    for( int c=0; c<image_gray_u8.Cols(); c++ ){
        ASSERT_EQ( image_gray_u8(r,c).Dims(), 1 );
        ASSERT_EQ( image_gray_u8(r,c)[0], IMG::ChannelTypeUInt8::minValue );
    }
    
    // Modify a few values
    image_gray_u8(10,10) = IMG::PixelGray_u8(25);
    
    // Check the values
    for( int r=0; r<image_gray_u8.Rows(); r++ )
    for( int c=0; c<image_gray_u8.Cols(); c++ ){
        if( r == 10 && c == 10 ){
            ASSERT_EQ( image_gray_u8(r,c).Dims(), 1 );
            ASSERT_EQ( image_gray_u8(r,c)[0], 25 );
        }
        else{
            ASSERT_EQ( image_gray_u8(r,c).Dims(), 1 );
            ASSERT_EQ( image_gray_u8(r,c)[0], IMG::ChannelTypeUInt8::minValue );
        }
    }

    // Check the metadata
    ASSERT_EQ( image_gray_u8.Get_Metadata(), nullptr );

}

