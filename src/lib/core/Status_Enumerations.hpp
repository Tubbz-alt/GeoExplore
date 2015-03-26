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
}; // End of CoreStatusReason Enumeration

/**
 * GDAL Status Reason
*/
enum class GDALStatusReason : uint32_t {
    UNKNOWN_PROJECTION_TYPE = 6 /*< Unknown OGR Coordinate Type */,
}; // End of GDALStatusReason

} // End of GEO Namespace

#endif
