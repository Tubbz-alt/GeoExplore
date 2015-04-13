/**
 * @file    TEST_System_Utilities.cpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/utilities/StringUtilities.hpp>
#include <GeoExplore/utilities/System_Utilities.hpp>

using namespace GEO;

/**
 * Test the system call function
*/
TEST( System_Utilities, System_Call )
{

    // Test the LS Command
    std::string output = System_Call("ls CMake*","r");

    ASSERT_EQ(string_trim(output),"CMakeLists.txt");

}

