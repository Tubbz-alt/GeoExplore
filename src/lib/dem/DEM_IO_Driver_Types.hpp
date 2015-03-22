/**
 * @file    DEM_IO_Driver_Types.hpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#ifndef __GEOEXPLORE_LIB_DEM_DEM_IO_DRIVER_TYPES_HPP__
#define __GEOEXPLORE_LIB_DEM_DEM_IO_DRIVER_TYPES_HPP__

// C++ Standard Libraries
#include <cinttypes>
#include <string>

namespace GEO{
namespace DEM{

/**
 * @enum DEM_IO_Driver_Type
*/
enum class  DEM_IO_Driver_Type : uint16_t{
    UNKNOWN = 0,
    BASE = 1,
    FLAT = 2,
    SRTM = 3,
}; 



/**
 * @brief DEM_IO_Driver_Type to string.
 *
 * @param[in] driver_type DEM_IO_Driver_Type enum to evaluate.
 *
 * @return DEM_IO_Driver_Type string representation.
*/
std::string DEM_IO_Driver_Type_To_String( DEM_IO_Driver_Type const& driver_type );

/**
 * @brief String to DEM_IO_Driver_Type.
 *
 * @param[in] driver_type Driver type string to evaluate.
 *
 * @return DEM_IO_Driver_Type representation.
*/
DEM_IO_Driver_Type String_To_DEM_IO_Driver_Type( std::string const& driver_type );


} // End of DEM Namespace
} // End of GEO Namespace

#endif
