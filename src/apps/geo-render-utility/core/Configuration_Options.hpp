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
         * @brief Get the number of max threads to use.
         *
         * @return Number of threads.
        */
        inline int Get_Max_Threads()const{
            return m_max_thread_count;
        }


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
        

        /**
         * @brief Get the Vertex Shader Path 
         *
         * @return Vertex Shader Path.
         */
        inline FS::FilesystemPath Get_Vertex_Shader_Path()const{
            return m_vertex_shader_path;
        }


        /**
         * @brief Get the Fragment Shader Path
         *
         * @return Fragment Shader Path.
        */
        inline FS::FilesystemPath Get_Fragment_Shader_Path()const{
            return m_fragment_shader_path;
        }

        
        /**
         * @brief Get the Viewer FOV Angle in Degrees.
         *
         * @return FOV Angle in Degrees.
        */
        inline double Get_Viewer_FOV_Angle_Degrees()const{
            return m_viewer_fov_angle_degrees;
        }


        /**
         * @brief Get the Viewer Aspect Ratio.
         *
         * @return Viewer aspect ratio.
         */
        inline double Get_Viewer_Aspect_Ratio()const{
            return m_viewer_aspect_ratio;
        }


        /**
         * @brief Get the Viewer Min Clipping Distance.
         *
         * @return Viewer min clipping distance.
        */
        inline double Get_Viewer_Min_Clipping()const{
            return m_viewer_min_clipping;
        }


        /**
         * @brief Get the Viewer Max Clipping Distance.
         *
         * @return Viewer max clipping distance.
        */
        inline double Get_Viewer_Max_Clipping()const{
            return m_viewer_max_clipping;
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
         * @brief Parse the Core Configuration
        */
        void Parse_Core_Configuration( pugi::xml_node& core_config_node );


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

        /// Max Thread Count
        int m_max_thread_count;

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

        /// Fragment Shader Path
        FS::FilesystemPath m_fragment_shader_path;

        /// Vertex Shader Path
        FS::FilesystemPath m_vertex_shader_path;

        /// FOV Angle
        double m_viewer_fov_angle_degrees;

        /// Aspect ratio 
        double m_viewer_aspect_ratio;

        /// Min Clipping Distance
        double m_viewer_min_clipping;

        /// Max Clipping
        double m_viewer_max_clipping;


}; // End of Configuration_Options Class



#endif
