/**
 * @file    StringUtilities.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#ifndef __SRC_CORE_STRINGUTILITIES_HPP__
#define __SRC_CORE_STRINGUTILITIES_HPP__

#include <sstream>
#include <string>
#include <vector>

namespace GEO{


/**
 * Convert a string into a number
 *
 * @param[in] in Input string
 *
 * @return Numerical value
 */
template <typename TP>
TP str2num( std::string const& in ){
    
    TP out;
    std::stringstream(in) >> out;
    return out;

}

/**
 * Convert a number into a string
 *
 * @param[in] an input number
 *
 * @return   string representation
 */
template <typename TP>
std::string num2str( TP const& value ){

    std::stringstream sin;
    sin << value;
    return sin.str();
}


/**
 * Split a string into components given a regex to split with
 */
std::vector<std::string> string_split( const std::string& input, const std::string& pattern );

} /// End of GEO Namespace

#endif
