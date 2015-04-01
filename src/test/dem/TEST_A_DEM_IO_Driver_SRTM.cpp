/**
 * @file    TEST_A_DEM_IO_Driver_SRTM.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore Library
#include "../../lib/dem/A_DEM_IO_Driver_SRTM.hpp"

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

}


