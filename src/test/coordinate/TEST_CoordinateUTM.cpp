/**
 * @file    TEST_CoordinateUTM.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/coordinate/CoordinateUTM.hpp"

using namespace GEO;

/**
 * Test the Coordinate UTM Constructor
*/
TEST( CoordinateUTM, Constructor_default ){

    // Create some coordinates
    CRD::CoordinateUTM_d    coordinate_d;
    CRD::CoordinateUTM<int> coordinate_i;

    // Eps
    const double eps = 0.0001;

    // Check the easting
    ASSERT_NEAR( coordinate_d.easting_meters(),  166021.4, eps );
    ASSERT_EQ( coordinate_i.easting_meters(), 166021 );

    // Check the northing
    ASSERT_NEAR( coordinate_d.northing_meters(), 0, eps );
    ASSERT_EQ( coordinate_i.northing_meters(), 0 );

    // Check the altitude
    ASSERT_NEAR( coordinate_d.altitude_meters(), 0, eps );
    ASSERT_EQ( coordinate_i.altitude_meters(), 0 );

    // Check the datum
    ASSERT_EQ( coordinate_d.datum(), Datum::WGS84 );
    ASSERT_EQ( coordinate_i.datum(), Datum::WGS84 );

    // Check hemisphere
    ASSERT_TRUE( coordinate_d.Is_Northern_Hemisphere() );
    ASSERT_TRUE( coordinate_i.Is_Northern_Hemisphere() );

}


/**
 * Check the Addition Operator 
*/
TEST( CoordinateUTM, AdditionOperator ){

    // Define the eps
    const double eps = 0.0001;

    // CoordinateUTM_d test
    CRD::CoordinateUTM_d coord_d_01( 11, true, 100, 200,-300 );
    CRD::CoordinateUTM_d coord_d_02( 11, true,-100, 100, 200 );
    CRD::CoordinateUTM_d coord_d_03( 13, true, 100, 200, 300 );
    CRD::CoordinateUTM_d coord_d_04( 11,false, 100, 200, 300 );
    
    // Check the diffs
    CRD::CoordinateUTM_d coord_sum_d_01 = coord_d_01 + coord_d_01;
    CRD::CoordinateUTM_d coord_sum_d_02 = coord_d_01 + coord_d_02;
    CRD::CoordinateUTM_d coord_sum_d_03 = coord_d_01 + coord_d_03;
    CRD::CoordinateUTM_d coord_sum_d_04 = coord_d_01 + coord_d_04;

    // Set our expected values
    CRD::CoordinateUTM_d exp_coord_sum_d_01( 11, true, 200,  400,-600);
    CRD::CoordinateUTM_d exp_coord_sum_d_02( 11, true,   0,  300,-100);
    CRD::CoordinateUTM_d exp_coord_sum_d_03( 11, true, 200,  400,   0);
    CRD::CoordinateUTM_d exp_coord_sum_d_04( 11, true, 200,  400,   0);

    // Validate the results
    ASSERT_EQ( coord_sum_d_01.zone(), 11 );
    ASSERT_EQ( coord_sum_d_02.zone(), 11 );
    ASSERT_EQ( coord_sum_d_03.zone(), 11 );
    ASSERT_EQ( coord_sum_d_04.zone(), 11 );
    
    ASSERT_TRUE( coord_sum_d_01.Is_Northern_Hemisphere() );
    ASSERT_TRUE( coord_sum_d_02.Is_Northern_Hemisphere() );
    ASSERT_TRUE( coord_sum_d_03.Is_Northern_Hemisphere() );
    ASSERT_TRUE( coord_sum_d_04.Is_Northern_Hemisphere() );

    ASSERT_EQ( coord_sum_d_01.datum(), Datum::WGS84 );
    ASSERT_EQ( coord_sum_d_02.datum(), Datum::WGS84 );
    ASSERT_EQ( coord_sum_d_03.datum(), Datum::WGS84 );
    ASSERT_EQ( coord_sum_d_01.datum(), Datum::WGS84 );

    ASSERT_NEAR( coord_sum_d_01.easting_meters(), exp_coord_sum_d_01.easting_meters(), eps );
    ASSERT_NEAR( coord_sum_d_02.easting_meters(), exp_coord_sum_d_02.easting_meters(), eps );
    ASSERT_NEAR( coord_sum_d_03.easting_meters(), exp_coord_sum_d_03.easting_meters(), eps );
    ASSERT_NEAR( coord_sum_d_04.easting_meters(), exp_coord_sum_d_04.easting_meters(), eps );
    
    
    ASSERT_NEAR( coord_sum_d_01.northing_meters(), exp_coord_sum_d_01.northing_meters(), eps );
    ASSERT_NEAR( coord_sum_d_02.northing_meters(), exp_coord_sum_d_02.northing_meters(), eps );
    ASSERT_NEAR( coord_sum_d_03.northing_meters(), exp_coord_sum_d_03.northing_meters(), eps );
    ASSERT_NEAR( coord_sum_d_04.northing_meters(), exp_coord_sum_d_04.northing_meters(), eps );
   

    ASSERT_NEAR( coord_sum_d_01.altitude_meters(), exp_coord_sum_d_01.altitude_meters(), eps );
    ASSERT_NEAR( coord_sum_d_02.altitude_meters(), exp_coord_sum_d_02.altitude_meters(), eps );
    ASSERT_NEAR( coord_sum_d_03.altitude_meters(), exp_coord_sum_d_03.altitude_meters(), eps );
    ASSERT_NEAR( coord_sum_d_04.altitude_meters(), exp_coord_sum_d_04.altitude_meters(), eps );
}


