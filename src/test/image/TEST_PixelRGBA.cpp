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

    FAIL();

}

/**
 * Test the RGB Constructor
*/
TEST( PixelRGBA, Constructor_rgb ){

    FAIL();

}

/**
 * Test the RGBA Constructor
*/
TEST( PixelRGBA, Constructor_rgba ){

    FAIL();

}

/**
 * Test the Equivalent Operator
*/
TEST( PixelRGBA, Equivalent_Operator ){

    FAIL();

}
