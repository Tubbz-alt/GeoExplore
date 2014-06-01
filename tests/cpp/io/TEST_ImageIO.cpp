/**
 * @file    TEST_ImageIO.cpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#include <gtest/gtest.h>

/// GeoExplore
#include <GeoExplore.hpp>

/**
 * Test the Compute driver function
*/
TEST( ImageIO, ComputeDriver ){

    /// Test the driver for OPENCV-type images
    ASSERT_EQ( GEO::IO::compute_driver("/var/tmp/image.jpg"),  GEO::ImageDriverType::GDAL );
    ASSERT_EQ( GEO::IO::compute_driver("/var/tmp/image.dt0"),  GEO::ImageDriverType::GDAL );
    ASSERT_EQ( GEO::IO::compute_driver("/var/tmp/image.dt1"),  GEO::ImageDriverType::GDAL );
    ASSERT_EQ( GEO::IO::compute_driver("/var/tmp/image.dt2"),  GEO::ImageDriverType::GDAL );
    ASSERT_EQ( GEO::IO::compute_driver("/var/tmp/image.ntf"),  GEO::ImageDriverType::GDAL );
    ASSERT_EQ( GEO::IO::compute_driver("/var/tmp/image.nitf"), GEO::ImageDriverType::GDAL );
    ASSERT_EQ( GEO::IO::compute_driver("/var/tmp/image.NTF"),  GEO::ImageDriverType::GDAL );
    ASSERT_EQ( GEO::IO::compute_driver("/var/tmp/image.NITF"), GEO::ImageDriverType::GDAL );
    
}

/**
 * Test the read_image function
*/
TEST( ImageIO, ReadImage ){

    GEO::Image<GEO::PixelRGB_u8> image;
    GEO::IO::read_image("../../tests/data/images/Lenna.jpg", image);

    ASSERT_EQ( image.rows(), 512 );
    ASSERT_EQ( image.cols(), 512 );

}

/**
 * Test the read_image function using Disk Image
*/
TEST( ImageIO, ReadDiskImage ){

    // force GDAL using NITF
    GEO::DiskImage<GEO::PixelRGB_u8> image;
    GEO::IO::read_image("../../tests/data/images/i_3001a.ntf", image);
    
    ASSERT_EQ( image.rows(), 1024 );
    ASSERT_EQ( image.cols(), 1024 );

    // force GDAL using SRTM
    GEO::DiskImage<GEO::PixelGray_df> image02;
    GEO::IO::read_image("../../tests/data/dem/n39_w120_3arc_v1.bil", image02 );

    ASSERT_EQ( image02.rows(), 1201 );
    ASSERT_EQ( image02.cols(), 1201 );

}


