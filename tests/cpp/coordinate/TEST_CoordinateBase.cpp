/**
 * @file    TEST_CoordinateBase.cpp
 * @author  Marvin Smith
 * @date    4/16/2014
 */
#include <gtest/gtest.h>

/// GeoExplore Library
#include <GeoExplore.hpp>

/**
 * Test the CoordinateBase constructors
 */
TEST( CoordinateBase, Constructors ){

    // create a blank coordinate base
    GEO::CoordinateBase<double> coord01;
    ASSERT_NEAR( coord01.altitude(), 0, 0.0001 );
    ASSERT_EQ( coord01.datum(), GEO::Datum::WGS84 );
    ASSERT_EQ( coord01.type(), GEO::CoordinateType::Base );

    // create a coordinate base from parameters
    GEO::CoordinateBase<double> coord02( 5000, GEO::Datum::NAD83 );
    ASSERT_NEAR( coord02.altitude(), 5000, 0.0001 );
    ASSERT_EQ( coord02.datum(), GEO::Datum::NAD83 );
    ASSERT_EQ( coord02.type(), GEO::CoordinateType::Base );

}

