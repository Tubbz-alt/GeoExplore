#ifndef __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_BASE_HPP__
#define __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_BASE_HPP__

// C++ Standard Libraries
#include <memory>


// GeoExplore Libraries
#include "../coordinate/CoordinateGeographic.hpp"
#include "../coordinate/CoordinateUTM.hpp"
#include "../core/A_Status.hpp"
#include "An_Elevation_Tile.hpp"
#include "DEM_IO_Driver_Types.hpp"


namespace GEO{
namespace DEM{

/**
 * @class A_DEM_IO_Driver_Base
*/
class A_DEM_IO_Driver_Base{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_DEM_IO_Driver_Base> ptr_t;
        
        
        /**
         * @brief Initialize the driver.
        */
        virtual Status Initialize(){
            return Status(StatusType::SUCCESS);
        }

        /**
         * @brief Check if elevation value is covered.
         *
         * @param[in] coordinate Geographic coordinate to test.
         *
         * @return True if covered, false otherwise.
        */
        virtual bool Coverage( CRD::CoordinateGeographic_d const& coordinate )const = 0;
        
        /**
         * @brief Check if elevation value is covered.
         *
         * @param[in] min_coordinate Minimum coordinate in geographic.
         * @param[in] max_coordinate Maximum coordinate in geographic.
         *
         * @return True if the bounding region is covered. False otherwise.
        */
        virtual bool Coverage( CRD::CoordinateGeographic_d const& min_coordinate,
                               CRD::CoordinateGeographic_d const& max_coordinate )const = 0;
        
        /**
         * @brief Check if elevation value is covered.
         *
         * @param[in] coordinate UTM Coordinate to check.
         *
         * @return True if covered, false otherwise.
        */
        virtual bool Coverage( CRD::CoordinateUTM_d const& coordinate )const = 0;
        
        /**
         * @brief Check if elevation range is covered.
         *
         * @param[in] min_coordinate Minimum coordinate in UTM.
         * @param[in] max_coordinate Maximum coordinate in UTM.
         *
         * @return True if covered, false otherwise.
        */
        virtual bool Coverage( CRD::CoordinateUTM_d const& min_coordinate,
                               CRD::CoordinateUTM_d const& max_coordinate )const = 0;
        

        /**
         * @brief Create Elevation Tile
         *
         * @param[in] min_corner Minimum corner of tile.
         * @param[in] tile_size Size of tile in pixels.
         * @param[in] gsd Ground sampling distance in meters-per-pixel.
         *
         * @return Elevation tile.
        */
        virtual ElevationTileUTM_d::ptr_t  Create_Elevation_Tile( CRD::CoordinateUTM_d const&  min_corner,
                                                                  A_Size<int>     const&  tile_size,
                                                                  double          const&  gsd ) = 0;
        
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
                                                                 double                 const&  gsd ) = 0;
        
        /**
         * @brief Return the DEM Driver Type.
         *
         * @return DEM_IO_Driver_Type.
        */
        virtual DEM_IO_Driver_Type Get_DEM_IO_Driver_Type()const{
            return DEM_IO_Driver_Type::BASE;
        }

}; /// End of A_DEM_IO_Driver_Base

} /// End of DEM Namespace
} /// End of GEO Namespace

#endif
