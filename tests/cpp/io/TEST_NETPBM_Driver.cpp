/**
 * @file    TEST_NETPBM_Driver.hpp
 * @author  Marvin Smith
 * @date    5/14/2014
*/
#include <gtest/gtest.h>

/// GeoExplore Libraries
#include <GeoExplore.hpp>


/**
 * Test the Write PPM Function
*/
TEST( NETPBM_Driver, WriteImagePPM ){

    /// create an image
    GEO::Image<GEO::PixelRGB_d>  image01(100,100);

    // write the image
    GEO::IO::NETPBM::write_image( image01, "file.ppm");

}

/**
 * Test the Write PGM Function
*/
TEST( NETPBM_Driver, WriteImagePGM ){

    /// create an image
    GEO::Image<GEO::PixelGray_d>  image01(100,100);

    // write the image
    GEO::IO::NETPBM::write_image( image01, "file.pgm");

}

/**
 * Test the Write Image with bad file type
*/
TEST( NETPBM_Driver, WriteImageError ){

    /// Create an image
    GEO::Image<GEO::PixelRGB_d> image01;

    // write the image
    ASSERT_THROW( GEO::IO::NETPBM::write_image( image01, "file.jpg"), GEO::GeneralException );

}

