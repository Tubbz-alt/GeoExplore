/**
 * @file    Elevation_Tile.hpp
 * @author  Marvin Smith
 * @date    3/8/2015
*/
#ifndef __GEOEXPLORE_DEM_ELEVATION_TILE_HPP__
#define __GEOEXPLORE_DEM_ELEVATION_TILE_HPP__

// GeoExplore Libraries
#include "../core/A_Size.hpp"
#include "../math/A_Point.hpp"

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
        An_Elevation_Tile( const CoordinateType&             bottom_left_corner,
                           const double&                     gsd,
                           const A_Size<ElevationDataType>&  elevation_tile_size )
        {

        }
    

    private:

        /// Elevation Data
        ElevationDataType*  m_elevation_data;


        /// Bottom-Left Corner
        CoordinateType m_bottom_left_corner;
        
        /// GSD
        double m_gsd;


}; /// End of An_Elevation_Tile Class

// Typedef
typedef An_Elevation_Tile<CoordinateUTM<double>,double> ElevationTileUTM_d;

} /// End of GEO Namespace

#endif
