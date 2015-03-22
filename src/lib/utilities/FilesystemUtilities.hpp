/**
 * @file    FilesystemUtilities.hpp
 * @author  Marvin Smith
 * @date    5/11/2014
*/
#ifndef __GEOEXPLORE_UTILITIES_FILESYSTEMUTILITIES_HPP__
#define __GEOEXPLORE_UTILITIES_FILESYSTEMUTILITIES_HPP__

/// C++ Standard Libraries
#include <cinttypes>
#include <string>

/// Boost C++ Libraries
#include <boost/filesystem.hpp>


namespace GEO{
namespace FS{

/**
 * @class FileType
*/
enum class FileType : uint16_t {
    UNKNOWN = 0,
    JPEG = 1,
    JPEG2000 = 2,
    PNG = 3,
    NITF = 4,
    DTED = 5,
    SRTM = 6,
    TIFF = 7,
};

/**
 * Get File Type
*/
FileType Get_File_Type( const boost::filesystem::path& pathname );

} /// End of FS Namespace
} /// End of GEO Namespace

#endif

