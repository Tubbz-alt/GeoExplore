/**
 * @file    StringUtilities.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#ifndef __SRC_CORE_STRINGUTILITIES_HPP__
#define __SRC_CORE_STRINGUTILITIES_HPP__

#include <iomanip>
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
 * @param[in] value Input number
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
 * Convert a number into a string
 *
 * @param[in] value Input number
 *
 * @return   string representation
 */
template <typename TP>
std::string num2str( TP const& value, const int& precision ){

    std::stringstream sin;
    sin << std::setprecision(precision) << value;
    return sin.str();
}


/**
 * @brief Trim a string.
 *
 * @param[in] str String to trim.
 *
 * @return Trimmed string.
*/
std::string string_trim( const std::string& str );


/**
 * @brief Trim a string.
 *
 * @param[in] str String to trim.
 * @param[in] trim_pattern Characters to trim if found.
 *
 * @return Trimmed string.
 */
std::string string_trim( const std::string& str, 
                         const std::string& trim_pattern );

/**
 * @brief Split a string into components given a regex to split with.
 *
 * @param[in] input Input string.
 * @param[in] pattern for splitting.
 * 
 * @return split strings.
 */
std::vector<std::string> string_split( const std::string& input, 
                                       const std::string& pattern );

/**
 * @brief Convert all characters to upper case
 *
 * @return Upper-Case string.
 */
std::string string_toUpper( const std::string& str );

/**
 * @brief Convert all characters to lower case.
 *
 * @return Lower case string.
 */
std::string string_toLower( const std::string& str );


} /// End of GEO Namespace

#endif
