/**
 * @file    Configuration_Options.hpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#ifndef __GEOEXPLORE_APPS_GEORENDERUTILITY_CONFIGURATION_OPTIONS_HPP__
#define __GEOEXPLORE_APPS_GEORENDERUTILITY_CONFIGURATION_OPTIONS_HPP__

// Boost Libraries
#include <boost/filesystem.hpp>

// C++ Standard Libraries
#include <string>

// Pugixml
#include "../../../lib/thirdparty/pugixml/pugixml.hpp"

// GeoExplore
#include <coordinate/CoordinateUTM.hpp>
#include "../../../lib/core.hpp"
#include "../../../lib/dem/A_DEM_IO_Driver_SRTM.hpp"

using namespace GEO;

/** 
 * @class Configuration_Options
*/
class Configuration_Options{

    public:
        
        /**
         * Constructor
        */
        Configuration_Options();
        
        /**
         * @brief Initialize
        */
        void Initialize( int argc, char* argv[] );


        /**
         * @brief Get the render center coordinate.
        */
        inline CRD::CoordinateUTM_d Get_Render_Center_Coordinate()const{
            return m_render_center_coordinate;
        }

        
        /**
          * @brief Get the Render GSD Node
         */
         inline double Get_Render_GSD()const{
             return m_render_gsd;
         }


        /**
         * @brief Get the Viewer Window Name
        */
        inline std::string Get_Viewer_Window_Name()const{
            return m_viewer_window_name;
        }


        /**
         * @brief Get the Window Viewer Size
        */
        inline A_Size<int> Get_Viewer_Window_Size()const{
            return m_viewer_window_size;
        }

        
        /**
         * @brief Get the DEM IO Driver List
        */
        inline std::vector<DEM::A_DEM_IO_Driver_Base::ptr_t> Get_DEM_Driver_List()const{
            return m_dem_driver_list;
        }


    private:

        /**
         * @brief Parse the Command-Line
         */
        void Parse_Command_Line( int argc, char* argv[] );


        /**
         * @brief Read the configuration file
        */
        void Parse_Configuration_File();

        
        /**
         * @brief Parse the Render Configuration
        */
        void Parse_Render_Configuration( pugi::xml_node& render_config_node );


        /**
         * @brief Parse the Viewer Configuration
        */
        void Parse_Viewer_Configuration( pugi::xml_node& viewer_config_node );
        
        
        /**
         * @brief Parse the Terrain Configuration node.
        */
        void Parse_Terrain_Configuration( pugi::xml_node& terrain_config_node );


        /**
         * @brief Print Usage Instructions
        */
        void Usage()const;


        /// Configuration File Path
        boost::filesystem::path m_configuration_path;
        
        /// Render Center Point
        CRD::CoordinateUTM_d m_render_center_coordinate;
    
        /// Render GSD
        double m_render_gsd;

        /// Window Name
        std::string m_viewer_window_name;

        /// Window Size
        A_Size<int> m_viewer_window_size;
        
        /// Terrain Driver List
        std::vector<DEM::A_DEM_IO_Driver_Base::ptr_t> m_dem_driver_list;


}; // End of Configuration_Options Class



#endif
