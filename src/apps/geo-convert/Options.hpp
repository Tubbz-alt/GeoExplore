/**
 * @file    Options.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#ifndef __SRC_APPS_GEOCONVERT_OPTIONS_HPP__
#define __SRC_APPS_GEOCONVERT_OPTIONS_HPP__

#include <deque>
#include <string>

/**
 * Conversion Type
 */
enum class ConversionType{
    
    COORDINATE,

}; /// End of ConversionType Enumeration

/**
 * @class Options
 */
class Options{

    public:
        
        /// Name of the application
        std::string appName;
        
        /// Conversion Type
        ConversionType ctype;
        
        /// Input List
        std::deque<std::string> inputs;

        /// Output List
        std::deque<std::string> outputs;

}; /// End of Options class


/**
 * Print Usage Instructions
 */
void usage( const std::string& appName );

/**
 * Parse Command-Line Options
 */
Options parse_command_line( int argc, char* argv[] );



#endif
