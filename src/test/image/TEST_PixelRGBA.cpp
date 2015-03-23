/**
 * @file    TEST_PixelRGBA.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/image/PixelRGBA.hpp"

using namespace GEO;

/**
 * Test the Default Constructors
*/
TEST( PixelRGBA, Constructor_default ){

    // Define the eps
    const double eps = 0.00001;

    // Create some pixels
    IMG::PixelRGBA_d    pix01;
    IMG::PixelRGBA_df   pix02;
    IMG::PixelRGBA_u8   pix03;
    IMG::PixelRGBA_u12  pix04;
    IMG::PixelRGBA_u14  pix05;
    IMG::PixelRGBA_u16  pix06;
    IMG::PixelRGBA_u32  pix07;

    // Check Values
    ASSERT_NEAR( pix01[0],  IMG::ChannelTypeDouble::minValue, eps );
    ASSERT_NEAR( pix01[1],  IMG::ChannelTypeDouble::minValue, eps );
    ASSERT_NEAR( pix01[2],  IMG::ChannelTypeDouble::minValue, eps );
    ASSERT_NEAR( pix01[3],  IMG::ChannelTypeDouble::maxValue, eps );
    
    ASSERT_NEAR( pix02[0],  IMG::ChannelTypeDoubleFree::minValue, eps );
    ASSERT_NEAR( pix02[1],  IMG::ChannelTypeDoubleFree::minValue, eps );
    ASSERT_NEAR( pix02[2],  IMG::ChannelTypeDoubleFree::minValue, eps );
    ASSERT_NEAR( pix02[3],  IMG::ChannelTypeDoubleFree::maxValue, eps );

    ASSERT_EQ( pix03[0], IMG::ChannelTypeUInt8::minValue );
    ASSERT_EQ( pix03[1], IMG::ChannelTypeUInt8::minValue );
    ASSERT_EQ( pix03[2], IMG::ChannelTypeUInt8::minValue );
    ASSERT_EQ( pix03[3], IMG::ChannelTypeUInt8::maxValue );
    
    ASSERT_EQ( pix04[0], IMG::ChannelTypeUInt12::minValue );
    ASSERT_EQ( pix04[1], IMG::ChannelTypeUInt12::minValue );
    ASSERT_EQ( pix04[2], IMG::ChannelTypeUInt12::minValue );
    ASSERT_EQ( pix04[3], IMG::ChannelTypeUInt12::maxValue );
    
    ASSERT_EQ( pix05[0], IMG::ChannelTypeUInt14::minValue );
    ASSERT_EQ( pix05[1], IMG::ChannelTypeUInt14::minValue );
    ASSERT_EQ( pix05[2], IMG::ChannelTypeUInt14::minValue );
    ASSERT_EQ( pix05[3], IMG::ChannelTypeUInt14::maxValue );
    
    ASSERT_EQ( pix06[0], IMG::ChannelTypeUInt16::minValue );
    ASSERT_EQ( pix06[1], IMG::ChannelTypeUInt16::minValue );
    ASSERT_EQ( pix06[2], IMG::ChannelTypeUInt16::minValue );
    ASSERT_EQ( pix06[3], IMG::ChannelTypeUInt16::maxValue );

    ASSERT_EQ( pix07[0], IMG::ChannelTypeUInt32::minValue );
    ASSERT_EQ( pix07[1], IMG::ChannelTypeUInt32::minValue );
    ASSERT_EQ( pix07[2], IMG::ChannelTypeUInt32::minValue );
    ASSERT_EQ( pix07[3], IMG::ChannelTypeUInt32::maxValue );
}

