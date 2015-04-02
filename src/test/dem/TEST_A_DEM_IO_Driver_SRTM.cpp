/**
 * @file    TEST_A_DEM_IO_Driver_SRTM.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore Library
#include "../../lib/dem/A_DEM_IO_Driver_SRTM.hpp"
#include "../../lib/image/Image_Utilities.hpp"

using namespace GEO;

/**
 * Test the Constructor
*/
TEST( A_DEM_IO_Driver_SRTM, Constructor_Invalid_SRTM_Path ){

    // Define our SRTM path
    FS::FilesystemPath srtm_file_path01 = "data/unit-test";
    FS::FilesystemPath srtm_file_path02 = "data/unit-tests/imagery";

    // Build the drivers
    DEM::A_DEM_IO_Driver_SRTM  driver01( srtm_file_path01 );
    DEM::A_DEM_IO_Driver_SRTM  driver02( srtm_file_path02 );

    // Check that the initialization methods failed.
    ASSERT_EQ( driver01.Initialize().Get_Status_Type(), StatusType::FAILURE );
    ASSERT_EQ( driver02.Initialize().Get_Status_Type(), StatusType::FAILURE );

}


/**
 * Test the Constructor
*/
TEST( A_DEM_IO_Driver_SRTM, Constructor_Valid_SRTM_Directory_Path ){

    // Define our SRTM path
    FS::FilesystemPath srtm_file_path = "data/unit-tests/dems/srtm";

    // Build the drivers
    DEM::A_DEM_IO_Driver_SRTM  driver( srtm_file_path );
    
    // Check that the initialization method passes.
    ASSERT_EQ( driver.Initialize().Get_Status_Type(), StatusType::SUCCESS );

    // Make sure that we have 2 files loaded
    ASSERT_EQ( driver.Get_SRTM_File_List().size(), 2);


}

/**
 * Test the Driver Constructor using a single filename.
 */
TEST( A_DEM_IO_Driver_SRTM, Constructor_Single_SRTM_Path ){

    // Define our SRTM path
    FS::FilesystemPath srtm_file_path = "data/unit-tests/dems/srtm/N36W119.hgt";

    // Build the drivers
    DEM::A_DEM_IO_Driver_SRTM  driver( srtm_file_path );
    
    // Check that the initialization method passes.
    ASSERT_EQ( driver.Initialize().Get_Status_Type(), StatusType::SUCCESS );

    // Make sure that we have 2 files loaded
    ASSERT_EQ( driver.Get_SRTM_File_List().size(), 1);

}

/**
 * TEst the SRTM Driver Constructor using a list of filenames 
*/
TEST( A_DEM_IO_Driver_SRTM, Constructor_List_SRTM_Paths ){
    
    // Define our SRTM path
    std::vector<FS::FilesystemPath> srtm_file_paths;
    srtm_file_paths.push_back("data/unit-tests/dems/srtm/N36W119.hgt");
    srtm_file_paths.push_back("data/unit-tests/dems/srtm/N39W120.hgt");

    // Build the drivers
    DEM::A_DEM_IO_Driver_SRTM  driver( srtm_file_paths );
    
    // Check that the initialization method passes.
    ASSERT_EQ( driver.Initialize().Get_Status_Type(), StatusType::SUCCESS );

    // Make sure that we have 2 files loaded
    ASSERT_EQ( driver.Get_SRTM_File_List().size(), 2);
    ASSERT_EQ( driver.Get_SRTM_File_List()[0], srtm_file_paths[0] );
    ASSERT_EQ( driver.Get_SRTM_File_List()[1], srtm_file_paths[1] );


}

