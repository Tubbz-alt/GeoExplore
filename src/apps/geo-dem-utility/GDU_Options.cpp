/**
 * @file    GDU_Options.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include "GDU_Options.hpp"

// C++ Standard Libraries
#include <cstdlib>

// PugiXML
#include <thirdparty/pugixml/pugixml.hpp>

using namespace GEO;

/**
 * GDU Command-Line Arguments
*/
class GDU_Command_Line_Arguments{

    public:

        /**
         * Constructor
        */
        GDU_Command_Line_Arguments(){

            // Setup the Usage mode
            USAGE_MODE_FLAGS.clear();
            USAGE_MODE_FLAGS.push_back("-h");
            USAGE_MODE_FLAGS.push_back("--help");

            // Setup the Gen-Config Mode
            GEN_CONFIG_MODE_FLAGS.clear();
            GEN_CONFIG_MODE_FLAGS.push_back("-gen-config");

            // Setup the Gen-Config Path Flag
            GEN_CONFIG_PATH_FLAGS.clear();
            GEN_CONFIG_PATH_FLAGS.push_back("-c");
            GEN_CONFIG_PATH_FLAGS.push_back("--config");

            // Render Mode
            RENDER_MODE_FLAGS.clear();
            RENDER_MODE_FLAGS.push_back("-render");
            
            // Render Mode
            RENDER_PATH_FLAGS.clear();
            RENDER_PATH_FLAGS.push_back("-c");
            RENDER_PATH_FLAGS.push_back("--config");

        }
        
        /// Usage Mode Options
        std::vector<std::string> USAGE_MODE_FLAGS;

        /// Gen-Config Mode 
        std::vector<std::string> GEN_CONFIG_MODE_FLAGS;

        /// Gen-Config Config File 
        std::vector<std::string> GEN_CONFIG_PATH_FLAGS;

        /// Render Mode Flag
        std::vector<std::string> RENDER_MODE_FLAGS;

        /// Render mode config flags
        std::vector<std::string> RENDER_PATH_FLAGS;


};

/**
 * Constructor
*/
GDU_Options::GDU_Options()
 : m_render_configuration(new GDU_Render_Configuration())
{

    // Set default options
    Set_Defaults();

}

/** 
 * Generate Defaults
 */
void GDU_Options::Set_Defaults()
{
    // Set generate flag to false
    m_generate_configuration_file = false;

}


/**
 * Initialize
*/
void GDU_Options::Initialize( int argc, char* argv[] )
{

    // Parse the command-line
    Parse_Command_Line( argc, argv );


    // If we need to, generate the configuration file
    if( m_generate_configuration_file == true ){
        Generate_Configuration_File();
    }
    
    // Parse the Configuration File
    Parse_Configuration_File();
}


/**
 * Parse the Command-Line
*/
void GDU_Options::Parse_Command_Line( int argc, char* argv[] )
{
    // Temp variables
    std::string tempStr;
    bool found_flag, found_value;

    // Get our arguments
    GDU_Command_Line_Arguments arguments;

    // Create a command-line parser
    CONFIG::A_Command_Line_Parser parser(argc, argv);

    // Set the application name
    m_application_name = parser.Get_Application_Name();

    // Check if the help/usage was requested
    if( parser.Check_If_Flag_Exists( arguments.USAGE_MODE_FLAGS ) == true ){
        Usage();
    }

    // Check if the gen-config flag was given
    if( parser.Check_If_Flag_Exists( arguments.GEN_CONFIG_MODE_FLAGS ) == true ){

        // Get the pathname
        tempStr = parser.Query_Flag_Value_As_String( arguments.GEN_CONFIG_PATH_FLAGS, 
                                                     found_flag,
                                                     found_value );
        if( found_flag != true || found_value != true )
        {
            std::cerr << "error: Unable to create an output configuration file." << std::endl;
            Usage();
        }
        m_configuration_file_to_generate = tempStr;

        // set the flag
        m_generate_configuration_file = true;


    }

    // Check if the render flag was givne
    else if( parser.Check_If_Flag_Exists( arguments.RENDER_MODE_FLAGS ) == true ){

        // set the mode
        m_gdu_mode = GDU_Mode::RENDER;

        // Get the configuration file
        tempStr = parser.Query_Flag_Value_As_String( arguments.RENDER_PATH_FLAGS, 
                                                     found_flag,
                                                     found_value );
        if( found_flag != true || found_value != true )
        {
            std::cerr << "error: Unable to find an output configuration file." << std::endl;
            Usage();
        }
        m_configuration_file = tempStr;


    }

    // Otherwise there is an unknown mode
    else{
        std::cerr << "error: Must select one of the required modes." << std::endl;
        Usage(-1);
    }

}


