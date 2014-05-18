/**
 * @file    Enumerations.cpp
 * @author  Marvin Smith
 * @date    5/5/2014
*/
#include "Enumerations.hpp"

/// C++ Standard Libraries
#include <stdexcept>


namespace GEO{

/**
 * Convert a DATUM to a Well-Known Text String
*/
std::string Datum2WKT_string( Datum const& datum ){

    switch(datum){
        
        /// If we have EGM96
        case Datum::EGM96:
            return "EGM96";

        /// If we have WGS84
        case Datum::WGS84:
            return "WGS84";
        
        /// If we have NAD83
        case Datum::NAD83:
            return "NAD83";

        default:
            throw std::runtime_error("Unknown datum.");
    }
}

/** 
 * Convert a coordinate type to a string
*/
std::string CoordinateType2String( CoordinateType const& ctype ){

    switch( ctype ){

        case CoordinateType::Base:
            return "Base";
        case CoordinateType::Geodetic:
            return "Geodetic";
        case CoordinateType::UTM:
            return "UTM";
        default:
            throw std::runtime_error("Unknown CoordinateType");
    }
}

} /// End of Namespace GEO

