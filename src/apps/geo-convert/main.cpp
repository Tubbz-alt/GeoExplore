/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */

/// GeoExplore Library
#include <GeoExplore.hpp>

/// Geo-Convert Libraries
#include "Options.hpp"
#include "CoordinateConversion.hpp"

/// C++ Libraries
#include <exception>
#include <iostream>
#include <string>

using namespace std;


/**
 * Main Function
 */
int main( int argc, char* argv[] ){

    try{

        /// Parse the command-line options
        Options options = parse_command_line( argc, argv );
        
        /// Check our conversion type and pass it to the appropriate function
        if( options.ctype == ConversionType::COORDINATE ){
            convert_coordinates( options );
        }


    } catch ( exception& e ){
        cerr << "error: " << e.what() << endl;
        usage(argv[0]);
        return 1;
    }


    return 0;
}

