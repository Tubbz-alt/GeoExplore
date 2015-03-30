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
    boost::filesystem::path srtm_file_path01 = "data/unit-test";
    boost::filesystem::path srtm_file_path02 = "data/unit-tests/imagery";

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
TEST( A_DEM_IO_Driver_SRTM, Constructor_Valid_SRTM_Path ){

    // Define our SRTM path
    boost::filesystem::path srtm_file_path = "data/unit-tests/dems/srtm";

    // Build the drivers
    DEM::A_DEM_IO_Driver_SRTM  driver( srtm_file_path );
    
    // Check that the initialization method passes.
    ASSERT_EQ( driver.Initialize().Get_Status_Type(), StatusType::SUCCESS );

    FAIL();
}


