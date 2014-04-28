/**
 * @file    Utilities.hpp
 * @author  Marvin Smith
 * @date    4/28/2014
 */
#ifndef __SRC_CPP_APPS_GEOCONVERT_UTILITIES_HPP__
#define __SRC_CPP_APPS_GEOCONVERT_UTILITIES_HPP__

/// C++ Standard Libraries
#include <string>

/// GeoExplore Library
#include <GeoExplore.hpp>

/**
 * Convert a string into its coordinate type
 */
GEO::CoordinateType String2CoordinateType( std::string const& ctype );



#endif
