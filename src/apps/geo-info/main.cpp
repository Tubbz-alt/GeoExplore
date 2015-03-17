/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    5/16/2014
*/

/// Geo-Explore Libraries
#include <GeoExplore.hpp>

/// GeoInfo Libraries
#include "Options.hpp"


using namespace std;

int main( int argc, char* argv[] ){

    /// Parse Command-Line Options
    Options options = parse_command_line( argc, argv );

    return 0;
}


