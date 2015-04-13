/**
 * @file    TEST_CoordinateGeographic.cpp
 * @author  Marvin Smith
 * @date    3/23/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>
#include <GeoExplore/coordinate/CoordinateGeographic.hpp>


using namespace GEO;

/**
 * Constructor
*/
TEST( CoordinateGeographic, Constructor ){

    // Run empty constructor
    CRD::CoordinateGeographic_d coord01;

    // Run Parameterized Constructor
    CRD::CoordinateGeographic_d coord02(Datum::NAD83 );
    CRD::CoordinateGeographic_d coord03( 39.1, -120.1 );
    CRD::CoordinateGeographic_d coord04( 39.1, -120.1, 100 );
    CRD::CoordinateGeographic_d coord05( 39.1, -120.1, 100, Datum::NAD83 );
    CRD::CoordinateGeographic_d coord06( 39.1, -120.1, Datum::NAD83 );

    ASSERT_NEAR( coord01.latitude_degrees(), 0, 0.00001 );
    ASSERT_NEAR( coord01.longitude_degrees(), 0, 0.00001 );
    ASSERT_NEAR( coord01.altitude_meters(), 0, 0.00001 );
    ASSERT_EQ( coord01.datum(), Datum::WGS84 );
    
    ASSERT_NEAR( coord02.latitude_degrees(), 0, 0.00001 );
    ASSERT_NEAR( coord02.longitude_degrees(), 0, 0.00001 );
    ASSERT_NEAR( coord02.altitude_meters(), 0, 0.00001 );
    ASSERT_EQ( coord02.datum(), Datum::NAD83 );
    
    ASSERT_NEAR( coord03.latitude_degrees(), 39.1, 0.00001 );
    ASSERT_NEAR( coord03.longitude_degrees(), -120.1, 0.00001 );
    ASSERT_NEAR( coord03.altitude_meters(), 0, 0.00001 );
    ASSERT_EQ( coord03.datum(), Datum::WGS84 );
    
    ASSERT_NEAR( coord04.latitude_degrees(), 39.1, 0.00001 );
    ASSERT_NEAR( coord04.longitude_degrees(), -120.1, 0.00001 );
    ASSERT_NEAR( coord04.altitude_meters(), 100, 0.00001 );
    ASSERT_EQ( coord04.datum(), Datum::WGS84 );
    
    ASSERT_NEAR( coord05.latitude_degrees(), 39.1, 0.00001 );
    ASSERT_NEAR( coord05.longitude_degrees(), -120.1, 0.00001 );
    ASSERT_NEAR( coord05.altitude_meters(), 100, 0.00001 );
    ASSERT_EQ( coord05.datum(), Datum::NAD83 );
    
    ASSERT_NEAR( coord06.latitude_degrees(), 39.1, 0.00001 );
    ASSERT_NEAR( coord06.longitude_degrees(), -120.1, 0.00001 );
    ASSERT_NEAR( coord06.altitude_meters(), 0, 0.00001 );
    ASSERT_EQ( coord06.datum(), Datum::NAD83 );

}

/**
 * Test Addition
*/
TEST( CoordinateGeographic, Addition_Operator ){

    // EPS
    const double eps = 0.0001;

    // Create the coordinates
    CRD::CoordinateGeographic_d coordinate01( 12,-23, 123, Datum::WGS84 );
    CRD::CoordinateGeographic_d coordinate02(-12,-23, 123, Datum::WGS84 );
    
    // Add
    CRD::CoordinateGeographic_d coordinate03 = coordinate01 + coordinate02;

    // Check values
    ASSERT_NEAR( coordinate03.latitude_degrees(),  0, eps );
    ASSERT_NEAR( coordinate03.longitude_degrees(),-46, eps );
    ASSERT_NEAR( coordinate03.altitude_meters(),  246, eps );
    ASSERT_EQ( coordinate03.datum(), Datum::WGS84 );
}


/**
 * Test Subtraction
*/
TEST( CoordinateGeographic, Subtraction_Operator ){

    // EPS
    const double eps = 0.0001;

    // Create the coordinates
    CRD::CoordinateGeographic_d coordinate01( 12,-23, 123, Datum::WGS84 );
    CRD::CoordinateGeographic_d coordinate02(-12,-23, 123, Datum::WGS84 );
    
    // Subtract
    CRD::CoordinateGeographic_d coordinate03 = coordinate01 - coordinate02;

    // Check values
    ASSERT_NEAR( coordinate03.latitude_degrees(), 24, eps );
    ASSERT_NEAR( coordinate03.longitude_degrees(), 0, eps );
    ASSERT_NEAR( coordinate03.altitude_meters(), 0, eps );
    ASSERT_EQ( coordinate03.datum(), Datum::WGS84 );
}

/**
 * Test the Vincenty Distance
 */
TEST( CoordinateGeographic, Distance_Vincenty )
{
    // EPS 
    const double eps = 0.001;

    // TEST 01 - Same Coordinate
    CRD::CoordinateGeographic_d coordinate01( 39.53699, -119.814475, 9000 );
    CRD::CoordinateGeographic_d coordinate02( 39.53699, -119.814475, 9000 );
    double dist01 = CRD::CoordinateGeographic_d::Distance_Vincenty( coordinate01, coordinate02 );

    const double exp_dist01 = 0;
    ASSERT_NEAR( dist01, exp_dist01, eps );

    // TEST 02 - Same Coordinate, different elevations
    CRD::CoordinateGeographic_d coordinate03( 39.53699, -119.814475, 9000 );
    CRD::CoordinateGeographic_d coordinate04( 39.53699, -119.814475, 8000 );
    double dist02 = CRD::CoordinateGeographic_d::Distance_Vincenty( coordinate03, coordinate04 );

    const double exp_dist02 = 1000;
    ASSERT_NEAR( dist02, exp_dist02, eps );


    // TEST 03 - Different Coordinates
    CRD::CoordinateGeographic_d coordinate05( 39.53699, -119.814475, 9000 );
    CRD::CoordinateGeographic_d coordinate06( 39.404099, -119.746498, 9000 );
    double dist03 = CRD::CoordinateGeographic_d::Distance_Vincenty( coordinate05, coordinate06 );

    const double exp_dist03 = 15871.374;
    ASSERT_NEAR( dist03, exp_dist03, eps );

}

