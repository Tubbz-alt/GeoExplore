/**
 * @file    Elevation_Tile.hpp
 * @author  Marvin Smith
 * @date    3/8/2015
*/
#ifndef __GEOEXPLORE_DEM_ELEVATION_TILE_HPP__
#define __GEOEXPLORE_DEM_ELEVATION_TILE_HPP__

// GeoExplore Libraries
#include "../core/A_Size.hpp"
#include "../image/ChannelType.hpp"
#include "../image/Image.hpp"
#include "../image/MemoryResource.hpp"
#include "../image/PixelGray.hpp"
#include "../math/A_Point.hpp"


// C++ Standard Libraries
#include <memory>


namespace GEO{
namespace DEM{

/**
 * @class DEM
*/
template <typename CoordinateType,
          typename ElevationDataType>
class An_Elevation_Tile {

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<An_Elevation_Tile> ptr_t;

        
        /**
         * @brief Constructor
        */
        An_Elevation_Tile( const CoordinateType&    bottom_left_corner,
                           const A_Size<int>&       elevation_tile_size,
                           const double&            gsd )
            : m_elevation_data(new IMG::Image_<IMG::PixelGray_df,IMG::MemoryResource<IMG::PixelGray_df> >(elevation_tile_size, IMG::PixelGray_df(0))),
              m_bottom_left_corner(bottom_left_corner),
              m_gsd(gsd)
        {
            // Create data

        }


        /**
         * @brief Constructor given default elevation value.
         *
         * @param[in] bottom_left_corner Bottom left corner.
         * @param[in] gsd Ground sampling distance in meters-per-pixel.
         * @param[in] elevation_tile_size Size of elevation tile in pixels.
         * @param[in] default_elevation_value_meters Elevation in meters.
        */
        An_Elevation_Tile( const CoordinateType&       bottom_left_corner,
                           const A_Size<int>&          elevation_tile_size,
                           const double&               gsd,
                           const ElevationDataType&    default_elevation_value_meters )
            : m_elevation_data(new IMG::Image_<IMG::PixelGray_df,IMG::MemoryResource<IMG::PixelGray_df>>( elevation_tile_size,        
                                                                                                         IMG::PixelGray_df(default_elevation_value_meters))),
              m_bottom_left_corner(bottom_left_corner),
              m_gsd(gsd)
        {

        }
    

    private:

        /// Elevation Data
        IMG::Image_<IMG::PixelGray_df,IMG::MemoryResource<IMG::PixelGray_df>>::ptr_t m_elevation_data; 
        
        /// GSD
        double m_gsd;

        /// Bottom-Left Corner
        CoordinateType m_bottom_left_corner;

}; /// End of An_Elevation_Tile Class

// Typedef
typedef An_Elevation_Tile<CRD::CoordinateUTM<double>,double> ElevationTileUTM_d;


} /// End of DEM Namespace
} /// End of GEO Namespace

#endif
