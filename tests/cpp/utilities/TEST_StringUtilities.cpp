/**
 * @file    TEST_StringUtilities.cpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#include <gtest/gtest.h>

#include <GeoExplore.hpp>

/**
 * Test the String Split Function
 */
TEST( StringUtilities, StringSplit ){

    /// run the split command to test output
    std::vector<std::string>  test01 = GEO::string_split("hello.world.txt", ".");
    ASSERT_EQ( test01.size(), 3);
    ASSERT_EQ( test01[0], "hello");
    ASSERT_EQ( test01[1], "world");
    ASSERT_EQ( test01[2], "txt");

}

