/**
 * @file    Options.hpp
 * @author  Josh Gleason
 * @date    4/17/2014
 */
#ifndef __SRC_APPS_TERRAINEXPLORE_OPTIONS_HPP
#define __SRC_APPS_TERRAINEXPLORE_OPTIONS_HPP

/// C++ Headers
#include <string>

/**
 * @class Options
 */
class Options
{
public:
    /**
     * Default Constructor
     */
    Options() {}

    /// Application name
    std::string appName;
}; // class Options

/**
 * Print Usage Instructions
 */
void usage(const std::string& appName);

/**
 * Parse Command-Line Options
 */
Options parse_command_line(int argc, char* argv[]);

#endif // __SRC_APPS_TERRAINEXPLORE_OPTIONS_HPP

