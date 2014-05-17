/**
 * @file    TEST_CoordinateConversion.cpp
 * @author  Marvin Smith
 * @date    4/28/2014
 */
#include <gtest/gtest.h>

/// GeoExplore Library
#include <GeoExplore.hpp>

/// C++ Libraries
#include <iostream>

/// Boost C++ Libraries
#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

using namespace std;


/**
 * Test the coordinate conversion given pointers
*/
TEST( CoordinateConversion, Geodetic2UTM_ptr ){

    // create a geodetic coordinate
    GEO::CoordinateGeodetic_d::ptr_t coordinate01( new GEO::CoordinateGeodetic_d(0, 0, 0, GEO::Datum::WGS84));
    
    // convert the coordinate
    GEO::CoordinateUTM_d::ptr_t result01 = boost::static_pointer_cast<GEO::CoordinateUTM_d>(GEO::convert_coordinate<double>( coordinate01, GEO::CoordinateType::UTM, coordinate01->datum() ));
    
    // test the output
    ASSERT_EQ( GEO::Datum::WGS84, result01->datum() );
    ASSERT_EQ(         31, result01->zone() );
    ASSERT_NEAR( 166021.4, result01->easting(),  0.1 );
    ASSERT_NEAR(        0, result01->northing(), 0.1 );
    ASSERT_NEAR(        0, result01->altitude(), 0.1 );

    // test the white house
    coordinate01->latitude()  = 38.8977;
    coordinate01->longitude() = -77.0365;
    coordinate01->altitude()  = 17;
    coordinate01->datum()     = GEO::Datum::WGS84;

    result01 = boost::static_pointer_cast<GEO::CoordinateUTM_d>(GEO::convert_coordinate<double>( coordinate01, GEO::CoordinateType::UTM, coordinate01->datum()));
    ASSERT_EQ( GEO::Datum::WGS84, result01->datum() );
    ASSERT_EQ( 18, result01->zone());
    ASSERT_NEAR( 323394, result01->easting(), 1 );
    ASSERT_NEAR( 4307396, result01->northing(), 1);
    ASSERT_NEAR( 17, result01->altitude(), 1 );


}


/**
 * Test the Coordinate Conversion 
*/
TEST( CoordinateConversion, Geodetic2UTM01_freeZone_sameDatum ){

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
    
    // test the white house
    coordinate01.latitude()  = 38.8977;
    coordinate01.longitude() = -77.0365;
    coordinate01.altitude()  = 17;
    coordinate01.datum()     = GEO::Datum::WGS84;

    result01 = GEO::convert_coordinate( coordinate01 );
    ASSERT_EQ( GEO::Datum::WGS84, result01.datum() );
    ASSERT_EQ( 18, result01.zone());
    ASSERT_NEAR( 323394, result01.easting(), 1 );
    ASSERT_NEAR( 4307396, result01.northing(), 1);
    ASSERT_NEAR( 17, result01.altitude(), 1 );
    
}


/**
 * Test Geodetic to UTM with a fixed Zone
*/
TEST( CoordinateConversion, Geodetic2UTM02_fixedZone_sameDatum ){

    // create a geodetic coordinate
    GEO::CoordinateGeodetic_d coordinate01(0, 0, 0, GEO::Datum::WGS84);
    
    // convert the coordinate
    GEO::CoordinateUTM_d result01 = GEO::convert_coordinate( coordinate01, 30 );

    // test the output
    ASSERT_EQ( GEO::Datum::WGS84, result01.datum() );
    ASSERT_EQ(          30, result01.zone() );
    ASSERT_NEAR( 833978.56, result01.easting(),  0.1 );
    ASSERT_NEAR(         0, result01.northing(), 0.1 );
    ASSERT_NEAR(         0, result01.altitude(), 0.1 );
    
    // test the white house
    coordinate01.latitude()  = 38.8977;
    coordinate01.longitude() = -77.0365;
    coordinate01.altitude()  = 17;
    coordinate01.datum()     = GEO::Datum::WGS84;

    result01 = GEO::convert_coordinate( coordinate01, 19 );
    ASSERT_EQ( GEO::Datum::WGS84, result01.datum() );
    ASSERT_EQ(        19, result01.zone());
    ASSERT_NEAR( -197379, result01.easting(), 1 );
    ASSERT_NEAR( 4336248, result01.northing(), 1);
    ASSERT_NEAR(      17, result01.altitude(), 1 );
    
}

/**
 * Test Geodetic to UTM with a free zone and different datum
*/
TEST( CoordinateConversion, Geodetic2UTM03_freeZone_differentDatum ){

    // create an empty Geodetic coordinate for testing
    GEO::CoordinateGeodetic_d coordinate01( 0, 0, 0, GEO::Datum::WGS84);
    
    // convert the coordinate
    GEO::CoordinateUTM_d result01 = GEO::convert_coordinate( coordinate01, GEO::Datum::NAD83);

    // validate the coordinate converts 
    ASSERT_EQ( GEO::Datum::NAD83, result01.datum());
    ASSERT_EQ( 31, result01.zone());
    ASSERT_NEAR( 166021.443, result01.easting(), 0.1);
    ASSERT_NEAR( 0, result01.northing(), 0.1 );
    ASSERT_NEAR( 0, result01.altitude(), 0.1 );

    // test the white house
    coordinate01.latitude()  = 38.8977;
    coordinate01.longitude() = -77.0365;
    coordinate01.altitude()  = 17;
    coordinate01.datum()     = GEO::Datum::WGS84;

    result01 = GEO::convert_coordinate( coordinate01 );
    ASSERT_EQ( GEO::Datum::WGS84, result01.datum() );
    ASSERT_EQ( 18, result01.zone());
    ASSERT_NEAR( 323394, result01.easting(), 1 );
    ASSERT_NEAR( 4307396, result01.northing(), 1);
    ASSERT_NEAR(      17, result01.altitude(), 1 );

    
}

/**
 * Test Geodetic to UTM with a fixed zone and different datum
*/
TEST( CoordinateConversion, Geodetic2UTM04_fixedZone_differentDatum ){

    // create an empty Geodetic coordinate for testing
    GEO::CoordinateGeodetic_d coordinate01( 0, 0, 0, GEO::Datum::WGS84);


    FAIL();
}

/**
 * Test the UTM to Geodetic
*/
TEST( CoordinateConversion, UTM2Geodetic01_freeZone_sameDatum ){

    // create a UTM Coordinate
    GEO::CoordinateUTM_d coordinate01;

    // convert the coordinate
    GEO::CoordinateGeodetic_d result01 = GEO::convert_coordinate( coordinate01 );

    // test the output
    ASSERT_EQ( GEO::Datum::WGS84, result01.datum() );
    ASSERT_NEAR( 0, result01.latitude(), 1 );
    ASSERT_NEAR( 0, result01.longitude(), 1);
    ASSERT_NEAR( 0, result01.altitude(), 1 );
    
    // test the white house
    coordinate01.datum()    = GEO::Datum::WGS84;
    coordinate01.zone()     = 18;
    coordinate01.easting()  = 323394;
    coordinate01.northing() = 4307396;
    coordinate01.altitude() = 17;

    // convert to geodetic
    result01 = GEO::convert_coordinate( coordinate01 );

    // test the output
    ASSERT_EQ( GEO::Datum::WGS84, result01.datum() );
    ASSERT_NEAR(  38.8977, result01.latitude() , 1 );
    ASSERT_NEAR( -77.0365, result01.longitude(), 1 );
    ASSERT_NEAR(       17, result01.altitude() , 1 );

}

