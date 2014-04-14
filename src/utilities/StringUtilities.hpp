/**
 * @file    StringUtilities.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#ifndef __SRC_CORE_STRINGUTILITIES_HPP__
#define __SRC_CORE_STRINGUTILITIES_HPP__

#include <string>
#include <vector>

namespace GEO{

/**
 * Split a string into components given a regex to split with
 */
std::vector<std::string> string_split( const std::string& input, const std::string& pattern );

} /// End of GEO Namespace

#endif