/**
 * Test the Coverage Method.
*/
TEST( A_DEM_IO_Driver_SRTM, Coverage_Geographic ){

    // Define our SRTM path
    FS::FilesystemPath srtm_file_path = "data/unit-tests/dems/srtm";

    // Build the drivers
    DEM::A_DEM_IO_Driver_SRTM  driver( srtm_file_path );
    
    // Check that the initialization method passes.
    ASSERT_EQ( driver.Initialize().Get_Status_Type(), StatusType::SUCCESS );

    // Make sure that we have 2 files loaded
    ASSERT_EQ( driver.Get_SRTM_File_List().size(), 2);

    // Check coverage for a list of single points

    // Good Values
    CRD::CoordinateGeographic_d test_coordinate01( 36.1, -118.9);
    CRD::CoordinateGeographic_d test_coordinate02( 36.4, -118.7);
    ASSERT_TRUE( driver.Coverage( test_coordinate01 ) );
    ASSERT_TRUE( driver.Coverage( test_coordinate02 ) );

    // Bad Values
    CRD::CoordinateGeographic_d test_coordinate03( 36.4, -119.1);
    CRD::CoordinateGeographic_d test_coordinate04( 37.1, -118.7);
    ASSERT_FALSE( driver.Coverage( test_coordinate03 ));
    ASSERT_FALSE( driver.Coverage( test_coordinate04 ));
    
    // Check Coverage for a range of points

    // Good Values
    CRD::CoordinateGeographic_d test_coordinate05( 39.1, -119.9);
    CRD::CoordinateGeographic_d test_coordinate06( 39.4, -119.7);
    ASSERT_TRUE( driver.Coverage( test_coordinate01, test_coordinate02 ) );
    ASSERT_TRUE( driver.Coverage( test_coordinate05, test_coordinate06 ) );

    // Bad Values
    CRD::CoordinateGeographic_d test_coordinate07( 39.1, -120.1);
    CRD::CoordinateGeographic_d test_coordinate08( 39.4, -119.9);
    ASSERT_FALSE( driver.Coverage( test_coordinate03, test_coordinate04 ) );
    ASSERT_FALSE( driver.Coverage( test_coordinate07, test_coordinate08 ) );

}


/**
 * Test the Coverage Method.
*/
TEST( A_DEM_IO_Driver_SRTM, Coverage_UTM ){

    // Define our SRTM path
    FS::FilesystemPath srtm_file_path = "data/unit-tests/dems/srtm";

    // Build the drivers
    DEM::A_DEM_IO_Driver_SRTM  driver( srtm_file_path );
    
    // Check that the initialization method passes.
    ASSERT_EQ( driver.Initialize().Get_Status_Type(), StatusType::SUCCESS );

    // Make sure that we have 2 files loaded
    ASSERT_EQ( driver.Get_SRTM_File_List().size(), 2);

    // Check coverage for a list of single points

    // Good Values
    CRD::CoordinateUTM_d test_coordinate01( 11, true, 328964.3, 3996711.3);
    CRD::CoordinateUTM_d test_coordinate02( 11, true, 347553.8, 4029658.1);
    ASSERT_TRUE( driver.Coverage( test_coordinate01 ) );
    ASSERT_TRUE( driver.Coverage( test_coordinate02 ) );

    // Bad Values
    CRD::CoordinateUTM_d test_coordinate03( 11, true, 311679.8, 4030364.3);
    CRD::CoordinateUTM_d test_coordinate04( 11, true, 348932.9, 4107317.9);
    ASSERT_FALSE( driver.Coverage( test_coordinate03 ));
    ASSERT_FALSE( driver.Coverage( test_coordinate04 ));
    
    // Check Coverage for a range of points

    // Good Values
    CRD::CoordinateUTM_d test_coordinate05( 11, true, 249215.6, 4331878.4);
    CRD::CoordinateUTM_d test_coordinate06( 11, true, 267507.5, 4364645.0);
    ASSERT_FALSE( driver.Coverage( test_coordinate01, test_coordinate02 ) );
    ASSERT_FALSE( driver.Coverage( test_coordinate05, test_coordinate06 ) );

    // Bad Values
    /*
    CRD::CoordinateGeographic_d test_coordinate07( 39.1, -120.1);
    CRD::CoordinateGeographic_d test_coordinate08( 39.4, -119.9);
    ASSERT_FALSE( driver.Coverage( test_coordinate03, test_coordinate04 ) );
    ASSERT_FALSE( driver.Coverage( test_coordinate07, test_coordinate08 ) );
    */
}

