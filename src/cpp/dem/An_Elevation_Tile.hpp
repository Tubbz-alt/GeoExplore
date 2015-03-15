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
#include "A_DEM_IO_Driver_Base.hpp"


// C++ Standard Libraries
#include <memory>


namespace GEO{

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
        An_Elevation_Tile( const CoordinateType&            bottom_left_corner,
                           const double&                    gsd,
                           const A_Size<ElevationDataType>& elevation_tile_size )
            : m_elevation_data(new IMG::Image_<IMG::PixelGray_df,IMG::MemoryResource<IMG::PixelGray_df> >(elevation_tile_size, IMG::PixelGray_df(0))),
              m_bottom_left_corner(bottom_left_corner),
              m_gsd(gsd)
        {
            // Create data

        }


        /**
         * @brief Constructor
        */
        An_Elevation_Tile( const CoordinateType&             bottom_left_corner,
                           const double&                     gsd,
                           const A_Size<ElevationDataType>&  elevation_tile_size,
                           const ElevationDataType&          default_elevation_value )
            : m_elevation_data(new IMG::Image_<IMG::PixelGray_df,IMG::MemoryResource<IMG::PixelGray_df>>( elevation_tile_size,        
                                                                                                         IMG::PixelGray_df(default_elevation_value))),
              m_bottom_left_corner(bottom_left_corner),
              m_gsd(gsd)
        {

        }
    

    private:

        /// Elevation Data
        IMG::Image_<IMG::PixelGray_df,IMG::MemoryResource<IMG::PixelGray_df>> m_elevation_data; 
        
        /// GSD
        double m_gsd;

        /// Bottom-Left Corner
        CoordinateType m_bottom_left_corner;

}; /// End of An_Elevation_Tile Class

// Typedef
typedef An_Elevation_Tile<CoordinateUTM<double>,double> ElevationTileUTM_d;

} /// End of GEO Namespace

#endif
