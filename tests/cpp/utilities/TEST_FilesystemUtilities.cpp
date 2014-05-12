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

    FAIL();

}