/**
 * Query Geographic Coordinate
*/
TEST( A_DEM_IO_Driver_SRTM, Query_Elevation_Meters_geographic )
{
    // Status 
    Status status;

    // EPS
    const double eps = 10;
    
    // Define our SRTM path
    FS::FilesystemPath srtm_file_path = "data/unit-tests/dems/srtm";

    // Build the drivers
    DEM::A_DEM_IO_Driver_SRTM  driver( srtm_file_path );
    
    // Check that the initialization method passes.
    ASSERT_EQ( driver.Initialize().Get_Status_Type(), StatusType::SUCCESS );

    // Make sure that we have 2 files loaded
    ASSERT_EQ( driver.Get_SRTM_File_List().size(), 2);

    // Define the coordinates
    const CRD::CoordinateGeographic_d  test_coordinate_01( 36.578581, -118.291995, 4400, Datum::WGS84 );

    // Query the tile
    double elevation_meters = driver.Query_Elevation_Meters( test_coordinate_01, status );

    // Make sure the operation succeeded
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    ASSERT_NEAR( elevation_meters, test_coordinate_01.altitude_meters(), eps );


}

/**
 * Query UTM Coordinate
*/
TEST( A_DEM_IO_Driver_SRTM, Query_Elevation_Meters_utm ){
    
    // Status
    Status status;
    
    // EPS
    const double eps = 10;

    // Define our SRTM path
    FS::FilesystemPath srtm_file_path = "data/unit-tests/dems/srtm";

    // Build the drivers
    DEM::A_DEM_IO_Driver_SRTM  driver( srtm_file_path );
    
    // Check that the initialization method passes.
    ASSERT_EQ( driver.Initialize().Get_Status_Type(), StatusType::SUCCESS );

    // Make sure that we have 2 files loaded
    ASSERT_EQ( driver.Get_SRTM_File_List().size(), 2);


    // Define the coordinates 
    const CRD::CoordinateUTM_d   test_coordinate_01( 11, true, 384409, 4048901, 4400, Datum::WGS84 );

    // Query the tile
    double elevation_meters = driver.Query_Elevation_Meters( test_coordinate_01, status );

    // Make sure the operation succeeded
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    ASSERT_NEAR( elevation_meters, test_coordinate_01.altitude_meters(), eps );


}


/**********************************************************/
/*          Test the SRTM Dem Driver Create Tile          */
/**********************************************************/
TEST(  A_DEM_IO_Driver_SRTM, Create_Elevation_Tile_utm )
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
    DEM::A_DEM_IO_Driver_SRTM  driver( srtm_file_path );
    
    // Check that the initialization method passes.
    ASSERT_EQ( driver.Initialize().Get_Status_Type(), StatusType::SUCCESS );

    // Make sure that we have 2 files loaded
    ASSERT_EQ( driver.Get_SRTM_File_List().size(), 2);

    // Set our utm coordinate
    CRD::CoordinateUTM_d  center_coordinate( 11, true, 384409, 4048901 );
    CRD::CoordinateUTM_d  min_coordinate = center_coordinate;
    min_coordinate.easting_meters()  -= (tile_size.Width()  * gsd)/2.0;
    min_coordinate.northing_meters() -= (tile_size.Height() * gsd)/2.0;

    // Create the elevation tile
    DEM::ElevationTileUTM_d::ptr_t  elevation_tile = driver.Create_Elevation_Tile( min_coordinate,
                                                                                   tile_size,
                                                                                   gsd, 
                                                                                   status );

    // make sure the operation succeeded
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );

    // check the elevation range
    IMG::PixelGray_df minPix, maxPix;
    status = IMG::MinMax( *elevation_tile->Get_Image_Ptr(), minPix, maxPix );

    ASSERT_NEAR( maxPix[0], 4412, 0.00001 );
    ASSERT_NEAR( minPix[0], 3872, 0.00001 );
}


