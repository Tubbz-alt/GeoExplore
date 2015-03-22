/**
 * @file    TEST_MemoryResource.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/image/MemoryResource.hpp"
#include "../../lib/image/Pixel_Types.hpp"

using namespace GEO;

/**
 * Test the Default Constructor
*/
TEST( MemoryResource, Constructor_default ){

    // Create Memory Resources
    IMG::MemoryResource<IMG::PixelRGB_u8>   resource01;
    IMG::MemoryResource<IMG::PixelRGBA_u12> resource02;
    IMG::MemoryResource<IMG::PixelGray_df>  resource03;
    

    // Validate resources
    ASSERT_EQ( resource01.Rows(), 0 );
    ASSERT_EQ( resource01.Cols(), 0 );
    ASSERT_EQ( resource01.Channels(), 3 );
    ASSERT_EQ( resource02.Rows(), 0 );
    ASSERT_EQ( resource02.Cols(), 0 );
    ASSERT_EQ( resource02.Channels(), 4 );
    ASSERT_EQ( resource03.Rows(), 0 );
    ASSERT_EQ( resource03.Cols(), 0 );
    ASSERT_EQ( resource03.Channels(), 1 );

}

/**
 * Test the Constructor with rows/cols
*/
TEST( MemoryResource, Constructor_rows_cols ){
    
    // Create Memory Resources
    IMG::MemoryResource<IMG::PixelRGB_u8>   resource01( 101, 202 );
    IMG::MemoryResource<IMG::PixelRGBA_u12> resource02( 101, 202 );
    IMG::MemoryResource<IMG::PixelGray_df>  resource03( 101, 202 );
    

    // Validate resources
    ASSERT_EQ( resource01.Rows(), 101 );
    ASSERT_EQ( resource01.Cols(), 202 );
    ASSERT_EQ( resource01.Channels(), 3 );
    ASSERT_EQ( resource02.Rows(), 101 );
    ASSERT_EQ( resource02.Cols(), 202 );
    ASSERT_EQ( resource02.Channels(), 4 );
    ASSERT_EQ( resource03.Rows(), 101 );
    ASSERT_EQ( resource03.Cols(), 202 );
    ASSERT_EQ( resource03.Channels(), 1 );

    // Check values
    for( int r=0; r<resource01.Rows(); r++ )
    for( int c=0; c<resource01.Cols(); c++ ){
        ASSERT_EQ( resource01(r,c), IMG::PixelRGB_u8::Black() );
        ASSERT_EQ( resource02(r,c), IMG::PixelRGBA_u12::Black() );
        ASSERT_EQ( resource03(r,c), IMG::PixelGray_df::Black() );
    }

}