/**
 * Check the Subtraction Operator 
*/
TEST( CoordinateUTM, SubtractionOperator ){

    // Define the eps
    const double eps = 0.0001;

    // CoordinateUTM_d test
    CRD::CoordinateUTM_d coord_d_01( 11, true, 100, 200,-300 );
    CRD::CoordinateUTM_d coord_d_02( 11, true,-100, 100, 200 );
    CRD::CoordinateUTM_d coord_d_03( 13, true, 100, 200, 300 );
    CRD::CoordinateUTM_d coord_d_04( 11,false, 100, 200, 300 );
    
    // Check the diffs
    CRD::CoordinateUTM_d coord_diff_d_01 = coord_d_01 - coord_d_01;
    CRD::CoordinateUTM_d coord_diff_d_02 = coord_d_01 - coord_d_02;
    CRD::CoordinateUTM_d coord_diff_d_03 = coord_d_01 - coord_d_03;
    CRD::CoordinateUTM_d coord_diff_d_04 = coord_d_01 - coord_d_04;

    // Set our expected values
    CRD::CoordinateUTM_d exp_coord_diff_d_01( 11, true,   0,    0,   0);
    CRD::CoordinateUTM_d exp_coord_diff_d_02( 11, true, 200,  100,-500);
    CRD::CoordinateUTM_d exp_coord_diff_d_03( 11, true,   0,    0,-600);
    CRD::CoordinateUTM_d exp_coord_diff_d_04( 11, true,   0,    0,-600);

    // Validate the results
    ASSERT_EQ( coord_diff_d_01.zone(), 11 );
    ASSERT_EQ( coord_diff_d_02.zone(), 11 );
    ASSERT_EQ( coord_diff_d_03.zone(), 11 );
    ASSERT_EQ( coord_diff_d_04.zone(), 11 );
    
    ASSERT_TRUE( coord_diff_d_01.Is_Northern_Hemisphere() );
    ASSERT_TRUE( coord_diff_d_02.Is_Northern_Hemisphere() );
    ASSERT_TRUE( coord_diff_d_03.Is_Northern_Hemisphere() );
    ASSERT_TRUE( coord_diff_d_04.Is_Northern_Hemisphere() );

    ASSERT_EQ( coord_diff_d_01.datum(), Datum::WGS84 );
    ASSERT_EQ( coord_diff_d_02.datum(), Datum::WGS84 );
    ASSERT_EQ( coord_diff_d_03.datum(), Datum::WGS84 );
    ASSERT_EQ( coord_diff_d_01.datum(), Datum::WGS84 );

    ASSERT_NEAR( coord_diff_d_01.easting_meters(), exp_coord_diff_d_01.easting_meters(), eps );
    ASSERT_NEAR( coord_diff_d_02.easting_meters(), exp_coord_diff_d_02.easting_meters(), eps );
    ASSERT_NEAR( coord_diff_d_03.easting_meters(), exp_coord_diff_d_03.easting_meters(), eps );
    ASSERT_NEAR( coord_diff_d_04.easting_meters(), exp_coord_diff_d_04.easting_meters(), eps );
    
    
    ASSERT_NEAR( coord_diff_d_01.northing_meters(), exp_coord_diff_d_01.northing_meters(), eps );
    ASSERT_NEAR( coord_diff_d_02.northing_meters(), exp_coord_diff_d_02.northing_meters(), eps );
    ASSERT_NEAR( coord_diff_d_03.northing_meters(), exp_coord_diff_d_03.northing_meters(), eps );
    ASSERT_NEAR( coord_diff_d_04.northing_meters(), exp_coord_diff_d_04.northing_meters(), eps );
   

    ASSERT_NEAR( coord_diff_d_01.altitude_meters(), exp_coord_diff_d_01.altitude_meters(), eps );
    ASSERT_NEAR( coord_diff_d_02.altitude_meters(), exp_coord_diff_d_02.altitude_meters(), eps );
    ASSERT_NEAR( coord_diff_d_03.altitude_meters(), exp_coord_diff_d_03.altitude_meters(), eps );
    ASSERT_NEAR( coord_diff_d_04.altitude_meters(), exp_coord_diff_d_04.altitude_meters(), eps );
}


