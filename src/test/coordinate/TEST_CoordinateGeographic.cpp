/**
 * @file    TEST_CoordinateGeographic.cpp
 * @author  Marvin Smith
 * @date    3/23/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/core/Enumerations.hpp"
#include "../../lib/coordinate/CoordinateGeographic.hpp"


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


