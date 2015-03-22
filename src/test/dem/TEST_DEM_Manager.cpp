/**
 * @file    TEST_DEM_Manager.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/dem/A_DEM_IO_Driver_FLAT.hpp"
#include "../../lib/dem/An_Elevation_Tile.hpp"
#include "../../lib/dem/DEM_Manager.hpp"

using namespace GEO;

/**
 * Test the DEM Manager Constructors
*/
TEST( DEM_Manager, Constructors ){

    // Create a dem manager
    DEM::DEM_Manager manager;
    
    ASSERT_EQ( manager.Get_Number_Of_DEM_IO_Drivers(), 0 );
    ASSERT_EQ( manager.Get_DEM_IO_Drivers().size(), 0 );
}


/**
 * Test the Flat Elevation Manager
*/
TEST( DEM_Manager, Create_Elevation_Tile_FLAT_Driver_01 ){

    // Misc Variable
    const double eps = 0.0001;

    // Create the DEM Manager
    DEM::DEM_Manager manager;

    // Add the flat io manager
    const double exp_elevation = 1234;
    DEM::A_DEM_IO_Driver_Base::ptr_t flat_driver( new DEM::A_DEM_IO_Driver_Flat(exp_elevation));
    manager.Add_DEM_IO_Driver( flat_driver );

    // Check the manager for the driver
    ASSERT_EQ( manager.Get_Number_Of_DEM_IO_Drivers(), 1 );
    ASSERT_NE( manager.Get_DEM_IO_Drivers()[0], nullptr );
    ASSERT_EQ( manager.Get_DEM_IO_Drivers()[0]->Get_DEM_IO_Driver_Type(), DEM::DEM_IO_Driver_Type::FLAT );

    // Define the query characteristics
    const CRD::CoordinateUTM_d min_corner(11, true, 39, -119);
    const A_Size<int> tile_size(1024, 2048);
    const double tile_gsd = 0.25;

    // Build an Elevation tile
    DEM::ElevationTileUTM_d::ptr_t elevation_tile = manager.Create_Elevation_Tile( min_corner,
                                                                                   tile_size,
                                                                                   tile_gsd );
    
    // Make sure the tile is not null
    ASSERT_NE( elevation_tile, nullptr );
    
    // Check the size and values
    ASSERT_EQ( elevation_tile->Rows(), tile_size.Height());
    ASSERT_EQ( elevation_tile->Cols(), tile_size.Width());
    for( int r=0; r<elevation_tile->Rows(); r++ )
    for( int c=0; c<elevation_tile->Cols(); c++ )
        ASSERT_NEAR( (*elevation_tile)(r,c), exp_elevation, eps );
}

