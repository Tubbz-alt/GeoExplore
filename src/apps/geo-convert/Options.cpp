/**
 * @file    Options.cpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#include "Options.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>


/**
 * Print usage instructions for geo-convert
 */
void usage( const std::string& appName ){

    std::cerr << "usage: " << appName << "<ctype> -i <value> -o <value>" << std::endl;
    std::cerr << std::endl;
    std::cerr << "    required flags: " << std::endl;
    std::cerr << std::endl;
    std::cerr << "       -ctype : Set the conversion type." << std::endl;
    std::cerr << "             Supported Conversion Types" << std::endl;
    std::cerr << "             -c : Coordinate conversion" << std::endl;
    std::cerr << std::endl;
    std::cerr << "        -i <value>   : Set the input to be converted." << std::endl;
    std::cerr << "          Input Formats" << std::endl;
    std::cerr << "            Coordinates:" << std::endl;
    std::cerr << "              -utm:<easting>:<northing>:<altitude=0>:<projection=WGS84>" << std::endl;
    std::cerr << "              -geod-dd:<latitude>:<longitude>:<altitude=0>:<projection=WGS84>" << std::endl;
    std::cerr << "              -geod-dm:<lat,min>:<lon,min>:<altitude=0>:<projection=WGS84>" << std::endl;
    std::cerr << "              -geod-dms:<lat,min,sec>:<lon,min,sec>:<altitude=0>:<projection=WGS84>" << std::endl;
    std::cerr << std::endl;
    std::cerr << "        -o <value>   : Set the desired output given the conversion type." << std::endl;
    std::cerr << "            Coordinates:  Specify the output coordinate type." << std::endl;
    std::cerr << "                  Supported types:   -utm, -geod-dd, -geod-dm, -geod-dms" << std::endl;
    std::cerr << std::endl;
    std::cerr << "    optional flags: " << std::endl;
    std::cerr << "        -h, --help     : Print usage instructions." << std::endl;
    std::cerr << std::endl;
    std::cerr << "    Notes" << std::endl;
    std::cerr << "      1.  All geodetic coordinates should be comma-deliminated format if not in decimal degrees." << std::endl;
    std::cerr << std::endl;

}


/**
 * Parse Command-Line Options
 */
Options parse_command_line( int argc, char* argv[] ){

    // create our output container
    Options options;

    // set the application name
    options.appName = argv[0];

    // create a list of arguments to parse
    std::deque<std::string> args;
    for( int i=1; i<argc; i++ ){ 
        args.push_back(argv[i]);
    }
    
    // begin parsing command-line options
    while( args.size() > 0 ){

        // pop the next argument
        std::string arg = args.front();
        args.pop_front();

        // test if help was requested
        if( arg == "-h" || arg == "--help" ){
            usage(options.appName);
            exit(1);
        }

        // test if the coordinate conversion type was given
        else if( arg == "-c" ){
            options.ctype = ConversionType::COORDINATE;
        }

        // test if the input value was given
        else if( arg == "-i" ){

            // make sure there are still elements left
            if( args.size() <= 0 ){
                throw std::runtime_error("Input was specified with no arguments.");
            }

            // get the next component
            std::string targ = args.front();
            args.pop_front();
            
            options.inputs.push_back(targ);
        }
        
        // test for the output format
        else if( arg == "-o" ){

            // make sure there are still arguments left to parse
            if( args.size() <= 0 ){
                throw std::runtime_error("Output was specified with no argument.");
            }

            // get the next component
            std::string targ = args.front();
            args.pop_front();

            // add to output list
            options.outputs.push_back( targ );
        
        }
        
        // otherwise, throw an error for unknown argument
        else{
            throw std::runtime_error(std::string("Unknown argument (")+arg+std::string(")").c_str());
        }


    }


    // return our command-line options
    return options;
}
