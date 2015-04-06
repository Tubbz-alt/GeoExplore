/**
 * @file    TEST_MetadataItem.cpp
 * @author  Marvin Smith
 * @date    3/5/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <image/MetadataItem.hpp>

using namespace GEO;

/**
 * Test the Constructors
 */
TEST( MetadataItem, Constructors )
{
    // Test Default Constructor
    IMG::MetadataItem item01;
    ASSERT_EQ( item01.Key(), "" );
    ASSERT_EQ( item01.Value<std::string>(), "" );

    // Test String/String Constructor
    IMG::MetadataItem item02("Key","0.1");
    ASSERT_EQ( item02.Key(), "Key");
    ASSERT_EQ( item02.Value<std::string>(), "0.1" );

    // Test String/Double Constructor
    IMG::MetadataItem item03("Key",0.1);
    ASSERT_EQ( item03.Key(), "Key");
    ASSERT_EQ( item03.Value<std::string>(), "0.1");
    ASSERT_NEAR( item03.Value<double>(), 0.1, 0.0001);
}

