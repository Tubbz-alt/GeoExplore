/**
 * @file    Coordinate_Test_Harness.cpp
 * @author  Marvin Smith
 * @date    3/25/2015
*/
#include "Coordinate_Test_Harness.hpp"

// C++ Standard Libraries
#include <iostream>

// GeoExplore Libraries
#include "../../lib/thirdparty/pugixml/pugixml.hpp"

using namespace GEO;


// Instance of the coordinate test harness
static Coordinate_Test_Harness::ptr_t coordinate_harness_instance = nullptr;

/**
 * Constructor
*/
Coordinate_Test_Set::Coordinate_Test_Set( const std::string& coordinate_name,  
                                          const std::vector<CRD::CoordinateBase<double>::ptr_t>& coordinate_list )
  : m_coordinate_name(coordinate_name),
    m_coordinate_list( coordinate_list )
{

}

/**
 * Constructor
*/
Coordinate_Test_Harness::Coordinate_Test_Harness()
{

}

/**
 * Initialize the harness
*/
Status Coordinate_Test_Harness::Initialize( boost::filesystem::path const& pathname ){

    
    // Create a status object
    Status status;
    
    // Parse the configuration file
    status = Parse_Configuration_File( pathname );

    // return success
    return status;
}


/* 
* Get instance
*/
Coordinate_Test_Harness::ptr_t  Coordinate_Test_Harness::Instance_Of(){

    if( coordinate_harness_instance == nullptr ){

        // Create new harness instance
        coordinate_harness_instance = Coordinate_Test_Harness::ptr_t( new Coordinate_Test_Harness());
    }

    return coordinate_harness_instance;
}

/**
  *Parse the config file
 */
Status Coordinate_Test_Harness::Parse_Configuration_File( boost::filesystem::path const& pathname )
{

    // Make sure the file exists
    if( boost::filesystem::exists( pathname ) != true ){
        return Status( StatusType::FAILURE, 
                       CoreStatusReason::PATH_DOES_NOT_EXIST,
                       "Pathname does not exist." );
    }

    // Temp Coordinate List
    std::vector<CRD::CoordinateBase<double>::ptr_t> temp_coordinate_list;

    // Create the pugixml document
    pugi::xml_document doc;

    // Parse the document
    pugi::xml_parse_result result = doc.load_file( pathname.c_str() );

    // Make sure there were no errors
    if( result != true ){
        return Status( StatusType::FAILURE,
                       CoreStatusReason::GENERAL_IO_ERROR,
                       "XML file parsed with errors.");
    }

    // get the root node
    pugi::xml_node root_node = doc.child("GeoExplore").child("Unit_Test_Data").child("coordinate_test_harness");

    // Check that the node has a coordinate list node
    pugi::xml_node coordinates_node = root_node.child("coordinates");

    // Iterate over all coordinate nodes
    for (pugi::xml_node_iterator cit = coordinates_node.begin(); cit != coordinates_node.end(); ++cit)
    {
        // Make sure its a coordinate
        if( std::string(cit->name()) != "coordinate" ){
            continue;
        }

        // Get the node
        pugi::xml_node coordinate_node = (*cit);
        
        // Get the name
        std::string coordinate_name = cit->attribute("name").as_string();
        
        // Clear the temporary coordinate list
        temp_coordinate_list.clear();

        // Iterate over each position node
        for( pugi::xml_node_iterator pit = coordinate_node.begin(); 
             pit != coordinate_node.end(); 
             pit++ )
        {

            // Process Geographic
            if( std::string(pit->name()) == "position_utm" ){
                
                // Latitude
                double latitude_degrees = pit->attribute("latitude_degrees").as_double();

                // Longitude
                double longitude_degrees = pit->attribute("longitude_degrees").as_double();

                /// Elevation
                double elevation_meters = pit->attribute("elevation_meters").as_double();

                // Datum
                Datum datum_type = StringToDatum( pit->attribute("datum").as_string());

                // Create coordinate
                CRD::CoordinateBase<double>::ptr_t temp_coordinate( new CRD::CoordinateGeographic_d( latitude_degrees, 
                                                                                                     longitude_degrees,
                                                                                                     elevation_meters,
                                                                                                     datum_type ));

                // Add to list
                temp_coordinate_list.push_back( temp_coordinate );

            }

            // Process UTM
            else if( std::string(pit->name()) == "position_geographic"){

                // Zone
                int zone = pit->attribute("zone").as_int();

                // Hemisphere
                bool is_northern = pit->attribute("is_northern").as_bool();

                // Easting
                double easting_meters  = pit->attribute("easting_meters").as_double();
                
                // Northing
                double northing_meters = pit->attribute("northing_meters").as_double();
                
                // Elevation
                double elevation_meters = pit->attribute("elevation_meters").as_double();

                // Datum 
                Datum datum = StringToDatum( pit->attribute("datum").as_string());
                
                // Create the coordinate
                CRD::CoordinateBase<double>::ptr_t temp_coordinate(new CRD::CoordinateUTM_d( zone, is_northern,
                                                                                              easting_meters,
                                                                                              northing_meters,
                                                                                              elevation_meters,
                                                                                              datum ));

                // Add to the list
                temp_coordinate_list.push_back(temp_coordinate);

            }

            // Otherwise, throw an error
            else{

                std::cerr << "Unknown node in the file." << std::endl;
                std::exit(1);

            }


        }

        // Add the set
        m_coordinate_test_sets.push_back( Coordinate_Test_Set( coordinate_name,
                                                               temp_coordinate_list ));

    }

    // return success
    return Status(StatusType::SUCCESS);
}


