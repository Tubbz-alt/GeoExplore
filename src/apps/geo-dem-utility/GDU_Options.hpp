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
#include <GeoExplore/thirdparty/pugixml/pugixml.hpp>

using namespace GEO;

/**
 * @class GDU Mode
*/
enum class GDU_Mode{
    GENCONFIG,
    RENDER,
};


/**
 * @class GDU_Render_Configuration
*/
class GDU_Render_Configuration{

    public:

        /// Pointer Type
        typedef std::shared_ptr<GDU_Render_Configuration> ptr_t;
        
        /// Elevation Type
        typedef IMG::A_Color_Map<IMG::PixelGray_df,IMG::PixelRGBA_u8> ColorMapType;
        
        /// Color Map
        ColorMapType color_relief_map;
        
        /// Render Center Coordinate
        CRD::CoordinateUTM_d center_coordinate;
        
        /// Render GSD
        double gsd;

        // Render Image Size
        A_Size<int> image_size;

        /// Output Image Path
        FS::FilesystemPath output_path;

}; /// End of GDU_Render_Configuration Class


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
         * @brief Get the GDU Render Configuration
        */
        inline GDU_Render_Configuration::ptr_t Get_Render_Configuration()const{
            return m_render_configuration;
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

        /**
         * @brief Parse the color node.
         */
        void Parse_Color_Node( pugi::xml_node& color_node );


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
    
        /// Render Configuration
        GDU_Render_Configuration::ptr_t m_render_configuration;


}; // End of GDU_Options class


#endif
