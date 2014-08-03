/**
 * @file    Options.hpp
 * @author  Marvin Smith
 * @date    8/2/2014
*/
#ifndef __GEOEXPLORE_SRC_CPP_APPS_GEOUTILITY_OPTIONS_HPP__
#define __GEOEXPLORE_SRC_CPP_APPS_GEOUTILITY_OPTIONS_HPP__

// Boost C++ Libraries
#include <boost/filesystem.hpp>

/**
 * @class Options
*/
class Options{

    public:
        
        /**
         * @brief Set the application name
        */
        void Set_Application_Name( boost::filesystem::path const& path );

        /**
         * @brief Get the application name
        */
        boost::filesystem::path Get_Application_Name()const;


}; // End of Options Class

#endif
