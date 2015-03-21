/**
 * @file    Globals.hpp
 * @author  Marvin Smith
 * @date    8/2/2014
*/
#ifndef __GEOEXPLORE_SRC_CPP_APPS_GEOUTILITY_GLOBALS_HPP__
#define __GEOEXPLORE_SRC_CPP_APPS_GEOUTILITY_GLOBALS_HPP__

// GeoExplore Libraries
#include <GeoExplore.hpp>

// C++ Standard Libraries
#include <vector>

using namespace GEO;

class Data_Container{

    public:

        /// DEM Manager
        DEM::DEM_Manager::ptr_t dem_manager;

        /// Elevation Tile
        DEM::ElevationTileUTM_d::ptr_t elevation_tile;

        /// Image Tile 
        std::vector<IMG::Image<IMG::PixelRGBA_u8>::ptr_t> image_list; 

}; /// End of Data_Container Class



#endif

