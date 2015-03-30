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
         * @brief Constructor
        */
        Data_Container();


        /**
         * @brief Load and configure the internal data.
        */
        void Load_Data( const Configuration_Options& options );

        
        /**
         * Fetch the terrain manager
        */
        inline GEO::DEM::DEM_Manager::ptr_t Get_DEM_Manager()const{
            return m_dem_manager;
        }

    private:
        
        /// Class Name
        std::string m_class_name;

        /// Terrain DEM Manager
        GEO::DEM::DEM_Manager::ptr_t m_dem_manager;

}; // End of Data_Container Class


#endif
