/**
 * @file    TEST_ChannelType.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/image/ChannelType.hpp"

using namespace GEO;

/**
 * Test the Channeltype double
 */
TEST( ChannelType, ChannelTypeDouble ){

    // Check the accumulator type
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeDouble::accumulator_type, double>();
    
    // Check the datatype
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeDouble::type, double>();

    // Check the max value
    ASSERT_NEAR( IMG::ChannelTypeDouble::maxValue, 1, 0.0001 );
    
    // Check the min value
    ASSERT_NEAR( IMG::ChannelTypeDouble::minValue, 0, 0.0001 );
}


/**
 * Test the Channeltype double free
 */
TEST( ChannelType, ChannelTypeDoubleFree ){

    // Check the accumulator type
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeDoubleFree::accumulator_type, double>();
    
    // Check the datatype
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeDoubleFree::type, double>();

    // Check the max value
    ASSERT_NEAR( IMG::ChannelTypeDoubleFree::maxValue, 1, 0.0001 );
    
    // Check the min value
    ASSERT_NEAR( IMG::ChannelTypeDoubleFree::minValue, -1, 0.0001 );
}

/**
 * Test the ChannelType UInt8
 */
TEST( ChannelType, ChannelTypeUInt8 ){

    // Check the accumulator type
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeUInt8::accumulator_type, uint16_t>();

    // Check the datatype
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeUInt8::type, uint8_t>();

    // Check the max value
    ASSERT_EQ( IMG::ChannelTypeUInt8::maxValue, 255 );
    
    // Check the min value
    ASSERT_EQ( IMG::ChannelTypeUInt8::minValue, 0 );

}

/**
 * Test the ChannelType UInt12
 */
TEST( ChannelType, ChannelTypeUInt12 ){

    // Check the accumulator type
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeUInt12::accumulator_type, uint32_t>();

    // Check the datatype
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeUInt12::type, uint16_t>();

    // Check the max value
    ASSERT_EQ( IMG::ChannelTypeUInt12::maxValue, 4095 );
    
    // Check the min value
    ASSERT_EQ( IMG::ChannelTypeUInt12::minValue, 0 );

}


/**
 * Test the ChannelType UInt14
 */
TEST( ChannelType, ChannelTypeUInt14 ){

    // Check the accumulator type
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeUInt14::accumulator_type, uint32_t>();

    // Check the datatype
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeUInt14::type, uint16_t>();

    // Check the max value
    ASSERT_EQ( IMG::ChannelTypeUInt14::maxValue, 16383 );
    
    // Check the min value
    ASSERT_EQ( IMG::ChannelTypeUInt14::minValue, 0 );

}

/**
 * Test the ChannelType UInt16
 */
TEST( ChannelType, ChannelTypeUInt16 ){

    // Check the accumulator type
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeUInt16::accumulator_type, uint32_t>();

    // Check the datatype
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeUInt16::type, uint16_t>();

    // Check the max value
    ASSERT_EQ( IMG::ChannelTypeUInt16::maxValue, 65535 );
    
    // Check the min value
    ASSERT_EQ( IMG::ChannelTypeUInt16::minValue, 0 );

}


/**
 * Test the ChannelType UInt32
 */
TEST( ChannelType, ChannelTypeUInt32 ){

    // Check the accumulator type
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeUInt32::accumulator_type, uint64_t>();

    // Check the datatype
    ::testing::StaticAssertTypeEq<typename IMG::ChannelTypeUInt32::type, uint32_t>();

    // Check the max value
    ASSERT_EQ( IMG::ChannelTypeUInt32::maxValue, 4294967295);
    
    // Check the min value
    ASSERT_EQ( IMG::ChannelTypeUInt32::minValue, 0 );

}


