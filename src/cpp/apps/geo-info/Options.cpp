/**
 * @file    Options.cpp
 * @author  Marvin Smith
 * @date    5/18/2014
*/
#include "Options.hpp"

/**
 * Set Default Options
*/
void Options::setDefaults(){

}

/**
 * Set the application name
*/
void Options::setAppName( const std::string& appName ){
    this->m_appName = appName;
}

/**
 * Get the application name
*/
std::string Options::getAppName()const{
    return this->m_appName;
}

/**
 * Parse the Command-Line 
*/
Options parse_command_line( int argc, char* argv[] ){

    // output
    Options options;

    // set the app name
    options.setAppName( argv[0] );

    // return output
    return options;

}

