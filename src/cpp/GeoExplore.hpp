/**
 * @file    GeoExplore.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 *
 * Lead header file for main library.
 */
#ifndef __GEOEXPLORE_HPP__
#define __GEOEXPLORE_HPP__

/// Core Module
#include <GeoExplore/core/Enumerations.hpp>

/// Coordinate Module
#include <GeoExplore/coordinate/CoordinateBase.hpp>
#include <GeoExplore/coordinate/CoordinateConversion.hpp>
#include <GeoExplore/coordinate/CoordinateGeodetic.hpp>
#include <GeoExplore/coordinate/CoordinateUTM.hpp>

/// Image Module
#include <GeoExplore/image/BaseResource.hpp>
#include <GeoExplore/image/ChannelType.hpp>
#include <GeoExplore/image/Image.hpp>
#include <GeoExplore/image/MemoryResource.hpp>
#include <GeoExplore/image/MetadataContainer.hpp>
#include <GeoExplore/image/MetadataContainerBase.hpp>
#include <GeoExplore/image/PixelBase.hpp>
#include <GeoExplore/image/PixelCast.hpp>
#include <GeoExplore/image/PixelGray.hpp>
#include <GeoExplore/image/PixelRGB.hpp>

/// IO Module
#include <GeoExplore/io/GDAL_Driver.hpp>
#include <GeoExplore/io/ImageDriverBase.hpp>
#include <GeoExplore/io/ImageIO.hpp>
#include <GeoExplore/io/NETPBM_Driver.hpp>
#include <GeoExplore/io/OpenCV_Driver.hpp>

/// Utility Module
#include <GeoExplore/utilities/FilesystemUtilities.hpp>
#include <GeoExplore/utilities/StringUtilities.hpp>

namespace GEO{
namespace IMG{

/// Common Image Aliases
template <typename PixelType> using Image     = GEO::IMG::Image_<PixelType,GEO::IMG::MemoryResource<PixelType> >;
template <typename PixelType> using DiskImage = GEO::IMG::Image_<PixelType,GEO::IMG::DiskResource<PixelType> >;

} // End of IMG Namespace
} // End of GEO Namespace

#endif
