/**
 * @file    GDU_Options.hpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#ifndef __GEOEXPLORE_APPS_GEO_DEM_UTILITY_GDU_OPTIONS_HPP__
#define __GEOEXPLORE_APPS_GEO_DEM_UTILITY_GDU_OPTIONS_HPP__

// Boost Libraries
#include <boost/filesystem.hpp>

// GeoExplore Libraries
#include <GeoExplore.hpp>

// PugiXML
#include <thirdparty/pugixml/pugixml.hpp>

using namespace GEO;

/**
 * @class GDU Mode
*/
enum class GDU_Mode{
    GENCONFIG,
    RENDER,
};

/**
 * @class GDU_Options
*/
class GDU_Options{

    public:
        
        /**
         * @brief Constructor
        */
        GDU_Options();
        
        
        /**
         * @brief Initialize
        */
        void Initialize( int argc, char* argv[] );

        
        /**
         * @brief Parse Command-Line Options
        */
        void Parse_Command_Line( int argc, char* argv[] );


        /**
         * @brief Parse Configuration File
        */
        void Parse_Configuration_File();


        /**
         * @brief Generate a configuration file
        */
        void Generate_Configuration_File( );

        
        /** 
         * @brief Finalize the configuration
        */
        void Finalize();

        
        /**
         * @brief Print Usage Instructions
         *
         * @param[in] exit_code Exit code to quit with.
        */
        void Usage( const int& exit_code = -1 );


        /**
         * @brief Get the program mode.
        */
        inline GDU_Mode Get_Program_Mode()const{
            return m_gdu_mode;
        }

        /** 
         * @brief Get render center coordinate.
         */
        inline CRD::CoordinateUTM_d Get_Render_Center_Coordinate()const{
            return m_render_center_coordinate;
        }


        /**
         * @brief Get the Render GSD
        */
        inline double Get_Render_GSD()const{
            return m_render_gsd;
        }


        /**
         * @brief Get the Render Image Size
        */
        inline A_Size<int> Get_Render_Image_Size()const{
            return m_render_image_size;
        }

    private:

        /**
         * @brief Set Default Options
        */
        void Set_Defaults();

        /**
         * @brief Parse the terrain sources node.
        */
        void Parse_Terrain_Sources_Node( pugi::xml_node& terrain_node );
        
        /**
         * @brief Parse the render node.
        */
        void Parse_Render_Node( pugi::xml_node& render_node );

        /// Application Name
        std::string m_application_name;
        
        /// Gen mode
        GDU_Mode m_gdu_mode;

        /// Flag to generate configuration file
        bool m_generate_configuration_file;

        /// Configuration File to Load
        boost::filesystem::path m_configuration_file;

        /// Configuration File to Generate
        boost::filesystem::path m_configuration_file_to_generate;
    
        /// Render Center Coordinate
        CRD::CoordinateUTM_d m_render_center_coordinate;

        /// Render GSD
        double m_render_gsd;

        /// Render Image Size
        A_Size<int> m_render_image_size;

}; // End of GDU_Options class


#endif
