/**
 * @file    TEST_CoordinateConversion.cpp
 * @author  Marvin Smith
 * @date    4/28/2014
 */
#include <gtest/gtest.h>

#include <GeoExplore.hpp>

 /**
  * Test the Coordinate Conversion 
 */
 TEST( CoordinateConversion, Geodetic2UTM ){

    // create a geodetic coordinate
    GEO::CoordinateGeodetic_d coordinate01(0, 0, 0, GEO::Datum::WGS84);
    
    // convert the coordinate
    GEO::CoordinateUTM_d result01 = GEO::convert_coordinate( coordinate01 );

    // test the output
    ASSERT_EQ( GEO::Datum::WGS84, result01.datum() );
    ASSERT_EQ(         31, result01.zone() );
    ASSERT_NEAR( 166021.4, result01.easting(),  0.1 );
    ASSERT_NEAR(        0, result01.northing(), 0.1 );
    ASSERT_NEAR(        0, result01.altitude(), 0.1 );
    

}

