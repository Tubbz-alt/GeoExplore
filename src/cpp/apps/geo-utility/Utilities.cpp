/**
 * @file     Utilities.cpp
 * @author   Marvin Smith
 * @date     8/3/2014
*/
#include "Utilities.hpp"


/**
 * Parse Command-Line Options
*/
Options Parse_Command_Line_Options( int argc, char* argv[] ){

    // Create our options
    Options options;

    // set the application name
    options.Set_Application_Name(argv[0]);

    // create parser

    // return the options
    return options;

}
