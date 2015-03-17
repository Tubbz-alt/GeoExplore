/**
 * @file A_DEM_IO_Driver_Flat.cpp
 * @author Marvin Smith
 * @date 3/14/2015
*/
#include "A_DEM_IO_Driver_FLAT.hpp"

namespace GEO{
namespace DEM{

/**
 * Constructor
*/
A_DEM_IO_Driver_Flat::A_DEM_IO_Driver_Flat( const double& elevation_meters )
  : m_elevation_meters(elevation_meters)
{


}


/**
 * Create Elevation Tile
*/
typename ElevationTileUTM_d::ptr_t A_DEM_IO_Driver_Flat::Create_Elevation_Tile( CRD::CoordinateUTM_d const&  min_corner_utm,
                                                                                A_Size<int>     const&  image_size,
                                                                                double          const&  gsd )
{
    
    // Create tile
    ElevationTileUTM_d::ptr_t  elevation_tile(new ElevationTileUTM_d( min_corner_utm, 
                                                                      image_size, 
                                                                      gsd,
                                                                      m_elevation_meters ));

    // return the tile    
    return elevation_tile;
    
}


/**
 * Create Elevation Tile
*/
ElevationTileUTM_d::ptr_t A_DEM_IO_Driver_Flat::Create_Elevation_Tile( CRD::CoordinateGeographic_d const&  min_corner_geographic,
                                                                       A_Size<int>            const&  image_size,
                                                                       double                 const&  gsd )
{

    // Convert to UTM
    CRD::CoordinateUTM_d min_corner_utm = CRD::convert_coordinate( min_corner_geographic );

    // Create tile
    ElevationTileUTM_d::ptr_t  elevation_tile(new ElevationTileUTM_d( min_corner_utm, 
                                                                      image_size, 
                                                                      gsd,
                                                                      m_elevation_meters ));

    // return the tile    
    return elevation_tile;
    
}


} /// End of DEM Namespace
} /// End of GEO Namespace
