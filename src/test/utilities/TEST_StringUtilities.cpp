/**
 * @file    TEST_StringUtilities.cpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <utilities/StringUtilities.hpp>

using namespace GEO;

/**
 * Test the num2str method
*/
TEST( StringUtilities, num2str ){

    ASSERT_EQ( num2str(4), "4");
    ASSERT_EQ( num2str(4.4), "4.4");
    ASSERT_EQ( num2str(-1.1), "-1.1");

}


/**
 * Test the Str2num method
*/
TEST( StringUtilities, str2num )
{

    ASSERT_EQ( str2num<int>("1"), 1);
    ASSERT_EQ( str2num<int>("-1"), -1);
    ASSERT_NEAR( str2num<double>("-1.2345"), -1.2345, 0.0001 );

}

/**
 * Test the string trim method
*/
TEST( StringUtilities, string_trim ){

    ASSERT_EQ( string_trim(" hello\n"), "hello" );
    ASSERT_EQ( string_trim(" hello\n123", "\n 123"), "hello" );

}

/**
* TEst the tolower method
*/
TEST( StringUtilities, string_toLower ){

    ASSERT_EQ(string_toLower("hElLoWoRlD1234"), "helloworld1234");

}

/**
 * Test the to Upper method
*/
TEST( StringUtilities, string_toUpper ){

    ASSERT_EQ(string_toUpper("hElLoWoRlD1234"), "HELLOWORLD1234");

}

/**
 * Test the string split method
*/
TEST( StringUtilities, string_split ){

    std::string input_str = "1,2,3,4,5,6,";
    std::vector<std::string> strs = string_split(input_str,",");
    ASSERT_EQ( strs.size(), 7 );
    ASSERT_EQ( strs[0], "1");
    ASSERT_EQ( strs[1], "2");
    ASSERT_EQ( strs[2], "3");
    ASSERT_EQ( strs[3], "4");
    ASSERT_EQ( strs[4], "5");
    ASSERT_EQ( strs[5], "6");
    ASSERT_EQ( strs[6], "");

}



