/**
 * @file    StringUtilities.cpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#include "StringUtilities.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace GEO{

/**
 * Split a string
 */
std::vector<std::string> string_split( const std::string& input, std::string const& pattern ){

    /// create output
    std::vector<std::string> output;
    boost::split(output, input, boost::is_any_of(pattern));
    return output;

}

/**
 * Convert string to lower case
 */
std::string string_toLower( const string& in ){
    
    string value = in;
    std::transform( in.begin(), in.end(), value.begin(), ::tolower);
    return value;
}

/**
 * Convert string to upper case
 */
std::string string_toUpper( const string& in ){

    string value = in;
    std::transform( in.begin(), in.end(), value.begin(), ::toupper);
    return value;
}

/**
 * Trim string
*/
std::string string_trim( const std::string& str ){
    std::string output = str;
    boost::trim(output);
    return output;
}

/**
 * Trim String
 */
std::string string_trim( const std::string& str,
                         const std::string& pattern )
{
    std::string output = str;
    boost::trim_if(output, boost::is_any_of(pattern));
    return output;
}


 
}/// End of GEO Namespace

