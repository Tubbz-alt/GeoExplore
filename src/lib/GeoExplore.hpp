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
#include "core/A_Size.hpp"
#include "core/Enumerations.hpp"

/// Coordinate Module
#include "coordinate/CoordinateBase.hpp"
#include "coordinate/CoordinateConversion.hpp"
#include "coordinate/CoordinateGeographic.hpp"
#include "coordinate/CoordinateUTM.hpp"

/// Dem Module
#include "dem/A_DEM_IO_Driver_Base.hpp"
#include "dem/A_DEM_IO_Driver_Flat.hpp"
#include "dem/A_DEM_IO_Driver_SRTM.hpp"
#include "dem/An_Elevation_Tile.hpp"
#include "dem/DEM_Manager.hpp"

/// Image Module
#include "image/BaseResource.hpp"
#include "image/ChannelType.hpp"
#include "image/Image.hpp"
#include "image/DiskResource.hpp"
#include "image/MemoryResource.hpp"
#include "image/MetadataContainer.hpp"
#include "image/MetadataContainerBase.hpp"
#include "image/PixelBase.hpp"
#include "image/PixelCast.hpp"
#include "image/PixelGray.hpp"
#include "image/PixelRGB.hpp"

/// IO Module
#include "io/GDAL_Driver.hpp"
#include "io/ImageDriverBase.hpp"
#include "io/ImageIO.hpp"
#include "io/NETPBM_Driver.hpp"
#include "io/OpenCV_Driver.hpp"

/// Math Module
#include "math/A_Rectangle.hpp"
#include "math/A_Point.hpp"
#include "math/A_Polygon.hpp"

/// Utility Module
#include "utilities/FilesystemUtilities.hpp"
#include "utilities/StringUtilities.hpp"


#endif
