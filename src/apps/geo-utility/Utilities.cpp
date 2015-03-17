/**
 * @file     Utilities.cpp
 * @author   Marvin Smith
 * @date     8/3/2014
*/
#include "Utilities.hpp"

// C++ Libraries
#include <cstdlib>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>


/**
 * Parse Command-Line Options
*/
Options Parse_Command_Line( int argc, char* argv[] )
{

    // Create our options
    Options options;

    // set the application name
    options.Set_Application_Name(argv[0]);

    // create parser
    std::deque<std::string> args;
    std::string arg;
    for( int i=1; i<argc; i++ ){
        args.push_back(argv[i]);
    }

    // Iterate over args
    while( args.size() > 0 ){

        // get the next argument
        arg = args.front();
        args.pop_front();

        // Check if help
        if( arg == "-h" || arg == "--help" ){
            Usage(options);
        }

        // Check if user provided a configuration file
        else if( arg == "-c" | arg == "--config" ){
            options.Set_Configuration_File( args.front() );
            args.pop_front();
        }

        // Otherwise, there was an error
        else{
            std::cerr << "error: unknown argument (" << arg << std::endl;
            std::exit(-1);
        }
        
    }

    // Finalize the configuration
    options.Finalize();

    // return the options
    return options;

}


/**
 * Print Usage Instructions
*/
void Usage( const Options& options ){

    // Print
    std::cerr << std::endl;
    std::cerr << "usage: " << options.Get_Application_Name().c_str() << " <options>" << std::endl;
    std::cerr << std::endl;

    // Print Optional Flags
    std::cerr << "    optional flags:" << std::endl;
    std::cerr << std::endl;
    std::cerr << "-h | --help : Print usage instructions." << std::endl;
    std::cerr << std::endl;

    std::cerr << "    render flags: " << std::endl;
    std::cerr << "-c | --config <path>  : Set an optional configuration file." << std::endl;
    std::cerr << std::endl;

    std::exit(-1);
}


/**
 * Initialize DEM Manager
*/
void Initialize_DEM_Manager( Options const& options ){
    
    /// Initialize the dem manager
    GEO::DEM::The_DEM_Manager::Initialize();

    /// Add the terrain data sources
    for( int i=0; i<options.Get_DEM_Drivers().size(); i++ ){
        GEO::DEM::The_DEM_Manager::Instance_Of()->Add_DEM_IO_Driver( options.Get_DEM_Drivers()[i] );
    }
}

/**
 * Initialize Data
*/
void Initialize_Data( Data_Container& data, 
                      Options const& options )
{

    // Activate the DEM Manager
    data.dem_manager = GEO::DEM::The_DEM_Manager::Instance_Of();

    // Create the elevation tile from the DEM Manager
    data.elevation_tile = data.dem_manager->Create_Elevation_Tile<GEO::CRD::CoordinateUTM<double>>( options.Get_Min_Image_Bound(),
                                                                                                    options.Get_Image_Size(),
                                                                                                    options.Get_GSD());
    
    // Make sure the elevation tile initialize properly
    if( data.elevation_tile == nullptr ){
        throw std::runtime_error("error: Elevation tile returned was null.");
    }

    // Load the requested images
}

