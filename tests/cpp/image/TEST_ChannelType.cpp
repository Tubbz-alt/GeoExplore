/**
 * @file    TEST_ChannelType.cpp
 * @author  Marvin Smith
 * @date    5/6/2014
*/
#include <gtest/gtest.h>

/// GeoExplore Library
#include <GeoExplore.hpp>

/// C++ Standard Library
#include <cmath>

/**
 * Test the ChannelType Ranges
*/
TEST( ChannelType, Ranges ){

    // test the double
    ASSERT_NEAR( GEO::ChannelTypeDouble::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::ChannelTypeDouble::maxValue, 1, 0.00001 );

    // test the char
    ASSERT_NEAR( GEO::ChannelTypeUInt8::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::ChannelTypeUInt8::maxValue, std::pow((int)2, (int)8)-1, 0.00001 );
    
    // test the uint12
    ASSERT_NEAR( GEO::ChannelTypeUInt12::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::ChannelTypeUInt12::maxValue, std::pow((int)2, (int)12)-1, 0.00001 );
    
    // test the uint14
    ASSERT_NEAR( GEO::ChannelTypeUInt14::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::ChannelTypeUInt14::maxValue, std::pow((int)2, (uint64_t)14)-1, 0.00001 );

    // test the uint16
    ASSERT_NEAR( GEO::ChannelTypeUInt16::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::ChannelTypeUInt16::maxValue, std::pow((int)2, (uint64_t)16)-1, 0.00001 );

    // test the uint32
    ASSERT_NEAR( GEO::ChannelTypeUInt32::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::ChannelTypeUInt32::maxValue, std::pow((int)2, (uint64_t)32)-1, 0.00001 );

}

/**
 * Test the Range Cast
*/
TEST( ChannelType, RangeCast ){

    // convert a double to uint8
    uint8_t result01 = GEO::range_cast<GEO::ChannelTypeDouble,GEO::ChannelTypeUInt8>(0.5);
    ASSERT_EQ( 255/2, result01);
    

}


