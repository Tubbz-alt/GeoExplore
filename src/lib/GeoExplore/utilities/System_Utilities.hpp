/**
 * @file    System_Utilities.hpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#ifndef __GEOEXPLORE_LIB_UTILITIES_SYSTEM_UTILITIES_HPP__
#define __GEOEXPLORE_LIB_UTILITIES_SYSTEM_UTILITIES_HPP__

// C++ Standard Libraries
#include <string>

namespace GEO{

/**
 * @brief Run a System Call and Return Output
*/
std::string System_Call( const std::string& command,
                         const std::string& arguments = "r" );



} // End of GEO Namespace

#endif
