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
    ASSERT_NEAR( GEO::IMG::ChannelTypeDouble::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::IMG::ChannelTypeDouble::maxValue, 1, 0.00001 );

    // test the char
    ASSERT_NEAR( GEO::IMG::ChannelTypeUInt8::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::IMG::ChannelTypeUInt8::maxValue, std::pow((int)2, (int)8)-1, 0.00001 );
    
    // test the uint12
    ASSERT_NEAR( GEO::IMG::ChannelTypeUInt12::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::IMG::ChannelTypeUInt12::maxValue, std::pow((int)2, (int)12)-1, 0.00001 );
    
    // test the uint14
    ASSERT_NEAR( GEO::IMG::ChannelTypeUInt14::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::IMG::ChannelTypeUInt14::maxValue, std::pow((int)2, (uint64_t)14)-1, 0.00001 );

    // test the uint16
    ASSERT_NEAR( GEO::IMG::ChannelTypeUInt16::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::IMG::ChannelTypeUInt16::maxValue, std::pow((int)2, (uint64_t)16)-1, 0.00001 );

    // test the uint32
    ASSERT_NEAR( GEO::IMG::ChannelTypeUInt32::minValue, 0, 0.00001 );
    ASSERT_NEAR( GEO::IMG::ChannelTypeUInt32::maxValue, std::pow((int)2, (uint64_t)32)-1, 0.00001 );

}

/**
 * Test the Range Cast
*/
TEST( ChannelType, RangeCast ){

    // convert a double to uint8
    uint8_t result01 = GEO::IMG::range_cast<GEO::IMG::ChannelTypeDouble,GEO::IMG::ChannelTypeUInt8>(0.5);
    ASSERT_EQ( 255/2, result01);
    
    // convert a uint8_t to double free
    double result02 = GEO::IMG::range_cast<GEO::IMG::ChannelTypeUInt8,GEO::IMG::ChannelTypeDoubleFree>(100);
    ASSERT_NEAR( 100, result02, 0.0001 );
    
    double result03 = GEO::IMG::range_cast<GEO::IMG::ChannelTypeDouble,GEO::IMG::ChannelTypeDoubleFree>(0.5);
    ASSERT_NEAR( 0.5, result03, 0.0001 );

    double result04 = GEO::IMG::range_cast<GEO::IMG::ChannelTypeUInt16,GEO::IMG::ChannelTypeDoubleFree>(65535);
    ASSERT_NEAR( 65535, result04, 0.0001 );

}


