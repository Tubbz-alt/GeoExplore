/**
 * @file    TEST_PixelRGB.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/image/PixelRGB.hpp>

using namespace GEO;

/**
 * Test hte Default Constructors
*/
TEST( PixelRGB, Constructor_default ){

    // Define the EPS
    const double eps = 0.00001;

    // Create some pixels
    IMG::PixelRGB_d    pix01;
    IMG::PixelRGB_df   pix02;
    IMG::PixelRGB_u8   pix03;
    IMG::PixelRGB_u12  pix04;
    IMG::PixelRGB_u14  pix05;
    IMG::PixelRGB_u16  pix06;
    IMG::PixelRGB_u32  pix07;

    // Check Values
    ASSERT_NEAR( pix01[0], IMG::ChannelTypeDouble::minValue, eps );
    ASSERT_NEAR( pix01[1], IMG::ChannelTypeDouble::minValue, eps );
    ASSERT_NEAR( pix01[2], IMG::ChannelTypeDouble::minValue, eps );
    
    ASSERT_NEAR( pix02[0], IMG::ChannelTypeDoubleFree::minValue, eps );
    ASSERT_NEAR( pix02[1], IMG::ChannelTypeDoubleFree::minValue, eps );
    ASSERT_NEAR( pix02[2], IMG::ChannelTypeDoubleFree::minValue, eps );
    
    ASSERT_EQ( pix03[0], IMG::ChannelTypeUInt8::minValue );
    ASSERT_EQ( pix03[1], IMG::ChannelTypeUInt8::minValue );
    ASSERT_EQ( pix03[2], IMG::ChannelTypeUInt8::minValue );
    
    ASSERT_EQ( pix04[0], IMG::ChannelTypeUInt12::minValue );
    ASSERT_EQ( pix04[1], IMG::ChannelTypeUInt12::minValue );
    ASSERT_EQ( pix04[2], IMG::ChannelTypeUInt12::minValue );
    
    ASSERT_EQ( pix05[0], IMG::ChannelTypeUInt14::minValue );
    ASSERT_EQ( pix05[1], IMG::ChannelTypeUInt14::minValue );
    ASSERT_EQ( pix05[2], IMG::ChannelTypeUInt14::minValue );

    ASSERT_EQ( pix06[0], IMG::ChannelTypeUInt16::minValue );
    ASSERT_EQ( pix06[1], IMG::ChannelTypeUInt16::minValue );
    ASSERT_EQ( pix06[2], IMG::ChannelTypeUInt16::minValue );
    
    ASSERT_EQ( pix07[0], IMG::ChannelTypeUInt32::minValue );
    ASSERT_EQ( pix07[1], IMG::ChannelTypeUInt32::minValue );
    ASSERT_EQ( pix07[2], IMG::ChannelTypeUInt32::minValue );

}

/**
 * Test the Grayscale Constructor
*/
TEST( PixelRGB, Constructor_grayscale ){

    // Create some grayscale RGB pixels
    IMG::PixelRGB_d    pix01(0.5);
    IMG::PixelRGB_df   pix02(1.1);
    IMG::PixelRGB_u8   pix03(128);
    IMG::PixelRGB_u12  pix04(128);
    IMG::PixelRGB_u14  pix05(128);
    IMG::PixelRGB_u16  pix06(128);
    IMG::PixelRGB_u32  pix07(128);

    // Check Values
    ASSERT_NEAR( pix01[0], 0.5, 0.0001 );
    ASSERT_NEAR( pix01[1], 0.5, 0.0001 );
    ASSERT_NEAR( pix01[2], 0.5, 0.0001 );
    
    ASSERT_NEAR( pix02[0], 1.1, 0.0001 );
    ASSERT_NEAR( pix02[1], 1.1, 0.0001 );
    ASSERT_NEAR( pix02[2], 1.1, 0.0001 );
    
    ASSERT_EQ( pix03[0], 128 );
    ASSERT_EQ( pix03[1], 128 );
    ASSERT_EQ( pix03[2], 128 );
    
    ASSERT_EQ( pix04[0], 128 );
    ASSERT_EQ( pix04[1], 128 );
    ASSERT_EQ( pix04[2], 128 );
    
    ASSERT_EQ( pix05[0], 128 );
    ASSERT_EQ( pix05[1], 128 );
    ASSERT_EQ( pix05[2], 128 );
    
    ASSERT_EQ( pix06[0], 128 );
    ASSERT_EQ( pix06[1], 128 );
    ASSERT_EQ( pix06[2], 128 );
    
    ASSERT_EQ( pix07[0], 128 );
    ASSERT_EQ( pix07[1], 128 );
    ASSERT_EQ( pix07[2], 128 );

}

