/**
 * @file     Utilities.hpp
 * @author   Marvin Smith
 * @date     8/3/2014
*/
#ifndef __GEOEXPLORE_SRC_CPP_APPS_GEOUTILITY_UTILITIES_HPP__
#define __GEOEXPLORE_SRC_CPP_APPS_GEOUTILITY_UTILITIES_HPP__

/// Geo Utility Libraries
#include "Globals.hpp"
#include "Options.hpp"


/**
 * @brief Parse Command-Line Options
*/
Options Parse_Command_Line( int argc, char* argv[] );


/**
 * Print Usage Instructions
*/
void Usage( Options const& options );


/**
 * Initialize DEM Manager
*/
void Initialize_DEM_Manager( const Options& options );

/**
 * Initialize Data
*/
void Initialize_Data( Data_Container& data, 
                      Options const& options );

#endif

