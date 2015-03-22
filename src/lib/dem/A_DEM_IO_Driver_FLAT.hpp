#ifndef __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_FLAT_HPP__
#define __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_FLAT_HPP__

// C++ Standard Libraries
#include <memory>

// GeoExplore Libraries
#include "../coordinate/CoordinateConversion.hpp"
#include "../coordinate/CoordinateGeographic.hpp"
#include "../coordinate/CoordinateUTM.hpp"
#include "A_DEM_IO_Driver_Base.hpp"

namespace GEO{
namespace DEM{


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
        inline virtual bool Coverage( CRD::CoordinateGeographic_d const& coordinate )const{
            return true;
        }
        
        
        /**
         * Check if elevation value is covered
        */
        inline virtual bool Coverage( CRD::CoordinateGeographic_d const& coordinate_min,
                                     CRD::CoordinateGeographic_d const& coordinate_max )const
        {
            return true;
        }

        /**
         * Check if elevation value is covered
        */
        virtual bool Coverage( CRD::CoordinateUTM_d const& coordinate )const{
            return true;
        }
        
        /**
         * Check if elevation value is covered
        */
        virtual bool Coverage( CRD::CoordinateUTM_d const& coordinate_min,
                               CRD::CoordinateUTM_d const& coordinate_max )const
        {
            return true;
        }


        
        /**
         * @brief Create Elevation Tile
         *
         * @param[in] min_corner Minimum corner of tile.
         * @param[in] tile_size Size of tile in pixels.
         * @param[in] gsd Ground sampling distance in meters-per-pixel.
         *
         * @return Elevation tile.
        */
        virtual ElevationTileUTM_d::ptr_t Create_Elevation_Tile( CRD::CoordinateUTM_d const&  min_corner,
                                                                 A_Size<int>     const&  tile_size,
                                                                 double          const&  gsd );
        
        /**
         * @brief Create Elevation Tile
         *
         * @param[in] min_corner Minimum corner of tile.
         * @param[in] tile_size Size of tile in pixels.
         * @param[in] gsd Ground sampling distance in meters-per-pixel.
         *
         * @return Elevation tile.
        */
        virtual ElevationTileUTM_d::ptr_t Create_Elevation_Tile( CRD::CoordinateGeographic_d const&  min_corner,
                                                                 A_Size<int>            const&  tile_size,
                                                                 double                 const&  gsd );

        
        /**
         * @brief Return the DEM Driver Type.
         *
         * @return DEM_IO_Driver_Type.
        */
        inline virtual DEM_IO_Driver_Type Get_DEM_IO_Driver_Type()const{
            return DEM_IO_Driver_Type::FLAT;
        }


    private:
        
        /// Elevation in meters
        double m_elevation_meters;


}; /// End of A_DEM_IO_Driver_Flat


} /// End of DEM Namespace
} /// End of GEO Namespace

#endif
