/**
 * @file     Data_Container.hpp
 * @author   Marvin Smith
 * @date     3/27/2015
*/
#ifndef __GEOEXPLORE_APP_GEO_RENDER_DATA_CONTAINER_HPP__
#define __GEOEXPLORE_APP_GEO_RENDER_DATA_CONTAINER_HPP__

// GeoExplore Libraries
#include <GeoExplore/dem/DEM_Manager.hpp>
#include <GeoExplore/image/Image.hpp>
#include <GeoExplore/image/Pixel_Types.hpp>

// Render Utility Libraries
#include "Configuration_Options.hpp"

// C++ Standard Libraries
#include <memory>

using namespace GEO;

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


        /**
         * @brief Get Terrain Buffer
         */
        inline int Get_Terrain_Buffer( float*& terrain_buffer )const
        {
            terrain_buffer = m_terrain_buffer;
            return m_terrain_buffer_size;
        }
        
        
        /**
         * @brief Get Terrain Buffer
         */
        inline int Get_Terrain_Color_Buffer( float*& terrain_color_buffer )const
        {
            terrain_color_buffer = m_terrain_color_buffer;
            return m_terrain_buffer_size;
        }


        /**
         * @brief Get Tile Center
         *
         * @return Tile Center Coordinate.
        */
        inline CRD::CoordinateUTM_d Get_Tile_Center()const{
            return m_tile_center_coordinate;
        }


    private:
        
        /// Class Name
        std::string m_class_name;

        /// Terrain DEM Manager
        GEO::DEM::DEM_Manager::ptr_t m_dem_manager;

        /// List of images
        std::vector<IMG::Image<IMG::PixelRGBA_u8>::ptr_t>  m_image_list;

        /// Terrain Vertex Buffer
        float* m_terrain_buffer;

        /// Terrain Vertex Buffer Size
        int m_terrain_buffer_size;

        /// Terrain Color Buffer
        float* m_terrain_color_buffer;

        /// Tile Center Coordinate
        CRD::CoordinateUTM_d m_tile_center_coordinate;

}; // End of Data_Container Class



#endif