/**
 * Test the RGB Constructor
*/
TEST( PixelRGB, Constructor_rgb ){

    // Create some RGB pixels
    IMG::PixelRGB_d    pix01(0.5, 0.1, 1.1);
    IMG::PixelRGB_df   pix02(1.1, 0.2, 2.1);
    IMG::PixelRGB_u8   pix03(128, 244, 255);
    IMG::PixelRGB_u12  pix04(128, 244, 212);
    IMG::PixelRGB_u14  pix05(128, 111, 222);
    IMG::PixelRGB_u16  pix06(128, 345, 567);
    IMG::PixelRGB_u32  pix07(128, 213, 142);

    // Check Values
    ASSERT_NEAR( pix01[0], 0.5, 0.0001 );
    ASSERT_NEAR( pix01[1], 0.1, 0.0001 );
    ASSERT_NEAR( pix01[2], 1.1, 0.0001 );
    
    ASSERT_NEAR( pix02[0], 1.1, 0.0001 );
    ASSERT_NEAR( pix02[1], 0.2, 0.0001 );
    ASSERT_NEAR( pix02[2], 2.1, 0.0001 );
    
    ASSERT_EQ( pix03[0], 128 );
    ASSERT_EQ( pix03[1], 244 );
    ASSERT_EQ( pix03[2], 255 );
    
    ASSERT_EQ( pix04[0], 128 );
    ASSERT_EQ( pix04[1], 244 );
    ASSERT_EQ( pix04[2], 212 );
    
    ASSERT_EQ( pix05[0], 128 );
    ASSERT_EQ( pix05[1], 111 );
    ASSERT_EQ( pix05[2], 222 );
    
    ASSERT_EQ( pix06[0], 128 );
    ASSERT_EQ( pix06[1], 345 );
    ASSERT_EQ( pix06[2], 567 );
    
    ASSERT_EQ( pix07[0], 128 );
    ASSERT_EQ( pix07[1], 213 );
    ASSERT_EQ( pix07[2], 142 );

}