/**
 * Test the Gray Constructor
*/
TEST( PixelRGBA, Constructor_grayscale ){

    // Create some grayscale RGBA pixels
    IMG::PixelRGBA_d    pix01(0.5);
    IMG::PixelRGBA_df   pix02(1.1);
    IMG::PixelRGBA_u8   pix03(128);
    IMG::PixelRGBA_u12  pix04(128);
    IMG::PixelRGBA_u14  pix05(128);
    IMG::PixelRGBA_u16  pix06(128);
    IMG::PixelRGBA_u32  pix07(128);

    // Check Values
    ASSERT_NEAR( pix01[0], 0.5, 0.0001 );
    ASSERT_NEAR( pix01[1], 0.5, 0.0001 );
    ASSERT_NEAR( pix01[2], 0.5, 0.0001 );
    ASSERT_NEAR( pix01[3], IMG::ChannelTypeDouble::maxValue, 0.0001 );

    ASSERT_NEAR( pix02[0], 1.1, 0.0001 );
    ASSERT_NEAR( pix02[1], 1.1, 0.0001 );
    ASSERT_NEAR( pix02[2], 1.1, 0.0001 );
    ASSERT_NEAR( pix02[3], IMG::ChannelTypeDoubleFree::maxValue, 0.0001 );
    
    ASSERT_EQ( pix03[0], 128 );
    ASSERT_EQ( pix03[1], 128 );
    ASSERT_EQ( pix03[2], 128 );
    ASSERT_EQ( pix03[3], IMG::ChannelTypeUInt8::maxValue );
    
    ASSERT_EQ( pix04[0], 128 );
    ASSERT_EQ( pix04[1], 128 );
    ASSERT_EQ( pix04[2], 128 );
    ASSERT_EQ( pix04[3], IMG::ChannelTypeUInt12::maxValue );
    
    ASSERT_EQ( pix05[0], 128 );
    ASSERT_EQ( pix05[1], 128 );
    ASSERT_EQ( pix05[2], 128 );
    ASSERT_EQ( pix05[3], IMG::ChannelTypeUInt14::maxValue );
    
    ASSERT_EQ( pix06[0], 128 );
    ASSERT_EQ( pix06[1], 128 );
    ASSERT_EQ( pix06[2], 128 );
    ASSERT_EQ( pix06[3], IMG::ChannelTypeUInt16::maxValue );
    
    ASSERT_EQ( pix07[0], 128 );
    ASSERT_EQ( pix07[1], 128 );
    ASSERT_EQ( pix07[2], 128 );
    ASSERT_EQ( pix07[3], IMG::ChannelTypeUInt32::maxValue );

}

/**
 * Test the RGB Constructor
*/
TEST( PixelRGBA, Constructor_rgb ){

    // Create some RGB pixels
    IMG::PixelRGBA_d    pix01(0.5, 0.1, 1.1);
    IMG::PixelRGBA_df   pix02(1.1, 0.2, 2.1);
    IMG::PixelRGBA_u8   pix03(128, 244, 255);
    IMG::PixelRGBA_u12  pix04(128, 244, 212);
    IMG::PixelRGBA_u14  pix05(128, 111, 222);
    IMG::PixelRGBA_u16  pix06(128, 345, 567);
    IMG::PixelRGBA_u32  pix07(128, 213, 142);

    // Check Values
    ASSERT_NEAR( pix01[0], 0.5, 0.0001 );
    ASSERT_NEAR( pix01[1], 0.1, 0.0001 );
    ASSERT_NEAR( pix01[2], 1.1, 0.0001 );
    ASSERT_NEAR( pix01[3], IMG::ChannelTypeDouble::maxValue, 0.0001 );
    
    ASSERT_NEAR( pix02[0], 1.1, 0.0001 );
    ASSERT_NEAR( pix02[1], 0.2, 0.0001 );
    ASSERT_NEAR( pix02[2], 2.1, 0.0001 );
    ASSERT_NEAR( pix02[3], IMG::ChannelTypeDoubleFree::maxValue, 0.0001 );
    
    ASSERT_EQ( pix03[0], 128 );
    ASSERT_EQ( pix03[1], 244 );
    ASSERT_EQ( pix03[2], 255 );
    ASSERT_EQ( pix03[3], IMG::ChannelTypeUInt8::maxValue );
    
    ASSERT_EQ( pix04[0], 128 );
    ASSERT_EQ( pix04[1], 244 );
    ASSERT_EQ( pix04[2], 212 );
    ASSERT_EQ( pix04[3], IMG::ChannelTypeUInt12::maxValue );
    
    ASSERT_EQ( pix05[0], 128 );
    ASSERT_EQ( pix05[1], 111 );
    ASSERT_EQ( pix05[2], 222 );
    ASSERT_EQ( pix05[3], IMG::ChannelTypeUInt14::maxValue );
    
    ASSERT_EQ( pix06[0], 128 );
    ASSERT_EQ( pix06[1], 345 );
    ASSERT_EQ( pix06[2], 567 );
    ASSERT_EQ( pix06[3], IMG::ChannelTypeUInt16::maxValue );
    
    ASSERT_EQ( pix07[0], 128 );
    ASSERT_EQ( pix07[1], 213 );
    ASSERT_EQ( pix07[2], 142 );
    ASSERT_EQ( pix07[3], IMG::ChannelTypeUInt32::maxValue );


}

