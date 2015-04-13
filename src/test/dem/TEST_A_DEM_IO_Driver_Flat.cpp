/**
 * @file    TEST_A_DEM_IO_Driver_Flat.cpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/dem/A_DEM_IO_Driver_Flat.hpp>

using namespace GEO;

/**
 * Test the flat constructor
*/
TEST( A_DEM_IO_Driver_Flat, Constructors )
{
    // Status
    Status status;

    // Define our elevation
    const double elevation = 100;

    // Create a DEM IO Driver
    DEM::A_DEM_IO_Driver_Flat driver(elevation);

    // Make sure its initialized
    ASSERT_EQ( driver.Initialize().Get_Status_Type(), StatusType::SUCCESS );

}


/**
 * Test the Query Elevation Method.
*/
TEST( A_DEM_IO_Driver_Flat, Query_Elevation_Meters )
{
    
    // Status
    Status status;

    // Define our epsilon
    const double eps = 0.0001;

    // Define our elevation
    const double elevation = 100;

    // Create a DEM IO Driver
    DEM::A_DEM_IO_Driver_Flat driver(elevation);


    // Check Coverage
    ASSERT_NEAR( driver.Query_Elevation_Meters( CRD::CoordinateGeographic_d( 23, 2), status ), elevation, eps );
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    ASSERT_NEAR( driver.Query_Elevation_Meters( CRD::CoordinateUTM_d( 3, true, 23, 2), status ), elevation, eps );
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    
    // Check type
    ASSERT_EQ( driver.Get_DEM_IO_Driver_Type(), DEM::DEM_IO_Driver_Type::FLAT );

}

/**
 * Test the Coverage Methods
*/
TEST( A_DEM_IO_Driver_Flat, Coverage ){

    // Elevation
    const double elevation = 102;

    // Create driver
    DEM::A_DEM_IO_Driver_Flat driver(elevation);

    // test 01 (Single Geographic Coordinate)
    ASSERT_TRUE( driver.Coverage( CRD::CoordinateGeographic_d(23, -1)));
    
    // test 02 (Single UTM Coordinate
    ASSERT_TRUE( driver.Coverage( CRD::CoordinateUTM_d(12, false, 23, -1)));
    
    // test 03 (Geographic Range)
    ASSERT_TRUE( driver.Coverage( CRD::CoordinateGeographic_d(-12, -12),
                                  CRD::CoordinateGeographic_d( 12,  12)));

    // test 04 (UTM Range)
    ASSERT_TRUE( driver.Coverage( CRD::CoordinateUTM_d(12, false, 10, 10),
                                  CRD::CoordinateUTM_d(13, true, 1, 32 )));



}