/** 
 * Test the equivalent operator
*/
TEST( PixelRGB, Equivalent_Operator ){

    // Create some RGB pixels
    IMG::PixelRGB_d    pix01(0.5, 0.1, 1.1);
    IMG::PixelRGB_df   pix02(1.1, 0.2, 2.1);
    IMG::PixelRGB_u8   pix03(128, 244, 255);
    IMG::PixelRGB_u12  pix04(128, 244, 212);
    IMG::PixelRGB_u14  pix05(128, 111, 222);
    IMG::PixelRGB_u16  pix06(128, 345, 567);
    IMG::PixelRGB_u32  pix07(128, 213, 142);

    // Create some more RGB pixels
    IMG::PixelRGB_d    other_pix01(0.4, 0.1, 1.1);
    IMG::PixelRGB_df   other_pix02(1.0, 0.2, 2.1);
    IMG::PixelRGB_u8   other_pix03(127, 244, 255);
    IMG::PixelRGB_u12  other_pix04(127, 244, 212);
    IMG::PixelRGB_u14  other_pix05(127, 111, 222);
    IMG::PixelRGB_u16  other_pix06(127, 345, 567);
    IMG::PixelRGB_u32  other_pix07(127, 213, 142);

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


/**
 * Check the addition operator
*/
TEST( PixelRGB, Addition_Operator ){

    IMG::PixelRGB_df pix01(1);
    IMG::PixelRGB_df pix02(-2);

    ASSERT_NEAR( (pix01+pix02)[0], -1, 0.0001 );
    ASSERT_NEAR( (pix01+pix02)[1], -1, 0.0001 );
    ASSERT_NEAR( (pix01+pix02)[2], -1, 0.0001 );
}

/**
 * Check the subtraction operator
*/
TEST( PixelRGB, Subtraction_Operator ){

    IMG::PixelRGB_df pix01(1);
    IMG::PixelRGB_df pix02(-2);

    ASSERT_NEAR( (pix01-pix02)[0], 3, 0.0001 );
    ASSERT_NEAR( (pix01-pix02)[1], 3, 0.0001 );
    ASSERT_NEAR( (pix01-pix02)[2], 3, 0.0001 );
}


/**
 * Check the White Operator
*/
TEST( PixelRGB, Black_Operator ){
    
    // Define Eps
    const double EPS = 0.0001;

    // Check results
    ASSERT_NEAR( IMG::PixelRGB_d::Black()[0], 0, EPS );
    ASSERT_NEAR( IMG::PixelRGB_d::Black()[1], 0, EPS );
    ASSERT_NEAR( IMG::PixelRGB_d::Black()[2], 0, EPS );
    
    ASSERT_NEAR( IMG::PixelRGB_df::Black()[0],-1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_df::Black()[1],-1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_df::Black()[2],-1, EPS );

    ASSERT_EQ( IMG::PixelRGB_u8::Black()[0],  IMG::ChannelTypeUInt8::minValue );
    ASSERT_EQ( IMG::PixelRGB_u8::Black()[1],  IMG::ChannelTypeUInt8::minValue );
    ASSERT_EQ( IMG::PixelRGB_u8::Black()[2],  IMG::ChannelTypeUInt8::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u12::Black()[0], IMG::ChannelTypeUInt12::minValue );
    ASSERT_EQ( IMG::PixelRGB_u12::Black()[1], IMG::ChannelTypeUInt12::minValue );
    ASSERT_EQ( IMG::PixelRGB_u12::Black()[2], IMG::ChannelTypeUInt12::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u14::Black()[0], IMG::ChannelTypeUInt14::minValue );
    ASSERT_EQ( IMG::PixelRGB_u14::Black()[1], IMG::ChannelTypeUInt14::minValue );
    ASSERT_EQ( IMG::PixelRGB_u14::Black()[2], IMG::ChannelTypeUInt14::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u16::Black()[0], IMG::ChannelTypeUInt16::minValue );
    ASSERT_EQ( IMG::PixelRGB_u16::Black()[1], IMG::ChannelTypeUInt16::minValue );
    ASSERT_EQ( IMG::PixelRGB_u16::Black()[2], IMG::ChannelTypeUInt16::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u32::Black()[0], IMG::ChannelTypeUInt32::minValue );
    ASSERT_EQ( IMG::PixelRGB_u32::Black()[1], IMG::ChannelTypeUInt32::minValue );
    ASSERT_EQ( IMG::PixelRGB_u32::Black()[2], IMG::ChannelTypeUInt32::minValue );

}

/**
 * Check the White Operator
*/
TEST( PixelRGB, White_Operator ){
    
    // Define Eps
    const double EPS = 0.0001;

    // Check results
    ASSERT_NEAR( IMG::PixelRGB_d::White()[0], 1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_d::White()[1], 1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_d::White()[2], 1, EPS );
    
    ASSERT_NEAR( IMG::PixelRGB_df::White()[0], 1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_df::White()[1], 1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_df::White()[2], 1, EPS );
    
    ASSERT_EQ( IMG::PixelRGB_u8::White()[0],  IMG::ChannelTypeUInt8::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u8::White()[1],  IMG::ChannelTypeUInt8::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u8::White()[2],  IMG::ChannelTypeUInt8::maxValue );
    
    ASSERT_EQ( IMG::PixelRGB_u12::White()[0], IMG::ChannelTypeUInt12::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u12::White()[1], IMG::ChannelTypeUInt12::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u12::White()[2], IMG::ChannelTypeUInt12::maxValue );
    
    ASSERT_EQ( IMG::PixelRGB_u14::White()[0], IMG::ChannelTypeUInt14::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u14::White()[1], IMG::ChannelTypeUInt14::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u14::White()[2], IMG::ChannelTypeUInt14::maxValue );
    
    ASSERT_EQ( IMG::PixelRGB_u16::White()[0], IMG::ChannelTypeUInt16::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u16::White()[1], IMG::ChannelTypeUInt16::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u16::White()[2], IMG::ChannelTypeUInt16::maxValue );
    
    ASSERT_EQ( IMG::PixelRGB_u32::White()[0], IMG::ChannelTypeUInt32::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u32::White()[1], IMG::ChannelTypeUInt32::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u32::White()[2], IMG::ChannelTypeUInt32::maxValue );

}


/**
 * Check the Red Operator
*/
TEST( PixelRGB, Red_Operator ){
    
    // Define Eps
    const double EPS = 0.0001;

    // Check results
    ASSERT_NEAR( IMG::PixelRGB_d::Red()[0], 1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_d::Red()[1], 0, EPS );
    ASSERT_NEAR( IMG::PixelRGB_d::Red()[2], 0, EPS );
    
    ASSERT_NEAR( IMG::PixelRGB_df::Red()[0], 1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_df::Red()[1],-1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_df::Red()[2],-1, EPS );
    
    ASSERT_EQ( IMG::PixelRGB_u8::Red()[0],  IMG::ChannelTypeUInt8::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u8::Red()[1],  IMG::ChannelTypeUInt8::minValue );
    ASSERT_EQ( IMG::PixelRGB_u8::Red()[2],  IMG::ChannelTypeUInt8::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u12::Red()[0], IMG::ChannelTypeUInt12::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u12::Red()[1], IMG::ChannelTypeUInt12::minValue );
    ASSERT_EQ( IMG::PixelRGB_u12::Red()[2], IMG::ChannelTypeUInt12::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u14::Red()[0], IMG::ChannelTypeUInt14::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u14::Red()[1], IMG::ChannelTypeUInt14::minValue );
    ASSERT_EQ( IMG::PixelRGB_u14::Red()[2], IMG::ChannelTypeUInt14::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u16::Red()[0], IMG::ChannelTypeUInt16::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u16::Red()[1], IMG::ChannelTypeUInt16::minValue );
    ASSERT_EQ( IMG::PixelRGB_u16::Red()[2], IMG::ChannelTypeUInt16::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u32::Red()[0], IMG::ChannelTypeUInt32::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u32::Red()[1], IMG::ChannelTypeUInt32::minValue );
    ASSERT_EQ( IMG::PixelRGB_u32::Red()[2], IMG::ChannelTypeUInt32::minValue );

}


/**
 * Check the Green Operator
*/
TEST( PixelRGB, Green_Operator ){
    
    // Define Eps
    const double EPS = 0.0001;

    // Check results
    ASSERT_NEAR( IMG::PixelRGB_d::Green()[0], 0, EPS );
    ASSERT_NEAR( IMG::PixelRGB_d::Green()[1], 1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_d::Green()[2], 0, EPS );
    
    ASSERT_NEAR( IMG::PixelRGB_df::Green()[0],-1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_df::Green()[1], 1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_df::Green()[2],-1, EPS );
    
    ASSERT_EQ( IMG::PixelRGB_u8::Green()[0],  IMG::ChannelTypeUInt8::minValue );
    ASSERT_EQ( IMG::PixelRGB_u8::Green()[1],  IMG::ChannelTypeUInt8::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u8::Green()[2],  IMG::ChannelTypeUInt8::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u12::Green()[0], IMG::ChannelTypeUInt12::minValue );
    ASSERT_EQ( IMG::PixelRGB_u12::Green()[1], IMG::ChannelTypeUInt12::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u12::Green()[2], IMG::ChannelTypeUInt12::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u14::Green()[0], IMG::ChannelTypeUInt14::minValue );
    ASSERT_EQ( IMG::PixelRGB_u14::Green()[1], IMG::ChannelTypeUInt14::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u14::Green()[2], IMG::ChannelTypeUInt14::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u16::Green()[0], IMG::ChannelTypeUInt16::minValue );
    ASSERT_EQ( IMG::PixelRGB_u16::Green()[1], IMG::ChannelTypeUInt16::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u16::Green()[2], IMG::ChannelTypeUInt16::minValue );
    
    ASSERT_EQ( IMG::PixelRGB_u32::Green()[0], IMG::ChannelTypeUInt32::minValue );
    ASSERT_EQ( IMG::PixelRGB_u32::Green()[1], IMG::ChannelTypeUInt32::maxValue );
    ASSERT_EQ( IMG::PixelRGB_u32::Green()[2], IMG::ChannelTypeUInt32::minValue );

}


/**
 * Check the Red Operator
*/
TEST( PixelRGB, Blue_Operator ){
    
    // Define Eps
    const double EPS = 0.0001;

    // Check results
    ASSERT_NEAR( IMG::PixelRGB_d::Blue()[0], 0, EPS );
    ASSERT_NEAR( IMG::PixelRGB_d::Blue()[1], 0, EPS );
    ASSERT_NEAR( IMG::PixelRGB_d::Blue()[2], 1, EPS );
    
    ASSERT_NEAR( IMG::PixelRGB_df::Blue()[0],-1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_df::Blue()[1],-1, EPS );
    ASSERT_NEAR( IMG::PixelRGB_df::Blue()[2], 1, EPS );
    
    ASSERT_EQ( IMG::PixelRGB_u8::Blue()[0],  IMG::ChannelTypeUInt8::minValue );
    ASSERT_EQ( IMG::PixelRGB_u8::Blue()[1],  IMG::ChannelTypeUInt8::minValue );
    ASSERT_EQ( IMG::PixelRGB_u8::Blue()[2],  IMG::ChannelTypeUInt8::maxValue );
    
    ASSERT_EQ( IMG::PixelRGB_u12::Blue()[0], IMG::ChannelTypeUInt12::minValue );
    ASSERT_EQ( IMG::PixelRGB_u12::Blue()[1], IMG::ChannelTypeUInt12::minValue );
    ASSERT_EQ( IMG::PixelRGB_u12::Blue()[2], IMG::ChannelTypeUInt12::maxValue );
    
    ASSERT_EQ( IMG::PixelRGB_u14::Blue()[0], IMG::ChannelTypeUInt14::minValue );
    ASSERT_EQ( IMG::PixelRGB_u14::Blue()[1], IMG::ChannelTypeUInt14::minValue );
    ASSERT_EQ( IMG::PixelRGB_u14::Blue()[2], IMG::ChannelTypeUInt14::maxValue );
    
    ASSERT_EQ( IMG::PixelRGB_u16::Blue()[0], IMG::ChannelTypeUInt16::minValue );
    ASSERT_EQ( IMG::PixelRGB_u16::Blue()[1], IMG::ChannelTypeUInt16::minValue );
    ASSERT_EQ( IMG::PixelRGB_u16::Blue()[2], IMG::ChannelTypeUInt16::maxValue );
    
    ASSERT_EQ( IMG::PixelRGB_u32::Blue()[0], IMG::ChannelTypeUInt32::minValue );
    ASSERT_EQ( IMG::PixelRGB_u32::Blue()[1], IMG::ChannelTypeUInt32::minValue );
    ASSERT_EQ( IMG::PixelRGB_u32::Blue()[2], IMG::ChannelTypeUInt32::maxValue );

}


