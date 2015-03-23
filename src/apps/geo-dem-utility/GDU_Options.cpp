/**
 * @file    GDU_Options.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include "GDU_Options.hpp"

// C++ Standard Libraries
#include <cstdlib>

/**
 * Constructor
*/
GDU_Options::GDU_Options(){

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
 * Parse the configuration file
*/
void GDU_Options::Parse_Configuration_File(){

}

/**
 * Generate the configuration file
*/
void GDU_Options::Generate_Configuration_File( ){


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

