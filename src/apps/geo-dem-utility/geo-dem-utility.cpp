/**
 * @file    geo-dem-utility.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/

// GeoExplore Libraries
#include <GeoExplore.hpp>

// DEM Utility Libraries
#include "GDU_Options.hpp"
#include "GDU_Render.hpp"
#include "GDU_Utilities.hpp"


using namespace GEO;

/**
 * @brief Main Driver
*/
int main( int argc, char* argv[] ){
    
    // Parse the Command-Line Options
    GDU_Options options;
    options.Initialize( argc, argv );

    // If in render mode, render the imagery
    if( options.Get_Program_Mode() == GDU_Mode::RENDER ){
        Render_Terrain( options );
    }


    return 0;
}


