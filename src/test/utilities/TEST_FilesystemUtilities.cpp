/**
 * @file    TEST_FilesystemUtilities.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#include <gtest/gtest.h>

// Filesystem Utilities
#include <GeoExplore/utilities/FilesystemUtilities.hpp>

using namespace GEO;

/**
 * Check the filesystem type enum values
*/
TEST( FilesystemUtilities, FileType_values ){

    // Assert values
    ASSERT_EQ( static_cast<int16_t>(FS::FileType::UNKNOWN), 0 );
    ASSERT_EQ( static_cast<int16_t>(FS::FileType::JPEG), 1 );
    ASSERT_EQ( static_cast<int16_t>(FS::FileType::JPEG2000), 2 );
    ASSERT_EQ( static_cast<int16_t>(FS::FileType::PNG), 3 );
    ASSERT_EQ( static_cast<int16_t>(FS::FileType::NITF), 4 );
    ASSERT_EQ( static_cast<int16_t>(FS::FileType::DTED), 5 );
    ASSERT_EQ( static_cast<int16_t>(FS::FileType::SRTM), 6 );
    ASSERT_EQ( static_cast<int16_t>(FS::FileType::TIFF), 7 );

}

/**
 * Test the Get File Type Method
*/
TEST( FilesystemUtilities, Get_File_Type ){

    // Test Unknown
    ASSERT_EQ( FS::Get_File_Type(""), FS::FileType::UNKNOWN );
    ASSERT_EQ( FS::Get_File_Type("image.txt"), FS::FileType::UNKNOWN );


    // Test JPEG
    ASSERT_EQ( FS::Get_File_Type("image.jpg"), FS::FileType::JPEG );
    ASSERT_EQ( FS::Get_File_Type("./image.JPG"), FS::FileType::JPEG );
    ASSERT_EQ( FS::Get_File_Type("./image.JPEG"), FS::FileType::JPEG );
    ASSERT_EQ( FS::Get_File_Type("/wow/image.jpeg"), FS::FileType::JPEG );
    ASSERT_EQ( FS::Get_File_Type("/wow/image.jpg"), FS::FileType::JPEG );

    // Test JPEG2000
    ASSERT_EQ( FS::Get_File_Type("image.jp2"), FS::FileType::JPEG2000 );


    // Test PNG
    ASSERT_EQ( FS::Get_File_Type("image.png"), FS::FileType::PNG );
    ASSERT_EQ( FS::Get_File_Type("image.PNG"), FS::FileType::PNG );
    ASSERT_EQ( FS::Get_File_Type("wow/image.png"), FS::FileType::PNG );
    ASSERT_EQ( FS::Get_File_Type("wow/image.PNG"), FS::FileType::PNG );
    ASSERT_EQ( FS::Get_File_Type("/root/image.png"), FS::FileType::PNG );
    ASSERT_EQ( FS::Get_File_Type("/root/image.PNG"), FS::FileType::PNG );


    // Test NITF
    ASSERT_EQ( FS::Get_File_Type("image.ntf"), FS::FileType::NITF );
    ASSERT_EQ( FS::Get_File_Type("image.nitf"), FS::FileType::NITF );
    ASSERT_EQ( FS::Get_File_Type("image.NTF"), FS::FileType::NITF );
    ASSERT_EQ( FS::Get_File_Type("image.NITF"), FS::FileType::NITF );
    ASSERT_EQ( FS::Get_File_Type("./image.ntf"), FS::FileType::NITF );
    ASSERT_EQ( FS::Get_File_Type("./image.nitf"), FS::FileType::NITF );
    ASSERT_EQ( FS::Get_File_Type("./image.NTF"), FS::FileType::NITF );
    ASSERT_EQ( FS::Get_File_Type("./image.NITF"), FS::FileType::NITF );


    // Test DTED
    ASSERT_EQ( FS::Get_File_Type("image.dt0"), FS::FileType::DTED );
    ASSERT_EQ( FS::Get_File_Type("image.dt1"), FS::FileType::DTED );
    ASSERT_EQ( FS::Get_File_Type("image.dt2"), FS::FileType::DTED );


    // Test SRTM
    ASSERT_EQ( FS::Get_File_Type("image.hgt"), FS::FileType::SRTM );


    // Test TIFF
    ASSERT_EQ( FS::Get_File_Type("/./image.tif"), FS::FileType::TIFF );
    ASSERT_EQ( FS::Get_File_Type("/./image.tiff"), FS::FileType::TIFF );
    ASSERT_EQ( FS::Get_File_Type("/./image.TIF"), FS::FileType::TIFF );
    ASSERT_EQ( FS::Get_File_Type("/./image.TIFF"), FS::FileType::TIFF );
    ASSERT_EQ( FS::Get_File_Type("./image.tif"), FS::FileType::TIFF );
    ASSERT_EQ( FS::Get_File_Type("./image.tiff"), FS::FileType::TIFF );
    ASSERT_EQ( FS::Get_File_Type("./image.TIF"), FS::FileType::TIFF );
    ASSERT_EQ( FS::Get_File_Type("./image.TIFF"), FS::FileType::TIFF );
    ASSERT_EQ( FS::Get_File_Type("image.tif"), FS::FileType::TIFF );
    ASSERT_EQ( FS::Get_File_Type("image.tiff"), FS::FileType::TIFF );
    ASSERT_EQ( FS::Get_File_Type("image.TIF"), FS::FileType::TIFF );
    ASSERT_EQ( FS::Get_File_Type("image.TIFF"), FS::FileType::TIFF );

}

