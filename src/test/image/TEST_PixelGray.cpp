/**
 * @file    TEST_PixelGray.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/image/PixelGray.hpp"

using namespace GEO;

/**
 * Test the default constructors
*/
TEST( PixelGray, Constructor_default ){

    // Define EPS
    const double EPS = 0.0001;

    // Create grayscale pixels
    IMG::PixelGray_df   pix01;
    IMG::PixelGray_d    pix02;
    IMG::PixelGray_u8   pix03;
    IMG::PixelGray_u12  pix04;
    IMG::PixelGray_u14  pix05;
    IMG::PixelGray_u16  pix06;
    IMG::PixelGray_u32  pix07;

    // Check values
    ASSERT_NEAR( pix01[0], 0, EPS );  
    ASSERT_NEAR( pix02[0], 0, EPS );
    ASSERT_EQ( pix03[0], 0 );
    ASSERT_EQ( pix04[0], 0 );
    ASSERT_EQ( pix05[0], 0 );
    ASSERT_EQ( pix06[0], 0 );
    ASSERT_EQ( pix07[0], 0 );

    // Check Dims
    ASSERT_EQ( pix01.Dims(), 1 );
    ASSERT_EQ( pix02.Dims(), 1 );
    ASSERT_EQ( pix03.Dims(), 1 );
    ASSERT_EQ( pix04.Dims(), 1 );
    ASSERT_EQ( pix05.Dims(), 1 );
    ASSERT_EQ( pix06.Dims(), 1 );
    ASSERT_EQ( pix07.Dims(), 1 );

}

/**
 * Test the grayscale constructors
*/
TEST( PixelGray, Constructor_grayscale ){

    // Define EPS
    const double EPS = 0.0001;

    // Create grayscale pixels
    IMG::PixelGray_df   pix01( 12 );
    IMG::PixelGray_d    pix02( 12 );
    IMG::PixelGray_u8   pix03( 12 );
    IMG::PixelGray_u12  pix04( 12 );
    IMG::PixelGray_u14  pix05( 12 );
    IMG::PixelGray_u16  pix06( 12 );
    IMG::PixelGray_u32  pix07( 12 );

    // Check values
    ASSERT_NEAR( pix01[0], 12, EPS );  
    ASSERT_NEAR( pix02[0], 12, EPS );
    ASSERT_EQ( pix03[0], 12 );
    ASSERT_EQ( pix04[0], 12 );
    ASSERT_EQ( pix05[0], 12 );
    ASSERT_EQ( pix06[0], 12 );
    ASSERT_EQ( pix07[0], 12 );

    // Check Dims
    ASSERT_EQ( pix01.Dims(), 1 );
    ASSERT_EQ( pix02.Dims(), 1 );
    ASSERT_EQ( pix03.Dims(), 1 );
    ASSERT_EQ( pix04.Dims(), 1 );
    ASSERT_EQ( pix05.Dims(), 1 );
    ASSERT_EQ( pix06.Dims(), 1 );
    ASSERT_EQ( pix07.Dims(), 1 );
}

/**
 * Check the equivalent operator
*/
TEST( PixelGray, Equivalent_Operator ){

    // Create grayscale pixels
    IMG::PixelGray_df   pix01( 12 );
    IMG::PixelGray_d    pix02( 12 );
    IMG::PixelGray_u8   pix03( 12 );
    IMG::PixelGray_u12  pix04( 12 );
    IMG::PixelGray_u14  pix05( 12 );
    IMG::PixelGray_u16  pix06( 12 );
    IMG::PixelGray_u32  pix07( 12 );
    
    IMG::PixelGray_df   other_pix01( 13 );
    IMG::PixelGray_d    other_pix02( 13 );
    IMG::PixelGray_u8   other_pix03( 13 );
    IMG::PixelGray_u12  other_pix04( 13 );
    IMG::PixelGray_u14  other_pix05( 13 );
    IMG::PixelGray_u16  other_pix06( 13 );
    IMG::PixelGray_u32  other_pix07( 13 );

    // Check 
    ASSERT_TRUE( pix01 == pix01 );
    ASSERT_TRUE( pix02 == pix02 );
    ASSERT_TRUE( pix03 == pix03 );
    ASSERT_TRUE( pix04 == pix04 );
    ASSERT_TRUE( pix05 == pix05 );
    ASSERT_TRUE( pix06 == pix06 );
    ASSERT_TRUE( pix07 == pix07 );

    ASSERT_FALSE( pix01 == other_pix01 );
    ASSERT_FALSE( pix02 == other_pix02 );
    ASSERT_FALSE( pix03 == other_pix03 );
    ASSERT_FALSE( pix04 == other_pix04 );
    ASSERT_FALSE( pix05 == other_pix05 );
    ASSERT_FALSE( pix06 == other_pix06 );
    ASSERT_FALSE( pix07 == other_pix07 );
}

/**
 * Check the Black Operator
*/
TEST( PixelGray, Black_Operator ){
    
    // Define Eps
    const double EPS = 0.0001;

    // Check results
    ASSERT_NEAR( IMG::PixelGrayDouble::Black()[0], 0, EPS );
    ASSERT_NEAR( IMG::PixelGrayDoubleFree::Black()[0], -1, EPS );
    ASSERT_EQ( IMG::PixelGrayUInt8::Black()[0], 0 );
    ASSERT_EQ( IMG::PixelGrayUInt12::Black()[0], 0 );
    ASSERT_EQ( IMG::PixelGrayUInt14::Black()[0], 0 );
    ASSERT_EQ( IMG::PixelGrayUInt16::Black()[0], 0 );
    ASSERT_EQ( IMG::PixelGrayUInt32::Black()[0], 0 );

}

/**
 * Check the White Operator
*/
TEST( PixelGray, White_Operator ){
    
    // Define Eps
    const double EPS = 0.0001;

    // Check results
    ASSERT_NEAR( IMG::PixelGrayDouble::White()[0], 1, EPS );
    ASSERT_NEAR( IMG::PixelGrayDoubleFree::White()[0], 1, EPS );
    ASSERT_EQ( IMG::PixelGrayUInt8::White()[0],  IMG::ChannelTypeUInt8::maxValue );
    ASSERT_EQ( IMG::PixelGrayUInt12::White()[0], IMG::ChannelTypeUInt12::maxValue );
    ASSERT_EQ( IMG::PixelGrayUInt14::White()[0], IMG::ChannelTypeUInt14::maxValue );
    ASSERT_EQ( IMG::PixelGrayUInt16::White()[0], IMG::ChannelTypeUInt16::maxValue );
    ASSERT_EQ( IMG::PixelGrayUInt32::White()[0], IMG::ChannelTypeUInt32::maxValue );


}
