/**
 * @file    TEST_CoordinateGeodetic.cpp
 * @author  Marvin Smith
 * @date    4/16/2014
 */
#include <gtest/gtest.h>

#include <GeoExplore.hpp>

TEST( CoordinateGeodetic, Constructors ){

    // test 1
    GEO::CoordinateGeodetic_d test01;
    ASSERT_NEAR( test01.latitude(), 0, 0.000001 );
    ASSERT_NEAR( test01.longitude(), 0, 0.00001 );
    ASSERT_NEAR( test01.altitude(), 0, 0.00001 );
    ASSERT_EQ( test01.datum(), GEO::Datum::WGS84 );

    // test 2
    GEO::CoordinateGeodetic_d test02( 35, -117, 1000, GEO::Datum::NAD83 );
    ASSERT_NEAR( test02.latitude(), 35, 0.00001 );
    ASSERT_NEAR( test02.longitude(), -117, 0.00001 );
    ASSERT_NEAR( test02.altitude(), 1000, 0.00001 );
    ASSERT_EQ( test02.datum(), GEO::Datum::NAD83 );


}

