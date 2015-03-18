/**
 * @file    Options.hpp
 * @author  Marvin Smith
 * @date    8/2/2014
*/
#ifndef __GEOEXPLORE_SRC_CPP_APPS_GEOUTILITY_OPTIONS_HPP__
#define __GEOEXPLORE_SRC_CPP_APPS_GEOUTILITY_OPTIONS_HPP__

// Boost C++ Libraries
#include <boost/filesystem.hpp>

// GeoExplore Libraries
#include "../../lib/thirdparty/pugixml/pugixml.hpp"
#include <GeoExplore.hpp>

/**
 * @class Options
*/
class Options{

    public:

        /**
         * @brief Constructor
        */
        Options();
        
        /**
         * @brief Set the application name
        */
        inline void Set_Application_Name( boost::filesystem::path const& application_name ){
            m_application_name = application_name;
        }

        /**
         * @brief Get the application name
        */
        inline boost::filesystem::path Get_Application_Name()const{
            return m_application_name;
        }
    
        
        /**
         * @brief Set the Configuration File Name
        */
        inline void Set_Configuration_File( boost::filesystem::path const& configuration_file ){
            m_configuration_file = configuration_file;
            m_configuration_file_provided = true;
        }

    
        /**
         * Get the image gsd
        */
        inline double Get_GSD()const{
            return m_gsd;
        }


        /**
         * Get the image size
        */
        inline GEO::A_Size<int> Get_Image_Size()const{
            return m_image_size;
        }


        /**
         * Get the image bounds
        */
        inline GEO::CRD::CoordinateUTM_d Get_Min_Image_Bound()const{
            return m_min_image_bound;
        }

        /**
         * Get the max image bound
        */
        inline GEO::CRD::CoordinateUTM_d Get_Max_Image_Bound()const{
            return m_max_image_bound;
        }


        /**
         * @brief Get the Configuration File Name
        */
        inline boost::filesystem::path Get_Configuration_File()const{
            return m_configuration_file;
        }
        

        /**
         * Finalize Configuration
        */
        void Finalize();
    

        /**
         * Get the dem driver list
         */
        inline std::vector<GEO::DEM::A_DEM_IO_Driver_Base::ptr_t> Get_DEM_Drivers()const{
            return m_dem_drivers;
        }

        /**
         * Get the image list
         */
        inline std::deque<boost::filesystem::path> Get_Image_List()const{
            return m_image_paths;
        }

        /**
         * Add Image to List
        */
        inline void Add_Image_Path( boost::filesystem::path const& image_path ){
            m_image_paths.push_back(image_path);
        }

    
    private:

        /**
         * Generate a configuration file
        */
        void Generate_Configuration_File();
        
        /**
         * Load the configuration file
        */
        void Load_Configuration_File();

        /**
         * Parse the render configuration
        */
        void Parse_Render_Configuration( pugi::xml_node& render_config_node );
        
        /**
         * Parse the DEM Configuration
        */
        void Parse_DEM_Configuration( pugi::xml_node& dem_config_node );
        
        /**
         * Parse the Image List
        */
        void Parse_Image_List( pugi::xml_node* image_list_node );


        /// Application Name
        boost::filesystem::path m_application_name; 

        /// Configuration File
        boost::filesystem::path m_configuration_file;
        
        /// Flag if user provided configuration file
        bool m_configuration_file_provided;


        /// Image Bounds
        GEO::CRD::CoordinateUTM_d m_min_image_bound;
        GEO::CRD::CoordinateUTM_d m_max_image_bound;

        /// Image Size
        GEO::A_Size<int> m_image_size;

        /// Image GSD
        double m_gsd;

        /// List of DEM IO Drivers
        std::vector<GEO::DEM::A_DEM_IO_Driver_Base::ptr_t> m_dem_drivers;

        /// List of Images
        std::deque<boost::filesystem::path> m_image_paths;

}; // End of Options Class

#endif