/**
 * Check the Mag2 Operator
*/
TEST( CoordinateUTM, Mag2 ){

    // EPS
    const double eps = 0.00001;

    // Create a UTM coordinate
    CRD::CoordinateUTM_d  utm_coord_01( 11, true, 1, 2, 3);

    ASSERT_NEAR( utm_coord_01.Mag2(), 14, eps );

}

/**
 * Check the Mag Operator
*/
TEST( CoordinateUTM, Mag ){

    // EPS
    const double eps = 0.0001;

    // Create a utm coordinate
    CRD::CoordinateUTM_d utm_coord_01( 11, true, 1, 2, 3);

    ASSERT_NEAR( utm_coord_01.Mag(), std::sqrt(14), eps );

}

/**
 * Check the Distance Operator
*/
TEST( CoordinateUTM, Distance ){

    // Create UTM Coordinates
    CRD::CoordinateUTM_d coord01( 11, true, 1, 2, 3);
    CRD::CoordinateUTM_d coord02( 11, true, -1, 2, 3);
    CRD::CoordinateUTM_d coord03( 11, true, -1,-2,-3);
    
    // Compute Distances
    ASSERT_NEAR( CRD::CoordinateUTM_d::Distance( coord01, coord01), 0, 0.0001 );
    ASSERT_NEAR( CRD::CoordinateUTM_d::Distance( coord02, coord02), 0, 0.0001 );
    ASSERT_NEAR( CRD::CoordinateUTM_d::Distance( coord03, coord03), 0, 0.0001 );
    ASSERT_NEAR( CRD::CoordinateUTM_d::Distance( coord01, coord02), 2, 0.0001 );
    ASSERT_NEAR( CRD::CoordinateUTM_d::Distance( coord01, coord03), std::sqrt(4+16+36), 0.0001 );
    ASSERT_NEAR( CRD::CoordinateUTM_d::Distance( coord02, coord01), 2, 0.0001 );
    ASSERT_NEAR( CRD::CoordinateUTM_d::Distance( coord03, coord01), std::sqrt(4+16+36), 0.0001 );


}

