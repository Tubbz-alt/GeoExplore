#ifndef __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_FLAT_HPP__
#define __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_FLAT_HPP__

// C++ Standard Libraries
#include <memory>

// GeoExplore Libraries
#include "../coordinate/CoordinateGeographic.hpp"
#include "../coordinate/CoordinateUTM.hpp"

/**
 * @class A_DEM_IO_Driver_Flat
*/
class A_DEM_IO_Driver_Flat : public A_DEM_IO_Driver_Base{


    public:

        /// Pointer Type
        typedef std::shared_ptr<A_DEM_IO_Driver_Flat> ptr_t;

        
        /**
         * @brief Constructor given fixed elevation
         *
         * @param[in] elevation_meters Constant elevation in meters to return.
         */
         A_DEM_IO_Driver_Flat( const double& elevation_meters );
         
        /**
         * Check if elevation value is covered
        */
        virtual bool Coverage( CoordinateGeographic_d const& coordinate )const{
            return true;
        }
        
        /**
         * Check if elevation value is covered
        */
        virtual bool Coverage( CoordinateUTM_d const& coordinate )const{
            return true;
        }

        
        /**
         * Create Elevation Tile
        */
        template <typename CoordinateType,
                  typename ElevationDataType>
        typename An_Elevation_Tile<CoordinateType,ElevationDataType>::ptr_t Create_Elevation_Tile( CoordinateType const& min_corner,
                                                                                                   A_Size_i const& image_size,
                                                                                                   const double& gsd )
        {
            // Create tile
            typename An_Elevation_Tile<CoordinateType,ElevationDataType>::ptr_t  elevation_tile(new An_Elevation_Tile<CoordinateType,ElevationDataType>( min_corner, 
                                                                                                                                                         image_size, 
                                                                                                                                                         gsd,
                                                                                                                                                         m_elevation_meters ));
            
            // return the tile
            return elevation_tile;
        }


    private:
        
        /// Elevation in meters
        double m_elevation_meters;


}; /// End of A_DEM_IO_Driver_Flat


#endif