/** 
 * Parse the configuration file
*/
void GDU_Options::Parse_Configuration_File(){
    
    // Make sure the file exists
    if( boost::filesystem::exists( m_configuration_file ) == false ){
        std::cerr << "error: Configuration file does not exist." << std::endl;
        Usage(-1);
    }
    
    //  Get the file
    pugi::xml_document doc;
    
    // Parse the document
    pugi::xml_parse_result result = doc.load_file(m_configuration_file.c_str());
    if( result == false ){
        std::cerr << "error: Configuration file opened with errors." << std::endl;
        Usage(-1);
    }
 
    // Get the root node
    pugi::xml_node root_node = doc.child("geo-dem-utility");

    // Get the terrain node
    pugi::xml_node terrain_node = root_node.child("terrain-sources");
    Parse_Terrain_Sources_Node( terrain_node );

    // Get the render node
    pugi::xml_node render_node = root_node.child("render");
    Parse_Render_Node( render_node );

    // Get the color node
    pugi::xml_node color_node = root_node.child("color-map");
    Parse_Color_Node( color_node );


}

/**
 * Parse the terrain sources node
*/
void GDU_Options::Parse_Terrain_Sources_Node( pugi::xml_node& terrain_node ){
    
    // misc variables
    std::string node_name;
    std::string tempStr;
    Status status;

    // Iterate over each source
    for( pugi::xml_node_iterator tit = terrain_node.begin(); 
         tit != terrain_node.end();
         tit++ )
    {

        // Check the name
        node_name = tit->name();

        // if srtm
        if( node_name == "srtm" ){
        
            // Log
            std::cout << "Initializing SRTM Terrain Driver" << std::endl;
            
            // Get the path
            tempStr = tit->attribute("path").as_string();

            // Create SRTM Driver
            DEM::A_DEM_IO_Driver_SRTM::ptr_t dem_driver(new DEM::A_DEM_IO_Driver_SRTM( tempStr ));
            
            // Initialize Driver
            status = dem_driver->Initialize();
            if( status.Get_Status_Type() != StatusType::SUCCESS ){
                std::cerr << "error: Unable to initialize SRTM DEM Driver. Details: " << status.Get_Status_Details() << std::endl;
                Usage(-1);
            }

            // Add to dem Manager
            DEM::The_DEM_Manager::Instance_Of()->Add_DEM_IO_Driver( dem_driver );

        }

        // if flat
        else if( node_name == "flat" ){

            // Log
            std::cout << "Initializing Flat Terrain Driver." << std::endl;

            // Get the elevation 
            double elevation = tit->attribute("elevation_meters").as_double();

            // Create FLAT Driver
            DEM::A_DEM_IO_Driver_Flat::ptr_t dem_driver(new DEM::A_DEM_IO_Driver_Flat( elevation ));
            
            // Initialize Driver
            status = dem_driver->Initialize();
            if( status.Get_Status_Type() != StatusType::SUCCESS ){
                std::cerr << "error: Unable to initialize Flat DEM Driver. Details: " << status.Get_Status_Details() << std::endl;
                Usage(-1);
            }

            // Add to dem Manager
            DEM::The_DEM_Manager::Instance_Of()->Add_DEM_IO_Driver( dem_driver );


        }
        else{
            std::cerr << "error: Unknown terrain source type (" << node_name << ")." << std::endl;
            std::exit(-1);
        }

    }

}


