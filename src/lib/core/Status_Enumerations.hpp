/**
 * @file    Status_Enumerations.hpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#ifndef __GEOEXPLORE_LIB_CORE_STATUS_ENUMERATIONS_HPP__
#define __GEOEXPLORE_LIB_CORE_STATUS_ENUMERATIONS_HPP__

// C++ Standard Libraries
#include <cinttypes>


namespace GEO{

/**
 * @class StatusType
*/
enum class StatusType : uint8_t {
    SUCCESS = 0,
    WARNING = 1,
    FAILURE = 2,
};  // End of StatusType Enumeration


/**
 * StatusReason
*/
enum class StatusReason : uint32_t {
    NO_ERROR = 0,
};

/**
 * StatusReason
*/
enum class CoreStatusReason : uint32_t {
    UNKNOWN = 1 /*< Unknown reason. */,
    UNINITIALIZED = 2 /*< Uninitialized value.*/,
    PATH_DOES_NOT_EXIST = 3 /*< Path does not exist.*/,
    FILE_NOT_SUPPORTED  = 4 /*< Path is not valid file type.*/,
    GENERAL_IO_ERROR    = 5 /*< Problem parsing file.*/,
    NOT_IMPLEMENTED     = 6 /*< Method or object not implemented yet.*/,
}; // End of CoreStatusReason Enumeration


/**
 * @brief DEM Module Status Errors
*/
enum class DemStatusReason : uint32_t {
    NO_DEM_IO_DRIVERS = 11,
    NO_TERRAIN_COVERAGE = 12,
    NO_SRTM_PATHS = 13,
}; // End of DEMStatusReason Enumeration

/**
 * GDAL Status Reason
*/
enum class GDALStatusReason : uint32_t {
    UNKNOWN_PROJECTION_TYPE = 7 /*< Unknown OGR Coordinate Type */,
}; // End of GDALStatusReason


/**
 * @brief Image Transform Reasons
*/
enum class TransformStatusReason : uint32_t {
    INPUT_IMAGE_NULL = 8,
    OUTPUT_IMAGE_NULL = 9,
    INVALID_THREADS   = 10,
}; // End of TransformStatusReason

} // End of GEO Namespace

#endif
