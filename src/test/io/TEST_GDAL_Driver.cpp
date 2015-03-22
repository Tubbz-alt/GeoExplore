/**
 * @file    TEST_GDAL_Driver.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../lib/image/DiskResource.hpp"
#include "../lib/image/MemoryResource.hpp"
#include "../lib/image/Pixel_Types.hpp"
#include "../lib/io/GDAL_Driver.hpp"

using namespace GEO;

/**
 * GDAL Driver Constructor
*/
TEST( GDAL_Driver, Default_Constructors ){

    // Create RGB_u8 GDAL_Driver
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>> gdal_driver_rgb_u8;
    ASSERT_FALSE( gdal_driver_rgb_u8.Is_Open() );

}

/**
 * GDAL Is_Read_Supported Method
*/
TEST( GDAL_Driver, Is_Read_Supported ){

    // Expected strings
    const std::string tiff_test_01 = "/root/image.tiff";
    const std::string tiff_test_02 = "/root/image.tif";
    const std::string tiff_test_03 = "/root/image.TIF";
    const std::string tiff_test_04 = "/root/image.TIFF";
    const std::string tiff_test_05 = "image.tif";
    const std::string tiff_test_06 = "image.tiff";
    const std::string tiff_test_07 = "image.TIF";
    const std::string tiff_test_08 = "image.TIFF";

    // Test PNG and other unknowns
    ASSERT_FALSE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u12>>::Is_Read_Supported("Image.png"));
    ASSERT_FALSE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u12>>::Is_Read_Supported("Image.txt"));
    ASSERT_FALSE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u12>>::Is_Read_Supported("Image.j2k"));

    // Test Tiff
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_01 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_02 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_03 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_04 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_05 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_06 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_07 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_08 ) );
    
    // Test J2k
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGBA_u12>>::Is_Read_Supported("image.jp2"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGBA_u12>>::Is_Read_Supported("image.JP2"));
    
    // Test  Jpeg
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelGray_df>>::Is_Read_Supported("image.jpg"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelGray_df>>::Is_Read_Supported("image.jpeg"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelGray_df>>::Is_Read_Supported("image.JPEG"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelGray_df>>::Is_Read_Supported("image.JPG"));

    // Test DTED
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelRGB_u16>>::Is_Read_Supported("/root/image.dt1"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelRGB_u16>>::Is_Read_Supported("/root/image.dt0"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelRGB_u16>>::Is_Read_Supported("/root/image.DT2"));
    
    // Read srtm
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelRGBA_df>>::Is_Read_Supported("file.hgt"));

    // Read nitf
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u8>>::Is_Read_Supported("image.ntf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u8>>::Is_Read_Supported("image.nitf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u8>>::Is_Read_Supported("image.NTF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u8>>::Is_Read_Supported("image.NITF"));

}

/**
 * GDAL Is_Write_Supported Method
*/
TEST( GDAL_Driver, Is_Write_Supported ){

    // Make sure most formats fail  
    ASSERT_FALSE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported(""));
    ASSERT_FALSE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.txt"));
    
    // Test NITF
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.ntf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.nitf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.NTF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.NITF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("../image.ntf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("../image.nitf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("../image.NTF"));

    // Test Tiff
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.tif"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("/image.tif"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.tiff"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("/image.tiff"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.TIF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("/../image.TIF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.TIFF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("/../image.TIFF"));
}


