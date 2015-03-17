/**
 * @file    Options.hpp
 * @author  Marvin Smith
 * @date    5/16/2014
*/
#ifndef __GEOEXPLORE_APPS_GEOINFO_OPTIONS_HPP__
#define __GEOEXPLORE_APPS_GEOINFO_OPTIONS_HPP__

/// C++ Standard Library
#include <string>

/**
 * Options container
*/
class Options { 

    public:
        
        /**
         * Set the default values
        */
        void setDefaults();

        /**
         * Set the application name
        */
        void setAppName( const std::string& appName );

        /**
         * Get the application name
        */
        std::string getAppName()const;


    private:
        
        /// Application Name
        std::string m_appName;


}; /// End of Options Class


/**
 * Parse Command-Line Options
*/
Options parse_command_line( int argc, char* argv[] );


#endif
