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


/******************************************************/
/*                   Constructor                      */
/******************************************************/
Configuration_Options::Configuration_Options()
 : m_max_thread_count(1),
   m_render_gsd(0.25),
   m_viewer_window_size(A_Size<int>(2000,1000))
{
}


/******************************************************/
/*                    Initialize                      */
/******************************************************/
void Configuration_Options::Initialize( int argc, char* argv[] )
{

    // Parse the command-line
    Parse_Command_Line( argc, argv );

    // Parse the configuration file
    Parse_Configuration_File();

}


/******************************************************/
/*              Parse the Command-Line                */
/******************************************************/
void Configuration_Options::Parse_Command_Line( int argc, char* argv[] )
{

    // Create a command-line parser
    CONFIG::A_Command_Line_Parser parser(argc, argv);

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


/******************************************************/
/*           Parse the configuration file             */
/******************************************************/
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

        // Parse the core configuration
        if( std::string(cit->name()) == "core" ){
            Parse_Core_Configuration( *cit );
        }

        // Parse the render configuration
        else if( std::string(cit->name()) == "render" ){
            Parse_Render_Configuration( *cit );
        }

        // Parse the viewer-configuration
        else if( std::string(cit->name()) == "viewer-window" ){
            Parse_Viewer_Configuration( *cit );
        }

        // Parse the DEM 
        else if( std::string(cit->name()) == "terrain" ){
            Parse_Terrain_Configuration( *cit );
        }

        // Otherwise there was an error
        else{
            std::cerr << "error: Unknown node in geo-render-utility node (" << cit->name() << ")." << std::endl;
            std::exit(-1);
        }
    }

}


/******************************************************/
/*              Parse the Core Configuration          */
/******************************************************/
void Configuration_Options::Parse_Core_Configuration( pugi::xml_node& core_config_node )
{

    // Iterate over nodes
    pugi::xml_node_iterator cit = core_config_node.begin();
    pugi::xml_node_iterator cit_end = core_config_node.end();
    for( ; cit != cit_end; cit++ )
    {

        // Check if max threads
        if( std::string(cit->name()) == "max-threads" ){
            m_max_thread_count = cit->attribute("value").as_int();
        }


    }

}


/******************************************************/
/*            Parse the render-configuration          */
/******************************************************/
void Configuration_Options::Parse_Render_Configuration( pugi::xml_node& render_config_node )
{

    // Get the render gsd node
    if( render_config_node.child("gsd") != NULL ){
        m_render_gsd = render_config_node.child("gsd").attribute("value").as_double();
    }

    // Get the center-coordinate node
    pugi::xml_node center_node = render_config_node.child("center-coordinate");

    // Get the type
    std::string type = string_toLower(center_node.attribute("type").as_string());
    if( type == "utm" ){

        // Get the coordinate data
        int zone = center_node.attribute("zone").as_int();
        bool isNorth = center_node.attribute("is_northern").as_bool();
        double easting = center_node.attribute("easting_meters").as_double();
        double northing = center_node.attribute("northing_meters").as_double();
        Datum datum = StringToDatum(center_node.attribute("datum").as_string());
        
        m_render_center_coordinate = CRD::CoordinateUTM_d( zone, isNorth, easting, northing, 0, datum );
    }
    else if( type == "geographic" ){

        // Get the coordinate data
        double latitude = center_node.attribute("latitude_degrees").as_double();
        double longitude = center_node.attribute("longitude_degrees").as_double();
        Datum datum = StringToDatum(center_node.attribute("datum").as_string());

        // Convert to UTM
        CRD::CoordinateGeographic_d geog_coord( latitude, longitude, datum );
        m_render_center_coordinate = CRD::convert_coordinate<CRD::CoordinateUTM_d>( geog_coord );

    }
    else{
        std::cerr << "error: Unknown coordinate type in render center-coordinate (" << type << ")." << std::endl;
        std::exit(-1);
    }

}

/******************************************************/
/*            Parse the viewer-configuration          */
/******************************************************/
void Configuration_Options::Parse_Viewer_Configuration( pugi::xml_node& viewer_config_node )
{
    // Get the window name
    m_viewer_window_name = viewer_config_node.child("name").attribute("value").as_string();

    // Get the window size
    pugi::xml_node window_size_node = viewer_config_node.child("size");

    int width = window_size_node.attribute("width").as_int();
    int height = window_size_node.attribute("height").as_int();

    // Set the size
    m_viewer_window_size = A_Size<int>(width,height);
    
    // Get the vertex shader
    m_vertex_shader_path = viewer_config_node.child("vertex-shader").attribute("path").as_string();
    
    // Get the fragment shader
    m_fragment_shader_path = viewer_config_node.child("fragment-shader").attribute("path").as_string();
}


/**********************************************************/
/*          Parse the Terrain Configuration node.         */
/**********************************************************/
void Configuration_Options::Parse_Terrain_Configuration( pugi::xml_node& terrain_config_node )
{

    // Temp Variables
    Status temp_status;
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
        if( "srtm" == string_toLower(temp_str) ){
            
            // Get the path
            temp_str = source_node.attribute("path").as_string();

            // Construct the datasource
            DEM::A_DEM_IO_Driver_SRTM::ptr_t temp_driver(new DEM::A_DEM_IO_Driver_SRTM( temp_str ));
            
            // Initialize
            temp_status = temp_driver->Initialize();
            if( temp_status.Get_Status_Type() != StatusType::SUCCESS ){
                std::cerr << "error: Unable to initialize the SRTM data source. Details: " << temp_status.Get_Status_Details() << std::endl;
                std::exit(-1);
            }

            // Add driver
            m_dem_driver_list.push_back(temp_driver);

        }

        // Otherwise, there is a problem
        else{
            std::cerr << "error: Unknown terrain source type (" << temp_str << ")." << std::endl;
            std::exit(-1);
        }

    }


}


/*********************************************/
/*         Print Usage Instructions          */
/*********************************************/
void Configuration_Options::Usage()const{



}

