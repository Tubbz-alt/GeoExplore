/**
 * @file    TEST_An_Elevation_Tile.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/coordinate/CoordinateUTM.hpp"
#include "../../lib/dem/An_Elevation_Tile.hpp"

using namespace GEO;


/**
 * Test the Default Constructor
*/
TEST( An_Elevation_Tile, Constructor_UTM_d ){

    // Define expected values
    const A_Size<int> exp_tile_size( 1024, 2048 );
    const double exp_gsd = 0.25;
    const CRD::CoordinateUTM_d exp_corner_bl( 11, false,   1,   2,   3);
    const CRD::CoordinateUTM_d exp_corner_br( 11, false, 257, 514,   3);
    const CRD::CoordinateUTM_d exp_corner_tl( 11, false,   1,   2,   3);
    const CRD::CoordinateUTM_d exp_corner_tr( 11, false, 257, 514,   3);


    // Define the exp and distance values
    const double exp_distance = 0;
    const double eps = 0.0001;

    // Create Tile
    DEM::An_Elevation_Tile<CRD::CoordinateUTM_d,double> elevation_tile( exp_corner_bl,
                                                                        exp_tile_size,
                                                                        exp_gsd );

    // Check the GSD
    ASSERT_NEAR( elevation_tile.Get_GSD(), exp_gsd, eps );

    // Check the Corner
    ASSERT_NEAR( CRD::CoordinateUTM_d::Distance(elevation_tile.Get_Corner_TL(), exp_corner_tl ), exp_distance, 0.0001 );
    ASSERT_NEAR( CRD::CoordinateUTM_d::Distance(elevation_tile.Get_Corner_TR(), exp_corner_tr ), exp_distance, 0.0001 );
    ASSERT_NEAR( CRD::CoordinateUTM_d::Distance(elevation_tile.Get_Corner_BL(), exp_corner_bl ), exp_distance, 0.0001 );
    ASSERT_NEAR( CRD::CoordinateUTM_d::Distance(elevation_tile.Get_Corner_BR(), exp_corner_br ), exp_distance, 0.0001 );


}

