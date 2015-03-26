/**
 * @file    TEST_Enumerations.cpp
 * @author  Marvin Smith
 * @date    3/25/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/core/Enumerations.hpp"

using namespace GEO;

/**
 * Test the Datum Values
*/
TEST( Datum, static_casts ){

    ASSERT_EQ( static_cast<uint8_t>(Datum::UNKNOWN), 0 );
    ASSERT_EQ( static_cast<uint8_t>(Datum::NAD83), 1 );
    ASSERT_EQ( static_cast<uint8_t>(Datum::WGS84),2 );

}

/**
 * Test Datum to String
*/
TEST( Datum, DatumToString ){

    ASSERT_EQ( DatumToString(Datum::UNKNOWN), "UNKNOWN" );
    ASSERT_EQ( DatumToString(Datum::NAD83),   "NAD83" );
    ASSERT_EQ( DatumToString(Datum::WGS84),   "WGS84" );
}

/**
  * Test string to datum
 */
TEST( Datum, StringToDatum ){

    ASSERT_EQ( StringToDatum("unkonwn"), Datum::UNKNOWN );
    ASSERT_EQ( StringToDatum("WGS84"),   Datum::WGS84 );
    ASSERT_EQ( StringToDatum("wgs84"),   Datum::WGS84 );
    ASSERT_EQ( StringToDatum("nad83"),   Datum::NAD83 );
    ASSERT_EQ( StringToDatum("NAD83"),   Datum::NAD83 );

}

