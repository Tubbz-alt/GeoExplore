/**
 * @file    DEM_IO_Driver_Types.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include "DEM_IO_Driver_Types.hpp"

// GeoExplore Libraries
#include "../utilities/StringUtilities.hpp"

namespace GEO{
namespace DEM{

/**
 * DEM IO Driver Type to String
*/
std::string DEM_IO_Driver_Type_To_String( DEM_IO_Driver_Type const& driver_type ){

    switch( driver_type ){

        // UNKNOWN
        case DEM_IO_Driver_Type::UNKNOWN:
            return "UNKNOWN";

        // BASE
        case DEM_IO_Driver_Type::BASE:
            return "BASE";

        // FLAT
        case DEM_IO_Driver_Type::FLAT:
            return "FLAT";

        // SRTM
        case DEM_IO_Driver_Type::SRTM:
            return "SRTM";
    }

    return "UNKNOWN";

}

/**
 * STring to DEM IO Driver Type
*/
DEM_IO_Driver_Type String_To_DEM_IO_Driver_Type( std::string const& driver_type )
{

    // Get lower case version
    std::string driver_lower = string_toLower( driver_type );

    // BASE
    if( driver_lower == "base" ){ return DEM_IO_Driver_Type::BASE; }

    // FLAT
    if( driver_lower == "flat" ){ return DEM_IO_Driver_Type::FLAT; }

    // SRTM
    if( driver_lower == "srtm" ){ return DEM_IO_Driver_Type::SRTM; }

    // Otherwise, unknown
    return DEM_IO_Driver_Type::UNKNOWN;
}

} // End of DEM Namespace
} // End of GEO Namespace