/**
 * Test the RGBA Constructor
*/
TEST( PixelRGBA, Constructor_rgba ){
    
    // Create some RGB pixels
    IMG::PixelRGBA_d    pix01(0.5, 0.1, 1.1, 2);
    IMG::PixelRGBA_df   pix02(1.1, 0.2, 2.1, 1);
    IMG::PixelRGBA_u8   pix03(128, 244, 255, 243);
    IMG::PixelRGBA_u12  pix04(128, 244, 212, 234);
    IMG::PixelRGBA_u14  pix05(128, 111, 222, 333);
    IMG::PixelRGBA_u16  pix06(128, 345, 567, 444);
    IMG::PixelRGBA_u32  pix07(128, 213, 142, 555);

    // Check Values
    ASSERT_NEAR( pix01[0], 0.5, 0.0001 );
    ASSERT_NEAR( pix01[1], 0.1, 0.0001 );
    ASSERT_NEAR( pix01[2], 1.1, 0.0001 );
    ASSERT_NEAR( pix01[3], 2  , 0.0001 );
    
    ASSERT_NEAR( pix02[0], 1.1, 0.0001 );
    ASSERT_NEAR( pix02[1], 0.2, 0.0001 );
    ASSERT_NEAR( pix02[2], 2.1, 0.0001 );
    ASSERT_NEAR( pix02[3], 1  , 0.0001 );
    
    ASSERT_EQ( pix03[0], 128 );
    ASSERT_EQ( pix03[1], 244 );
    ASSERT_EQ( pix03[2], 255 );
    ASSERT_EQ( pix03[3], 243 );
    
    ASSERT_EQ( pix04[0], 128 );
    ASSERT_EQ( pix04[1], 244 );
    ASSERT_EQ( pix04[2], 212 );
    ASSERT_EQ( pix04[3], 234 );
    
    ASSERT_EQ( pix05[0], 128 );
    ASSERT_EQ( pix05[1], 111 );
    ASSERT_EQ( pix05[2], 222 );
    ASSERT_EQ( pix05[3], 333 );
    
    ASSERT_EQ( pix06[0], 128 );
    ASSERT_EQ( pix06[1], 345 );
    ASSERT_EQ( pix06[2], 567 );
    ASSERT_EQ( pix06[3], 444 );
    
    ASSERT_EQ( pix07[0], 128 );
    ASSERT_EQ( pix07[1], 213 );
    ASSERT_EQ( pix07[2], 142 );
    ASSERT_EQ( pix07[3], 555 );

}

/**
 * Test the Equivalent Operator
*/
TEST( PixelRGBA, Equivalent_Operator ){

    // Create some RGBA pixels
    IMG::PixelRGBA_d    pix01(0.5, 0.1, 1.1, 2);
    IMG::PixelRGBA_df   pix02(1.1, 0.2, 2.1, 1);
    IMG::PixelRGBA_u8   pix03(128, 244, 255, 243);
    IMG::PixelRGBA_u12  pix04(128, 244, 212, 234);
    IMG::PixelRGBA_u14  pix05(128, 111, 222, 333);
    IMG::PixelRGBA_u16  pix06(128, 345, 567, 444);
    IMG::PixelRGBA_u32  pix07(128, 213, 142, 555);
    
    IMG::PixelRGBA_d    other_pix01(0.6, 0.1, 1.1, 2);
    IMG::PixelRGBA_df   other_pix02(1.0, 0.2, 2.1, 1);
    IMG::PixelRGBA_u8   other_pix03(127, 244, 255, 243);
    IMG::PixelRGBA_u12  other_pix04(127, 244, 212, 234);
    IMG::PixelRGBA_u14  other_pix05(127, 111, 222, 333);
    IMG::PixelRGBA_u16  other_pix06(127, 345, 567, 444);
    IMG::PixelRGBA_u32  other_pix07(127, 213, 142, 555);

    // Test Equivalency
    ASSERT_TRUE( pix01 == pix01 );
    ASSERT_TRUE( pix02 == pix02 );
    ASSERT_TRUE( pix03 == pix03 );
    ASSERT_TRUE( pix04 == pix04 );
    ASSERT_TRUE( pix05 == pix05 );
    ASSERT_TRUE( pix06 == pix06 );
    ASSERT_TRUE( pix07 == pix07 );
    
    ASSERT_TRUE( other_pix01 == other_pix01 );
    ASSERT_TRUE( other_pix02 == other_pix02 );
    ASSERT_TRUE( other_pix03 == other_pix03 );
    ASSERT_TRUE( other_pix04 == other_pix04 );
    ASSERT_TRUE( other_pix05 == other_pix05 );
    ASSERT_TRUE( other_pix06 == other_pix06 );
    ASSERT_TRUE( other_pix07 == other_pix07 );

    ASSERT_FALSE( pix01 == other_pix01 );
    ASSERT_FALSE( pix02 == other_pix02 );
    ASSERT_FALSE( pix03 == other_pix03 );
    ASSERT_FALSE( pix04 == other_pix04 );
    ASSERT_FALSE( pix05 == other_pix05 );
    ASSERT_FALSE( pix06 == other_pix06 );
    ASSERT_FALSE( pix07 == other_pix07 );


}
