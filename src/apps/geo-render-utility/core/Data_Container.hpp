/**
 * @file     Data_Container.hpp
 * @author   Marvin Smith
 * @date     3/27/2015
*/
#ifndef __GEOEXPLORE_APP_GEO_RENDER_DATA_CONTAINER_HPP__
#define __GEOEXPLORE_APP_GEO_RENDER_DATA_CONTAINER_HPP__

// GeoExplore Libraries
#include "../../../lib/dem/DEM_Manager.hpp"

// Render Utility Libraries
#include "Configuration_Options.hpp"

// C++ Standard Libraries
#include <memory>

/**
 * @class Data_Container
*/
class Data_Container{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<Data_Container> ptr_t;
        
        /**
         * @brief Load and configure the internal data.
        */
        void Load_Data( const Configuration_Options& options );


        /// Terrain DEM Manager
        GEO::DEM::DEM_Manager::ptr_t dem_manager;

}; // End of Data_Container Class


#endif
