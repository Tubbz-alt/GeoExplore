/**
 * @file    geo-utility.cpp
 * @author  Marvin Smith
 * @date    8/3/2014
*/

// C++ Standard Libraries
#include <iostream>

// Geo-Explore Libraries
#include <GeoExplore.hpp>

// Geo Utility Libraries
#include "Globals.hpp"
#include "Options.hpp"
#include "Utilities.hpp"

using namespace std;

/**
 * @brief Main Function
*/
int main( int argc, char* argv[] ){

    // Process Command-Line Arguments
    Options options = Parse_Command_Line(argc,argv);

    // Initialize the DEM Manager
    Initialize_DEM_Manager( options );

    //  Initialize the imagery
    Data_Container data;
    Initialize_Data( data, options );    

    return 0;
}


