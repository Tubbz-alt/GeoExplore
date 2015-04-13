/**
 * @file    TEST_OpenCV_Driver.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#include <gtest/gtest.h>

// OpenCV Driver
#include <GeoExplore/image/DiskResource.hpp>
#include <GeoExplore/image/MemoryResource.hpp>
#include <GeoExplore/image/Pixel_Types.hpp>
#include <GeoExplore/io/OpenCV_Driver.hpp>

using namespace GEO;

/**
 * Test the Is_Read_Supported Library
*/
TEST( ImageDriverOpenCV, Is_Read_Supported ){

    // Test JPEG
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Read_Supported("image.jpg"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Read_Supported("image.jpeg"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Read_Supported("image.JPG"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Read_Supported("image.JPEG"));
    
    // Test TIFF
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Read_Supported("image.tif"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Read_Supported("image.tiff"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Read_Supported("image.TIF"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Read_Supported("image.TIFF"));

    // Test PNG
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::DiskResource<IMG::PixelRGBA_u8>>::Is_Read_Supported("output.png"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::DiskResource<IMG::PixelRGBA_u8>>::Is_Read_Supported("output.PNG"));

    // Test Unknowns
    ASSERT_FALSE( IO::OPENCV::ImageDriverOpenCV<IMG::DiskResource<IMG::PixelGray_u12>>::Is_Read_Supported("output.pgm"));
    ASSERT_FALSE( IO::OPENCV::ImageDriverOpenCV<IMG::DiskResource<IMG::PixelGray_u12>>::Is_Read_Supported("output.ppm"));
    ASSERT_FALSE( IO::OPENCV::ImageDriverOpenCV<IMG::DiskResource<IMG::PixelGray_u12>>::Is_Read_Supported(""));


}

/**
 * Test the Is_Write_Supported Library
*/
TEST( ImageDriverOpenCV, Is_Write_Supported ){

    // Test JPEG
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Write_Supported("image.jpg"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Write_Supported("image.jpeg"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Write_Supported("image.JPG"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Write_Supported("image.JPEG"));
    
    // Test TIFF
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Write_Supported("image.tif"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Write_Supported("image.tiff"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Write_Supported("image.TIF"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::MemoryResource<IMG::PixelGray_df>>::Is_Write_Supported("image.TIFF"));

    // Test PNG
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::DiskResource<IMG::PixelRGBA_u8>>::Is_Write_Supported("output.png"));
    ASSERT_TRUE( IO::OPENCV::ImageDriverOpenCV<IMG::DiskResource<IMG::PixelRGBA_u8>>::Is_Write_Supported("output.PNG"));

    // Test Unknowns
    ASSERT_FALSE( IO::OPENCV::ImageDriverOpenCV<IMG::DiskResource<IMG::PixelGray_u12>>::Is_Write_Supported("output.pgm"));
    ASSERT_FALSE( IO::OPENCV::ImageDriverOpenCV<IMG::DiskResource<IMG::PixelGray_u12>>::Is_Write_Supported("output.ppm"));
    ASSERT_FALSE( IO::OPENCV::ImageDriverOpenCV<IMG::DiskResource<IMG::PixelGray_u12>>::Is_Write_Supported(""));
}