/**
 * Parse the render node
*/
void GDU_Options::Parse_Render_Node( pugi::xml_node& render_node )
{

    // Iterate over nodes
    pugi::xml_node_iterator rit = render_node.begin();
    for( ; rit != render_node.end(); rit++ )
    {
    
        // Get the render coordinate
        if( std::string(rit->name()) == "center-coordinate" )
        {
            // Get the node
            pugi::xml_node center_node = *rit;

            // Check the type
            std::string coord_type = center_node.attribute("type").as_string();
    
            if( coord_type == "utm" ){
                m_render_configuration->center_coordinate.zone() = center_node.attribute("zone").as_int();
                m_render_configuration->center_coordinate.Is_Northern_Hemisphere() = center_node.attribute("is_northern").as_bool();
                m_render_configuration->center_coordinate.easting_meters()         = center_node.attribute("easting_meters").as_double();
                m_render_configuration->center_coordinate.northing_meters()        = center_node.attribute("northing_meters").as_double();
            }   

            // Geographic coordinate
            else if( coord_type == "geographic" ){
        
                CRD::CoordinateGeographic_d coord;
                coord.latitude_degrees()  = center_node.attribute("latitude_degrees").as_double();
                coord.longitude_degrees() = center_node.attribute("longitude_degrees").as_double();
    
                // Convert to UTM
                m_render_configuration->center_coordinate = CRD::convert_coordinate<CRD::CoordinateUTM_d>(coord);

            }

            // Otherwise, we have an unknown type
            else{
                std::cerr << "error: Unknown coordinate type (" << coord_type << ")." << std::endl;
                Usage(-1);
            }
        }

        // Get the GSD
        else if( std::string(rit->name()) == "gsd" )
        {
            m_render_configuration->gsd = rit->attribute("value").as_double();
        }


        // Get the image size
        else if( std::string(rit->name()) == "image-size" )
        {
            m_render_configuration->image_size = A_Size<int>( rit->attribute("cols").as_int(),
                                                              rit->attribute("rows").as_int());

        }

        // Get the output
        else if( std::string(rit->name()) == "output" )
        {
            // Get the output node
            pugi::xml_node output_node = *rit;

            // Get the path
            m_render_configuration->output_path = FS::FilesystemPath(output_node.attribute("output-image-path").as_string());

        }

        // Otherwise, there is an error
        else{
            std::cerr << "error: Unknown node (" << rit->name() << ")" << std::endl;
            std::exit(-1);
        }
    }
}

/**
 * Parse the Color Node
*/
void GDU_Options::Parse_Color_Node( pugi::xml_node& color_node )
{

    // Get the color list 
    pugi::xml_node colors = color_node.child("color-pairs");

    // Iterate over each color pair
    for( pugi::xml_node_iterator cit = colors.begin();
         cit != colors.end();
         cit++ )
    {

        // Check the name
        if( std::string(cit->name()) != "color-pair" ){
            std::cerr << "error: Invalid node found in color pair list (" << cit->name() << ")" << std::endl;
            std::exit(-1);
        }   

        // Get the elevation and color components
        double elevation = cit->attribute("elevation_meters").as_double();
        int red   = cit->attribute("red_uint8").as_int();
        int green = cit->attribute("green_uint8").as_int();
        int blue  = cit->attribute("blue_uint8").as_int();
        int alpha = cit->attribute("alpha_uint8").as_int();

        // Add to pair list
        m_render_configuration->color_relief_map.Add_Color_Pair( IMG::PixelGray_df(elevation),
                                                                 IMG::PixelRGBA_u8( red, 
                                                                                    green, 
                                                                                    blue, 
                                                                                    alpha));

    }
}


