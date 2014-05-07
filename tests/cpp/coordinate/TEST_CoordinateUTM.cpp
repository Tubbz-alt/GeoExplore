/**
 * @file    TEST_CoordinateUTM.cpp
 * @author  Marvin Smith
 * @date    4/16/2014
 */
#include <gtest/gtest.h>

#include <GeoExplore.hpp>

/**
 * Test CoordinateUTM Constructors
 */
TEST( CoordinateUTM, Constructors ){

    // test 1
    GEO::CoordinateUTM_d test01( 11, 100, -100, 250, GEO::Datum::WGS84 );
    ASSERT_EQ(   test01.zone(),    11 );
    ASSERT_NEAR( test01.easting(), 100, 0.00001 );
    ASSERT_NEAR( test01.northing(), -100, 0.00001);
    ASSERT_NEAR( test01.altitude(), 250, 0.00001 );
    ASSERT_EQ( test01.datum(), GEO::Datum::WGS84 );

    // test 2
    GEO::CoordinateUTM_d test02;
    ASSERT_EQ( test02.zone(), 31 );
    ASSERT_NEAR( test02.easting(),  166021.4, 0.00001 );
    ASSERT_NEAR( test02.northing(), 0, 0.00001 );
    ASSERT_NEAR( test02.altitude(), 0, 0.00001 );
    ASSERT_EQ( test02.datum(), GEO::Datum::WGS84 );

}

