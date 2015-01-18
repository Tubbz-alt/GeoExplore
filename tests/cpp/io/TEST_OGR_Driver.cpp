/**
 *    @file    TEST_OGR_Driver.cpp
 *    @author  Marvin Smith
 *    @date    5/6/2014
*/
#include <gtest/gtest.h>

/// GeoExplore Libraries
#include <GeoExplore.hpp>

/**
 * Compute the UTM Zone
*/
TEST( OGR_Driver, computeUTMZone ){

    ASSERT_EQ( GEO::OGR::compute_UTM_Zone(   0), 31 );
    ASSERT_EQ( GEO::OGR::compute_UTM_Zone(  10), 32 );
    ASSERT_EQ( GEO::OGR::compute_UTM_Zone(  18), 34 );
    ASSERT_EQ( GEO::OGR::compute_UTM_Zone(-180),  1 );
    ASSERT_EQ( GEO::OGR::compute_UTM_Zone( 179), 60 );

}

/**
 * Convert Coordinate from UTM to Geographic
*/
TEST( OGR_Driver, convert_UTM2Geographic ){
   
    double newLatitude, newLongitude, newAltitude;
    
    // test first coordinate
    GEO::OGR::convert_UTM2Geographic( 31, 166021, 0, 0, 
                                    GEO::Datum::WGS84, GEO::Datum::WGS84, 
                                    newLatitude, newLongitude, newAltitude);
    ASSERT_NEAR( newLatitude, 0, 0.0001 );
    ASSERT_NEAR( newLongitude, 0, 0.0001 );
    ASSERT_NEAR( newAltitude, 0, 0.0001 );


    
}

/**
 * Convert Coordinate from Geographic to UTM
*/
TEST( OGR_Driver, convert_Geographic2UTM_fixedZone ){

    FAIL();

}

/**
 * Convert Coordinate from Geographic 2 UTM
*/
TEST( OGR_Driver, convert_Geographic2UTM ){

    FAIL();
}


