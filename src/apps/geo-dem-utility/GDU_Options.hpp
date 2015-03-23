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


    private:

        /**
         * @brief Set Default Options
        */
        void Set_Defaults();

        
        /// Flag to generate configuration file
        bool m_generate_configuration_file;

        /// Configuration File to Generate
        boost::filesystem::path m_configuration_file_to_generate;


}; // End of GDU_Options class


#endif
