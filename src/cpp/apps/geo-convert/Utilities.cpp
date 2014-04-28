/**
 * @file    Utilities.cpp
 * @author  Marvin Smith
 * @date    4/28/2014
 */
#include "Utilities.hpp"

/**
 * Convert a string into its coordinate type
 */
GEO::CoordinateType String2CoordinateType( std::string const& ctype ){

    // check for utm
    if( ctype == "-utm" ){
        return GEO::CoordinateType::UTM;
    }

    // check for geodd
    else if( ctype == "-geod-dd" || "-geod-dm" || "-geod-dms" ){
        return GEO::CoordinateType::Geodetic;
    }

    // otherwise we have an error
    else{
        throw std::runtime_error(std::string("Unknown output type (")+ctype+std::string(")"));
    }

    return GEO::CoordinateType::Base;
}

