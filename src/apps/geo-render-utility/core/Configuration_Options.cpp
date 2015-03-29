/**
 * @file    Configuration_Options.cpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#include "Configuration_Options.hpp"

// C++ Standard Libraries
#include <iostream>

// GeoExplore Libraries
#include "../../../lib/config/A_Command_Line_Parser.hpp"

/**
 * COnstructor
*/
Configuration_Options::Configuration_Options()
 : m_viewer_window_size(GEO::A_Size<int>(2000,1000))
{
}

/**
 * Initialize
*/
void Configuration_Options::Initialize( int argc, char* argv[] )
{

    // Parse the command-line
    Parse_Command_Line( argc, argv );

    // Parse the configuration file
    Parse_Configuration_File();

}


/**
 * Parse the Command-Line
*/
void Configuration_Options::Parse_Command_Line( int argc, char* argv[] )
{

    // Create a command-line parser
    GEO::CONFIG::A_Command_Line_Parser parser(argc, argv);

    // Temp Flags
    std::string tempStr;
    bool found_flag, found_value;
    
    // Look for a configuration file
    tempStr = parser.Query_Flag_Value_As_String("-c", found_flag, found_value );
    if( found_flag != true || found_value != true ){
        std::cerr << "Unable to determine the configuration file." << std::endl;
        Usage();
        std::exit(-1);
    }else{
        m_configuration_path = tempStr;
    }


}

/** 
 * Parse the configuration file
*/
void Configuration_Options::Parse_Configuration_File()
{

    // Make sure the configuration file exists
    if( boost::filesystem::exists( m_configuration_path ) == false ){
        std::cerr << "error: Config file (" << m_configuration_path << ") does not exist." << std::endl;
        Usage();
        std::exit(-1);
    }

    // Open the file
    pugi::xml_document doc;

    // Parse the document
    pugi::xml_parse_result result = doc.load_file(m_configuration_path.c_str());
    if( result == false ){
        throw std::runtime_error("File parsed with errors");
    }

    // Look for root node
    pugi::xml_node root = doc.child("geo-render-utility");

    // Iterate over nodes
    for (pugi::xml_node_iterator cit = root.begin(); cit != root.end(); cit++ ){

        // Parse the render-configuration
        if( std::string(cit->name()) == "viewer-window" ){
            Parse_Viewer_Configuration( *cit );
        }
    }

}


/**
 * Parse the render-configuration
*/
void Configuration_Options::Parse_Viewer_Configuration( pugi::xml_node& viewer_config_node )
{
    // Get the window name
    m_viewer_window_name = viewer_config_node.child("name").attribute("value").as_string();

    // Get the window size
    pugi::xml_node window_size_node = viewer_config_node.child("size");

    int width = window_size_node.attribute("width").as_int();
    int height = window_size_node.attribute("height").as_int();

    // Set the size
    m_viewer_window_size = GEO::A_Size<int>(width,height);

}


/**
 * Parse the Terrain Configuration node.
*/
void Configuration_Options::Parse_Terrain_Configuration( pugi::xml_node& terrain_config_node )
{

    // Get the window path
    std::string temp_str;

    // Get the sources node
    pugi::xml_node sources_node = terrain_config_node.child("sources");

    // Iterate over source nodes
    for( pugi::xml_node_iterator sit = sources_node.begin();
         sit != sources_node.end(); sit++ )
    {
        // Check the name
        if( std::string(sit->name()) != "source"){
            std::cerr << "error: Unknown node (" << sit->name() << ") in the terrain/sources configuration." << std::endl;
            std::exit(-1);
        }

        // Get the node
        pugi::xml_node source_node = (*sit);

        // Parse the type
        temp_str = source_node.attribute("type").as_string();

        // Parse SRTM
        if( "srtm" == GEO::string_toLower(temp_str) ){
            
            // Get the path
            temp_str = source_node.attribute("path").as_string();

            // Construct the datasource
            m_dem_driver_list.push_back(GEO::DEM::A_DEM_IO_Driver_SRTM::ptr_t(new GEO::DEM::A_DEM_IO_Driver_SRTM( temp_str )));
        }

        // Otherwise, there is a problem
        else{
            std::cerr << "error: Unknown terrain source type (" << temp_str << ")." << std::endl;
            std::exit(-1);
        }

    }


}


/**
 * Print Usage Instructions
*/
void Configuration_Options::Usage()const{



}

