/**
 * @file    A_Command_Line_Parser.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include "A_Command_Line_Parser.hpp"

namespace GEO{
namespace CONFIG{

/**
 * Constructor
*/
A_Command_Line_Parser::A_Command_Line_Parser( int argc, char* argv[] )
{
    // set the application name
    if( argc > 0 ){
        m_application_name = argv[0];
    }

    // Build the argument list
    for( int arg=1; arg<argc; arg++ ){
        m_argument_list.push_back(argv[arg]);
        m_reference_list.push_back(0);
    }

}

/**
 * Check if a flag exists.
*/
bool A_Command_Line_Parser::Check_If_Flag_Exists( const std::string& flag )
{

    // Iterate through flags
    for( int i=0; i<m_argument_list.size(); i++ ){
        if( flag == m_argument_list[i] ){
            m_reference_list[i]++;
            return true;
        }
    }
    return false;
}


} // End of CONFIG Namespace
} // End of GEO Namespace

