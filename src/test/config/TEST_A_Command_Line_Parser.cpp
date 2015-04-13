/** 
 * @file    TEST_A_Command_Line_Parser.cpp
 * @author  Marvin Smith
 * @date    3/23/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/config/A_Command_Line_Parser.hpp>

using namespace GEO;


/**
 * Test the constructor with no arguments
*/
TEST( A_Command_Line_Parser, Constructor_no_arguments ){

    char** argv = new char*[1];
    argv[0] = (char*)"main.out";
    int argc = 1;

    // Create parser
    CONFIG::A_Command_Line_Parser parser(argc, argv);
    
    // Check application name
    ASSERT_EQ( parser.Get_Application_Name(), "main.out");

    // Check if flags exist
    ASSERT_FALSE( parser.Check_If_Flag_Exists("flag") );
    
}

/**
 * Test the Argv/Argc constructor
*/
TEST( A_Command_Line_Parser, Constructor_arguments ){

    // Create argument list
    int argc = 5;
    char** argv = new char*[5];
    argv[0] = (char*)"./main.out";
    argv[1] = (char*)"-help";
    argv[2] = (char*)"--render";
    argv[3] = (char*)"-c";
    argv[4] = (char*)"file.txt";

    std::vector<std::string> help_list;
    help_list.push_back("-h");
    help_list.push_back("-help");
    
    std::vector<std::string> usage_list;
    usage_list.push_back("-u");
    usage_list.push_back("-usage");

    std::vector<std::string> config_list1;
    config_list1.push_back("-c");
    config_list1.push_back("--config");
    
    std::vector<std::string> config_list2;
    config_list2.push_back("-r");
    config_list2.push_back("--render-me");
    
    // Create the parser
    CONFIG::A_Command_Line_Parser parser(argc, argv);

    // Check the application name
    ASSERT_EQ( parser.Get_Application_Name(), "./main.out");

    // Check for flags
    ASSERT_TRUE( parser.Check_If_Flag_Exists("-help") );
    ASSERT_TRUE( parser.Check_If_Flag_Exists("-c") );
    ASSERT_FALSE( parser.Check_If_Flag_Exists("-C") );

    ASSERT_TRUE( parser.Check_If_Flag_Exists(help_list));
    ASSERT_FALSE( parser.Check_If_Flag_Exists(usage_list));
    
    // Check for flags and values
    bool flag_found, value_found;

    ASSERT_EQ( parser.Query_Flag_Value_As_String("-c", flag_found, value_found ), "file.txt" );
    ASSERT_TRUE( flag_found );
    ASSERT_TRUE( value_found );

    
    ASSERT_EQ( parser.Query_Flag_Value_As_String(config_list1, flag_found, value_found ), "file.txt" );
    ASSERT_TRUE( flag_found );
    ASSERT_TRUE( value_found );
    
    ASSERT_EQ( parser.Query_Flag_Value_As_String(config_list2, flag_found, value_found ), "" );
    ASSERT_FALSE( flag_found );
    ASSERT_FALSE( value_found );    


    ASSERT_EQ( parser.Query_Flag_Value_As_String("file.txt", flag_found, value_found), "");
    ASSERT_TRUE( flag_found );
    ASSERT_FALSE( value_found );

}

