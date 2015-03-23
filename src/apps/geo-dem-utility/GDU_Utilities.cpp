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
    


    // Finalize the options
    options.Finalize();

    // Return the options container
    return options;
}

