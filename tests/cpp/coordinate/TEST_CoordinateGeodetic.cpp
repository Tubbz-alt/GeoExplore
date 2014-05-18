/**
 * @file    TEST_CoordinateGeodetic.cpp
 * @author  Marvin Smith
 * @date    4/16/2014
 */
#include <gtest/gtest.h>

#include <GeoExplore.hpp>


/**
 * Test the Coordinate Geodetic Constructors
*/
TEST( CoordinateGeodetic, Constructors ){

    // test 1 (Default Constructor)
    GEO::CoordinateGeodetic_d test01;
    ASSERT_NEAR( test01.latitude(), 0, 0.000001 );
    ASSERT_NEAR( test01.longitude(), 0, 0.00001 );
    ASSERT_NEAR( test01.altitude(), 0, 0.00001 );
    ASSERT_EQ( test01.datum(), GEO::Datum::WGS84 );


    // test 2 (Parameterized Constructor )
    GEO::CoordinateGeodetic_d test02( 35, -117, 1000, GEO::Datum::NAD83 );
    ASSERT_NEAR( test02.latitude(), 35, 0.00001 );
    ASSERT_NEAR( test02.longitude(), -117, 0.00001 );
    ASSERT_NEAR( test02.altitude(), 1000, 0.00001 );
    ASSERT_EQ( test02.datum(), GEO::Datum::NAD83 );
    

    // test 3 (Parameterized Constructor)
    GEO::CoordinateGeodetic_d test03( GEO::Datum::EGM96 );
    ASSERT_NEAR( test03.latitude(), 0, 0.00001 );
    ASSERT_NEAR( test03.longitude(), 0, 0.00001 );
    ASSERT_NEAR( test03.altitude(), 0, 0.00001 );
    ASSERT_EQ( test03.datum(), GEO::Datum::EGM96 );

}

/**
 * Test the Getters and Setters 
*/
TEST( CoordinateGeodetic, GettersSetters ){

    // create an empty coordinate
    GEO::CoordinateGeodetic_d test01;

    // test
    ASSERT_NEAR( test01.latitude(), 0, 0.000001 );
    ASSERT_NEAR( test01.longitude(), 0, 0.00001 );
    ASSERT_NEAR( test01.altitude(), 0, 0.00001 );
    ASSERT_EQ( test01.datum(), GEO::Datum::WGS84 );

    // set the latitude
    test01.latitude() = 39;

    // test results
    ASSERT_NEAR( test01.latitude(), 39, 0.000001 );
    ASSERT_NEAR( test01.longitude(), 0, 0.00001 );
    ASSERT_NEAR( test01.altitude(), 0, 0.00001 );
    ASSERT_EQ( test01.datum(), GEO::Datum::WGS84 );
    
    // change the longitude
    test01.longitude() = -120.5;
    
    // test results
    ASSERT_NEAR( test01.latitude(), 39, 0.000001 );
    ASSERT_NEAR( test01.longitude(), -120.5, 0.00001 );
    ASSERT_NEAR( test01.altitude(), 0, 0.00001 );
    ASSERT_EQ( test01.datum(), GEO::Datum::WGS84 );
    
    // change the altitude
    test01.altitude() = 1205;

    // test results
    ASSERT_NEAR( test01.latitude(), 39, 0.000001 );
    ASSERT_NEAR( test01.longitude(), -120.5, 0.00001 );
    ASSERT_NEAR( test01.altitude(), 1205, 0.00001 );
    ASSERT_EQ( test01.datum(), GEO::Datum::WGS84 );

    // change the datum
    test01.datum() = GEO::Datum::EGM96;

    // test results
    ASSERT_NEAR( test01.latitude(), 39, 0.000001 );
    ASSERT_NEAR( test01.longitude(), -120.5, 0.00001 );
    ASSERT_NEAR( test01.altitude(), 1205, 0.00001 );
    ASSERT_EQ( test01.datum(), GEO::Datum::EGM96 );

}

/**
 * Test the Geodetic Coordinate Type Function
*/
TEST( CoordinateGeodetic, type ){

    ASSERT_EQ( GEO::CoordinateGeodetic_d().type(), GEO::CoordinateType::Geodetic );
    ASSERT_EQ( GEO::CoordinateGeodetic_i32().type(), GEO::CoordinateType::Geodetic );

}


