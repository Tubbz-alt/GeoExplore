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


/*****************************************************/
/*                Check if a flag exists.            */
/*****************************************************/
bool A_Command_Line_Parser::Check_If_Flag_Exists( const std::string& flag )
{

    // Iterate through flags
    for( int i=0; i<(int)m_argument_list.size(); i++ ){
        if( flag == m_argument_list[i] ){
            m_reference_list[i]++;
            return true;
        }
    }
    return false;
}


/*****************************************************/
/*                Check if a flag exists.            */
/*****************************************************/
bool A_Command_Line_Parser::Check_If_Flag_Exists( const std::vector<std::string>& flags )
{

    // Iterate over flags
    for( int i=0; i<(int)flags.size(); i++ ){
        if( Check_If_Flag_Exists(flags[i]) == true ){
            return true;
        }
    }
    return false;
}



/*************************************/
/*          Get the Value            */
/*************************************/
std::string A_Command_Line_Parser::Query_Flag_Value_As_String( const std::string& flag,   
                                                               bool&          flag_found,
                                                               bool&          value_found )
{

    // Set flags to false
    flag_found = false;
    value_found = false;

    // Iterate through flags
    for( int i=0; i<(int)m_argument_list.size(); i++ )
    {
        // Check if flag found
        if( flag == m_argument_list[i] ){
            
            flag_found = true;

            if( i < (((int)m_argument_list.size())-1) && m_reference_list[i+1] < 1 ){
                value_found = true;
                m_reference_list[i]++;
                return m_argument_list[i+1];
            }
            else{
                return "";
            }
        }
    }   

    return "";
}

/*************************************/
/*          Get the Value            */
/*************************************/
std::string A_Command_Line_Parser::Query_Flag_Value_As_String( const std::vector<std::string>& flags,   
                                                               bool&          flag_found,
                                                               bool&          value_found )
{
    // temp stuff
    std::string tempStr = "";

    // Iterate over flags
    for( int i=0; i<(int)flags.size(); i++ ){
        
        tempStr = Query_Flag_Value_As_String( flags[i], flag_found, value_found );
        if( flag_found == true ){
            return tempStr;
        }

    }

    return tempStr;
}

} // End of CONFIG Namespace
} // End of GEO Namespace