/**
 * Generate the configuration file
*/
void GDU_Options::Generate_Configuration_File( )
{
    
    // Open the file
    pugi::xml_document doc;

    // Get the root node
    pugi::xml_node root_node = doc.append_child("geo-dem-utility");

    // Add the source node
    pugi::xml_node sources_node = root_node.append_child("terrain-sources");

    // Add the srtm source
    pugi::xml_node srtm_source_node = sources_node.append_child("srtm");
    srtm_source_node.append_attribute("path").set_value("data/unit-tests/dems/srtm");
    
    /**************************************************/
    /*              Render Configuration              */
    /**************************************************/
    // Add the render configuration
    pugi::xml_node render_node = root_node.append_child("render");

    // add the center coordinate
    pugi::xml_node render_center_node = render_node.append_child("center-coordinate");
    render_center_node.append_attribute("type").set_value("utm");
    render_center_node.append_attribute("zone").set_value("11");
    render_center_node.append_attribute("is_northern").set_value("true");
    render_center_node.append_attribute("easting_meters").set_value(384409);
    render_center_node.append_attribute("northing_meters").set_value(4048901);

    // Add the gsd
    render_node.append_child("gsd").append_attribute("value").set_value("0.5");

    // add the image size
    pugi::xml_node render_size = render_node.append_child("image-size");
    render_size.append_attribute("cols").set_value(2000);
    render_size.append_attribute("rows").set_value(2000);

    // Add the output information
    pugi::xml_node output_node = render_node.append_child("output");
    output_node.append_attribute("output-image-path").set_value("dem-output.tif");
    
    
    /**************************************************/
    /*               Color Configuration              */
    /**************************************************/
    pugi::xml_node color_node = root_node.append_child("color-map");

    // add the colors node
    pugi::xml_node colors_node = color_node.append_child("color-pairs");

    // Add each color
    pugi::xml_node color_pair01 = colors_node.append_child("color-pair");
    color_pair01.append_attribute("elevation-meters").set_value(3700);
    color_pair01.append_attribute("red_uint8").set_value(200);
    color_pair01.append_attribute("green_uint8").set_value(130);
    color_pair01.append_attribute("blue_uint8").set_value(130);
    color_pair01.append_attribute("alpha_uint8").set_value(255);
    
    pugi::xml_node color_pair02 = colors_node.append_child("color-pair");
    color_pair02.append_attribute("elevation-meters").set_value(3800);
    color_pair02.append_attribute("red_uint8").set_value(110);
    color_pair02.append_attribute("green_uint8").set_value(220);
    color_pair02.append_attribute("blue_uint8").set_value(110);
    color_pair02.append_attribute("alpha_uint8").set_value(255);

    pugi::xml_node color_pair03 = colors_node.append_child("color-pair");
    color_pair03.append_attribute("elevation-meters").set_value(3900);
    color_pair03.append_attribute("red_uint8").set_value(240);
    color_pair03.append_attribute("green_uint8").set_value(250);
    color_pair03.append_attribute("blue_uint8").set_value(160);
    color_pair03.append_attribute("alpha_uint8").set_value(255);

    pugi::xml_node color_pair04 = colors_node.append_child("color-pair");
    color_pair04.append_attribute("elevation-meters").set_value(4050);
    color_pair04.append_attribute("red_uint8").set_value(230);
    color_pair04.append_attribute("green_uint8").set_value(220);
    color_pair04.append_attribute("blue_uint8").set_value(170);
    color_pair04.append_attribute("alpha_uint8").set_value(255);

    pugi::xml_node color_pair05 = colors_node.append_child("color-pair");
    color_pair05.append_attribute("elevation-meters").set_value(4150);
    color_pair05.append_attribute("red_uint8").set_value(220);
    color_pair05.append_attribute("green_uint8").set_value(220);
    color_pair05.append_attribute("blue_uint8").set_value(220);
    color_pair05.append_attribute("alpha_uint8").set_value(255);

    pugi::xml_node color_pair06 = colors_node.append_child("color-pair");
    color_pair06.append_attribute("elevation-meters").set_value(4290);
    color_pair06.append_attribute("red_uint8").set_value(250);
    color_pair06.append_attribute("green_uint8").set_value(250);
    color_pair06.append_attribute("blue_uint8").set_value(250);
    color_pair06.append_attribute("alpha_uint8").set_value(255);

    pugi::xml_node color_pair07 = colors_node.append_child("color-pair");
    color_pair07.append_attribute("elevation-meters").set_value(4420);
    color_pair07.append_attribute("red_uint8").set_value(245);
    color_pair07.append_attribute("green_uint8").set_value(245);
    color_pair07.append_attribute("blue_uint8").set_value(255);
    color_pair07.append_attribute("alpha_uint8").set_value(255);


    // Save the file
    doc.save_file(m_configuration_file_to_generate.c_str());

    // Log Exit
    std::cout << "Configuration file written to " << m_configuration_file_to_generate << std::endl;
    std::exit(0);
}

/*
 * Finalize
*/
void GDU_Options::Finalize(){

    // If we need to generate a configuration file, create the file, then exit
    if( m_generate_configuration_file == true ){
        
        // Generate the file
        Generate_Configuration_File();

        // Exit
        std::exit(0);
    }
}

/**
 * Print Usage
*/
void GDU_Options::Usage( const int& exit_code )
{

    // print header
    std::cerr << std::endl;
    std::cerr << "usage: " << m_application_name << "  [mode-flag] [mode-options]" << std::endl;
    std::cerr << std::endl;
    
    // Modes
    std::cerr << "Modes:" << std::endl;
    std::cerr << "-h | --help  : Print the usage and exit." << std::endl;
    std::cerr << std::endl;

    std::cerr << "-gen-config  -c <config-path>  : Generate configuration file and write to <config-path>." << std::endl;
    std::cerr << std::endl;
    std::cerr << "-render -c <config-path>  : Render DEM image." << std::endl;
    std::cerr << std::endl;

    // Exit
    std::exit(exit_code);
}
