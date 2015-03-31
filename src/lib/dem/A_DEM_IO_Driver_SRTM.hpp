#ifndef __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_SRTM_HPP__
#define __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_SRTM_HPP__

// C++ Standard Libraries
#include <memory>

// GeoExplore Libraries
#include "../coordinate/CoordinateGeographic.hpp"
#include "../coordinate/CoordinateUTM.hpp"
#include "../core/A_Status.hpp"
#include "../filesystem.hpp"
#include "../image/MemoryResource.hpp"
#include "../io/GDAL_Driver.hpp"
#include "../math/A_Rectangle.hpp"
#include "A_DEM_IO_Driver_Base.hpp"

namespace GEO{
namespace DEM{

/**
 * @class A_DEM_IO_Driver_SRTM
*/
class A_DEM_IO_Driver_SRTM : public A_DEM_IO_Driver_Base{

    public:
        
        /// Resource Type
        typedef IMG::MemoryResource<IMG::PixelGray_df> resource_type;


        /// Driver Type
        typedef IO::GDAL::ImageDriverGDAL<resource_type> io_driver_type;


        /**
         * @brief Construct the DEM IO Driver with a path to SRTM data.
         *
         * @param[in] srtm_path Path to SRTM data.  
         */
        A_DEM_IO_Driver_SRTM( FS::FilesystemPath const& pathname );


        /**
         * @brief Construct the DEM IO Driver with a list of paths to SRTM data.
         *
         * @param[in] srtm_paths List of SRTM File paths or directories.
        */
        A_DEM_IO_Driver_SRTM( std::vector<FS::FilesystemPath> const& pathname );


        /**
         * @brief Initialize driver.
         *
         * @return Status of the operation.
         */
        virtual Status Initialize();


        /**
         * @brief Check if driver is initialized.
         *
         * @param[out] status Status of the operation.
         *
         * @return True if initialized. False otherwise.
        */
        virtual bool Is_Initialized( Status& status )const;

        
        /**
         * @brief Check if elevation value is covered.
         *
         * @param[in] coordinate Geographic coordinate to test.
         * 
         * @return True if covered. False otherwise.
        */
        inline virtual bool Coverage( CRD::CoordinateGeographic_d const& coordinate )const{
            return false;
        }
        
                
        /**
         * @brief Check if elevation value is covered
         *
         * @param[in] coordinate Coordinate to test.
         * 
         * @return True if covered. False otherwise.
        */
        inline virtual bool Coverage( CRD::CoordinateUTM_d const& coordinate )const
        {
            return false;
        }
        
        
        /**
         * @brief Check if region is covered.
         *
         * @param[min] min_coordinate Minimum coordinate.
         * @param[min] max_coordinate Maximum coordinate.
         *
         * @return True if covered. False otherwise.
        */
        inline virtual bool Coverage( CRD::CoordinateGeographic_d const& min_coordinate,
                                      CRD::CoordinateGeographic_d const& max_coordinate )const;


        /**
         * @brief Check if elevation range is covered
         *
         * @param[in] min_coordinate Coordinate to test.
         * @param[in] max_coordinate Coordinate to test.
         * 
         * @return True if covered. False otherwise.
        */
        inline virtual bool Coverage( CRD::CoordinateUTM_d const& min_coordinate,
                                      CRD::CoordinateUTM_d const& max_coordinate )const
        {
            return false;
        }

        
        /**
         * @brief Query elevation in meters.
         *
         * @param[in] coordinate Coordinate to query.
         * @param[in] status Status of the operation.
         *
         * @return Elevation in meters.
        */
        virtual double  Query_Elevation_Meters( CRD::CoordinateGeographic_d const& coordinate,
                                                Status& status ) const;


        /**
         * @brief Query elevation in meters.
         *
         * @param[in] coordinate Coordinate to query.
         * @param[in] status Status of the operation.
         *
         * @return Elevation in meters.
        */
        virtual double  Query_Elevation_Meters( CRD::CoordinateUTM_d const& coordinate,
                                                Status& status ) const;

        
        /**
         * @brief Return the DEM Driver Type.
         *
         * @return DEM_IO_Driver_Type.
        */
        inline virtual DEM_IO_Driver_Type Get_DEM_IO_Driver_Type()const
        {
            return DEM_IO_Driver_Type::SRTM;
        }
        
        /**
         * @brief Create Elevation Tile
         *
         * @param[in] min_corner Minimum corner of tile.
         * @param[in] tile_size Size of tile in pixels.
         * @param[in] gsd Ground sampling distance in meters-per-pixel.
         * @param[out] status Status of the operation.
         *
         * @return Elevation tile.
        */
        virtual ElevationTileUTM_d::ptr_t  Create_Elevation_Tile( CRD::CoordinateUTM_d const&  min_corner,
                                                                  A_Size<int>          const&  tile_size,
                                                                  double               const&  gsd,
                                                                  Status&                      status );
        
        /**
         * @brief Create Elevation Tile
         *
         * @param[in] min_corner Minimum corner of tile.
         * @param[in] tile_size Size of tile in pixels.
         * @param[in] gsd Ground sampling distance in meters-per-pixel.
         * @param[out] status Status of the operation.
         *
         * @return Elevation tile.
        */
        virtual ElevationTileUTM_d::ptr_t Create_Elevation_Tile( CRD::CoordinateGeographic_d const&  min_corner,
                                                                 A_Size<int>                 const&  tile_size,
                                                                 double                      const&  gsd,
                                                                 Status&                             status );

    
    private:

        /// Class Name
        std::string m_class_name;

        
        /// Initialization Status
        Status m_initialization_status;


        /// path to srtm data
        std::vector<FS::FilesystemPath> m_srtm_pathnames;

        
        /// List of SRTM Files
        std::vector<FS::FilesystemPath> m_srtm_file_list;

        
        /// List of SRTM Extents
        std::vector<MATH::A_Rectangle2d> m_srtm_file_extents;

}; // End of A_DEM_IO_Driver_SRTM

} // End of DEM Namespace
} // End of GEO Namespace

#endif
