/**
 * @file    TEST_SRTM_Utilities.cpp
 * @author  Marvin Smith
 * @date    4/1/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/dem/SRTM_Utilities.hpp>

using namespace GEO;

/**
 * Test the Coordinate to Pixel Value.
 */
TEST( SRTM_Utilities, Coordinate_To_SRTM_Pixel )
{

    // Epsilon
    const double eps = 0.0001;

    // Status
    Status status;

    // Tile Width
    const double width  = -118.9998611 + 120.0001389; 
    const double height = 40.0001389 - 38.9998611;

    // Tile Size
    const int tile_rows = 3601;
    const int tile_cols = 3601;

    // Geographic Coordinate
    CRD::CoordinateGeographic_d coordinate01( 40.0001388889, -120.0001388889);
    CRD::CoordinateGeographic_d coordinate02( 39.0001388889, -119.0001388889);
    CRD::CoordinateGeographic_d coordinate03( 39.5001388889, -119.5001388889);

    // Create Rectangle
    MATH::A_Rectangle2d  extent( MATH::A_Point2d( -120.0001389, 38.9998611), 
                                 width, 
                                 height );


    // Compute Point
    MATH::A_Point2d pixel01 = DEM::SRTM::Coordinate_To_SRTM_Pixel( coordinate01,
                                                                   extent,
                                                                   tile_rows,
                                                                   tile_cols,
                                                                   status );
    
    // Make sure operation succeeded
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    
    // Compute Pixel
    ASSERT_NEAR( pixel01.x(), 0, eps );
    ASSERT_NEAR( pixel01.y(), 0, eps );

    // Point 2
    MATH::A_Point2d pixel02 = DEM::SRTM::Coordinate_To_SRTM_Pixel( coordinate02,
                                                                   extent,
                                                                   tile_rows,
                                                                   tile_cols,
                                                                   status );
    
    // Make sure operation succeeded
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    
    // Compute Pixel
    ASSERT_NEAR( pixel02.x(), 3600, eps );
    ASSERT_NEAR( pixel02.y(), 3600, eps );
    
    // Point 3
    MATH::A_Point2d pixel03 = DEM::SRTM::Coordinate_To_SRTM_Pixel( coordinate03,
                                                                   extent,
                                                                   tile_rows,
                                                                   tile_cols,
                                                                   status );
    
    // Make sure operation succeeded
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    
    // Compute Pixel
    ASSERT_NEAR( pixel03.x(), 1800, eps );
    ASSERT_NEAR( pixel03.y(), 1800, eps );
    

}

