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

        /// If we have WGS84
        case Datum::WGS84:
            return "WGS84";
        default:
            throw std::runtime_error("Unknown datum.");
    }
}

} /// End of Namespace GEO

