/**
 * @file    System_Utilities.cpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#include "System_Utilities.hpp"

// C++ Standard Libraries
#include <cstdlib>
#include <cstdio>
#include <iostream>

namespace GEO{


/**
 * System Call
*/
std::string System_Call( const std::string& command,
                         const std::string& arguments )
{

    // Create file
    FILE*  system_call_id = popen( command.c_str(),
                                   arguments.c_str());

    // Check if it opened
    if( system_call_id == NULL || 
        system_call_id == nullptr )
    {
        return "";
    }

    // Otherwise, get buffer
    std::string output;

    char buffer[1024];
    while( fgets(buffer, sizeof(buffer), system_call_id ) != NULL )
    {
        output += buffer;
    }
    
    // Close
    pclose(system_call_id);

    // return 
    return output;

}



} // End of GEO Namespace

