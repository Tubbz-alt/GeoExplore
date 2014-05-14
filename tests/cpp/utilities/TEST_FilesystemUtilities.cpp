/**
 * @file    TEST_FilesystemUtilities.cpp
 * @author  Marvin Smith
 * @date    5/11/2014
*/
#include <gtest/gtest.h>

/// GeoExplore Library
#include <GeoExplore.hpp>

/// C++ Standard Libraries
#include <iostream>

using namespace std;

/**
 * Test the magic string function
*/
TEST( FilesystemUtilities, getMagicNumber ){

    /// Test JPEG image 01
    std::string signature = GEO::FS::getMagicNumber("../../tests/data/images/Lenna.jpg");
    
    std::cout << signature << std::endl;

    FAIL();

}

/**
 * Test the get file type function
*/
TEST( FilesystemUtilities, getFileType ){
    
    /// create a set of tests
    ASSERT_EQ( GEO::FS::getFileType("/var/file.jpg"), GEO::FS::FileType::JPEG );
    ASSERT_EQ( GEO::FS::getFileType("file.png"), GEO::FS::FileType::PNG);
    ASSERT_EQ( GEO::FS::getFileType("/root/image.nitf"), GEO::FS::FileType::NITF);
    ASSERT_EQ( GEO::FS::getFileType("image.jp2"), GEO::FS::FileType::JPEG2000);

}


