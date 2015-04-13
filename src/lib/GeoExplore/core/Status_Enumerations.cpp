/**
 * @brief    Status_Enumerations.cpp
 * @author   Marvin Smith
 * @date     4/1/2015
*/
#include "Status_Enumerations.hpp"

namespace GEO{

/**
 * Convert Status Type to String
*/
std::string StatusTypeToString( StatusType const& status_type )
{
    if( status_type == StatusType::SUCCESS ){
        return "SUCCESS";
    }
    if( status_type == StatusType::WARNING ){
        return "WARNING";
    }
    return "FAILURE";
}


} // End of GEO Namespace

