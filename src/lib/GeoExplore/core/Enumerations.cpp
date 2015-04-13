/**
 * @file    Enumerations.cpp
 * @author  Marvin Smith
 * @date    5/5/2014
*/
#include "Enumerations.hpp"

/// C++ Standard Libraries
#include <stdexcept>

// GeoExplore Libraries
#include "../utilities/StringUtilities.hpp"


namespace GEO{

/**
 * Convert a Datum to String
*/
std::string DatumToString( const Datum& datum )
{
    // Check if WGS84
    if( datum == Datum::WGS84 ){
        return "WGS84";
    }

    // Check if NAD83
    if( datum == Datum::NAD83 ){
        return "NAD83";
    }

    // Return Unknown
    return "UNKNOWN";
}


/**
 * Convert a String to Datum.
*/
Datum StringToDatum( std::string const& datum_string ){

    // Check if WGS 84
    if( string_toLower(datum_string) == "wgs84" ){
        return Datum::WGS84;
    }
    
    // Check if NAD83
    if( string_toLower(datum_string) == "nad83" ){
        return Datum::NAD83;
    }


    // Return unknown
    return Datum::UNKNOWN;
}


/**
 * Convert a DATUM to a Well-Known Text String
*/
std::string Datum2WKT_string( Datum const& datum ){

    switch(datum){
        
        /// If we have WGS84
        case Datum::WGS84:
            return "WGS84";
        
        /// If we have NAD83
        case Datum::NAD83:
            return "NAD83";

        default:
            return "UNKNOWN";
    }
    return "UNKNOWN";
}

/** 
 * Convert a coordinate type to a string
*/
std::string CoordinateType2String( CoordinateType const& ctype ){

    switch( ctype ){

        case CoordinateType::Base:
            return "Base";
        case CoordinateType::Geographic:
            return "Geographic";
        case CoordinateType::UTM:
            return "UTM";
        default:
            throw std::runtime_error("Unknown CoordinateType");
    }
}

} /// End of Namespace GEO

