/**
 * @file    GDU_Utilities.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include "GDU_Utilities.hpp"

/** 
 * Parse Command-Line Options
*/
GDU_Options Parse_Command_Line( int argc, char* argv[] ){
    
    // Create output
    GDU_Options options;
    
    // Create a command-line parser
    GEO::CONFIG::A_Command_Line_Parser parser(argc, argv);

    // Run through the options


    // Finalize the options
    options.Finalize();

    // Return the options container
    return options;
}

