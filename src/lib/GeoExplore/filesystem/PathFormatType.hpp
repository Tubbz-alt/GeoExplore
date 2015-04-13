/**
 * @file    PathFormatType.hpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#ifndef __GEOEXPLORE_LIB_FILESYSTEM_PATHFORMATTYPE_HPP__
#define __GEOEXPLORE_LIB_FILESYSTEM_PATHFORMATTYPE_HPP__

// C++ Standard Libraries
#include <cinttypes>

namespace GEO{
namespace FS{

/**
 * @brief Path format enumeration.
*/
enum class PathFormatType : uint8_t{
    RELATIVE = 0,
    ABSOLUTE = 1,
}; // End of PathFormatType Enumeration.


} // End of FS  Namespace
} // End of GEO Namespace

#endif
