/**
 * @file    TEST_PathFormatType.cpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/filesystem/PathFormatType.hpp>

using namespace GEO;

/**
 * Test the Path FOrmat Type Casts
*/
TEST( PathFormatType, static_casts )
{

    ASSERT_EQ( static_cast<uint8_t>(FS::PathFormatType::RELATIVE), 0 );
    ASSERT_EQ( static_cast<uint8_t>(FS::PathFormatType::ABSOLUTE), 1 );

}

