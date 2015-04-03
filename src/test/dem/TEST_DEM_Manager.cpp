/**
 * @file    TEST_DEM_Manager.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/dem/A_DEM_IO_Driver_Flat.hpp"
#include "../../lib/dem/A_DEM_IO_Driver_SRTM.hpp"
#include "../../lib/dem/An_Elevation_Tile.hpp"
#include "../../lib/dem/DEM_Manager.hpp"
#include "../../lib/filesystem.hpp"
#include "../../lib/image/Image_Utilities.hpp"


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
 * Test Adding DEM IO Drivers that are invalid
*/
TEST( DEM_Manager, Add_DEM_Drivers_invalid ){

    // Create a DEM Manager
    DEM::DEM_Manager manager;

    // Add null manager
    manager.Add_DEM_IO_Driver( nullptr );

    // Define our SRTM path
    FS::FilesystemPath srtm_file_path = "data/unit-tests/dems/srtm";


    // Create SRTM Driver but do not initialize
    DEM::A_DEM_IO_Driver_SRTM::ptr_t  srtm_driver( new DEM::A_DEM_IO_Driver_SRTM(srtm_file_path));

    // Add uninitialized driver
    manager.Add_DEM_IO_Driver( srtm_driver );

    // Check the driver count
    ASSERT_EQ( manager.Get_Number_Of_DEM_IO_Drivers(), 0 );

}



/**
 * Test the Flat Elevation Manager
*/
TEST( DEM_Manager, Create_Elevation_Tile_Flat_Driver_01 ){

    // Misc Variable
    const double eps = 0.0001;
    Status status;

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
                                                                                   tile_gsd,
                                                                                   status );
    
    // Make sure succeeded
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );

    // Make sure the tile is not null
    ASSERT_NE( elevation_tile, nullptr );
    
    // Check the size and values
    ASSERT_EQ( elevation_tile->Rows(), tile_size.Height());
    ASSERT_EQ( elevation_tile->Cols(), tile_size.Width());
    for( int r=0; r<elevation_tile->Rows(); r++ )
    for( int c=0; c<elevation_tile->Cols(); c++ )
        ASSERT_NEAR( (*elevation_tile)(r,c), exp_elevation, eps );
}


/**********************************************************/
/*          Test the SRTM Dem Driver Create Tile          */
/**********************************************************/
TEST( DEM_Manager, Create_Elevation_Tile_utm )
{
    // Status
    Status status;


    // Set our desired tile size
    const A_Size<int> tile_size(500,500);


    // Set our desired GSD
    const double gsd = 1;


    // Define our SRTM path
    FS::FilesystemPath srtm_file_path = "data/unit-tests/dems/srtm";


    // Build the drivers
    DEM::A_DEM_IO_Driver_SRTM::ptr_t  driver( new DEM::A_DEM_IO_Driver_SRTM(srtm_file_path));
    

    // Check that the initialization method passes.
    ASSERT_EQ( driver->Initialize().Get_Status_Type(), StatusType::SUCCESS );


    // Make sure that we have 2 files loaded
    ASSERT_EQ( driver->Get_SRTM_File_List().size(), 2);

    
    // Create the DEM Manager
    DEM::DEM_Manager manager;
    
    // Get a copy of the DEM Manager
    manager.Add_DEM_IO_Driver( driver );

    
    // Set our utm coordinate
    CRD::CoordinateUTM_d  center_coordinate( 11, true, 384409, 4048901 );
    CRD::CoordinateUTM_d  min_coordinate = center_coordinate;
    min_coordinate.easting_meters()  -= (tile_size.Width()  * gsd)/2.0;
    min_coordinate.northing_meters() -= (tile_size.Height() * gsd)/2.0;

    // Create the elevation tile
    DEM::ElevationTileUTM_d::ptr_t  elevation_tile = manager.Create_Elevation_Tile( min_coordinate,
                                                                                    tile_size,
                                                                                    gsd, 
                                                                                    status );

    // make sure the operation succeeded
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );

    // check the elevation range
    IMG::PixelGray_df minPix, maxPix;
    status = IMG::MinMax( *elevation_tile->Get_Image_Ptr(), minPix, maxPix );

    ASSERT_NEAR( maxPix[0], 4412, 0.1 );
    ASSERT_NEAR( minPix[0], 3867.2505663045958, 0.1 );
}


