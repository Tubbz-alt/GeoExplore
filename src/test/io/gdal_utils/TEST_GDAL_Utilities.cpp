/**
 * @file    TEST_GDAL_Utilities.cpp
 * @author  Marvin Smith
 * @date    4/3/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <image/ChannelType.hpp>
#include <io/gdal_utils/GDAL_Utilities.hpp>

using namespace GEO;

/**
 * Test the ctype2gdaltype
*/
TEST( GDAL_Utilities, ctype2gdaltype )
{
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeUInt8>(), GDT_Byte );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeUInt12>(), GDT_UInt16 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeUInt14>(), GDT_UInt16 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeUInt16>(), GDT_UInt16 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeUInt32>(), GDT_UInt32 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeDouble>(), GDT_Float64 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeDoubleFree>(), GDT_Float64 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<float>(), GDT_Unknown );

}

/**
 * Test the Short driver from filename
*/
TEST( GDAL_Utilities, Get_Short_Driver_From_Filename )
{
    // Test Unknowns
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.txt")), "");

    // Test JPEG
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.jpg")), "JPEG");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.jpeg")), "JPEG");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.JPG")), "JPEG");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.JPEG")), "JPEG");

    // Test GeoTiff
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.tif")), "GTiff");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.tiff")), "GTiff");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.TIF")), "GTiff");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.TIFF")), "GTiff");

    // Test PNG
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.png")), "PNG" );
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.PNG")), "PNG" );

    // Test NITF
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.ntf")), "NITF" );
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.nitf")), "NITF" );
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.NTF")), "NITF" );
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.NITF")), "NITF" );

}

