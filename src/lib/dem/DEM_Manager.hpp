#ifndef __SRC_CPP_DEM_DEM_MANAGER_HPP__
#define __SRC_CPP_DEM_DEM_MANAGER_HPP__


/// C++ Standard Libraries
#include <memory>
#include <vector>


/// GeoExplore Libraries
#include "../coordinate/CoordinateUTM.hpp"
#include "An_Elevation_Tile.hpp"
#include "A_DEM_IO_Driver_Base.hpp"

namespace GEO{
namespace DEM{

/**
 * @class DEM_Manager
*/
class DEM_Manager{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<DEM_Manager> ptr_t;

        /**
         * Constructor
        */
        DEM_Manager();
        

        /**
         * @brief Create Elevation Tile
         *
         * @param[in] min_corner Minimum corner in the tile.
         * @param[in] image_size Size of the tile in pixels.
         * @param[in] gsd Ground-Sampling-Distance in meters-per-pixels.
         * @param[out] status Status of the operation.
         *
         * @return Elevation tile
        */
        template <typename CoordinateType>
        ElevationTileUTM_d::ptr_t Create_Elevation_Tile( CoordinateType const&  min_corner,
                                                         A_Size<int>    const&  image_size,
                                                         double         const&  gsd,
                                                         Status&                status )
        {
            // Create elevation tile
            ElevationTileUTM_d::ptr_t tile = nullptr;
            
            // Create temp coordinate
            CoordinateType sum_coordinate = min_corner;
            sum_coordinate.x() = image_size.Width()  * gsd;
            sum_coordinate.y() = image_size.Height() * gsd;
            
            // Compute max corner
            CoordinateType max_corner = min_corner + sum_coordinate;

            // Iterate over drivers
            for( int didx=0; didx<m_drivers.size(); didx++ ){

                // Check if driver has coverage
                if( m_drivers[didx]->Coverage( min_corner, max_corner ) == true ){
                    return m_drivers[didx]->Create_Elevation_Tile(  min_corner, 
                                                                    image_size, 
                                                                    gsd,
                                                                    status );   
                }

            }

            // Return success
            status = Status( StatusType::FAILURE, DemStatusReason::NO_TERRAIN_COVERAGE, "No terrain coverage.");

            // return tile
            return tile;

        }

        /**
         * @brief Add DEM IO Driver to DEM Manager.
         *
         * @param[in] driver Driver to add.
        */
        void Add_DEM_IO_Driver( A_DEM_IO_Driver_Base::ptr_t driver );

        
        /**
         * @brief Add DEM IO Driver List to DEM Manager.
         *
         * @param[in] driver_list Driver list to add.
        */
        void Add_DEM_IO_Drivers( std::vector<A_DEM_IO_Driver_Base::ptr_t> const& driver_list );
    

        /**
         * @brief Get the number of DEM IO Drivers
         * 
         * @return Number of DEM IO Drivers registered.
        */
        inline int Get_Number_Of_DEM_IO_Drivers()const{
            return m_drivers.size();
        }


        /**
         * @brief Get the list of dem drivers
         * 
         * @return DEM driver list
        */
        inline std::vector<A_DEM_IO_Driver_Base::ptr_t> Get_DEM_IO_Drivers()const{
            return m_drivers;
        }
        
    private:

        /// DEM Driver
        std::vector<A_DEM_IO_Driver_Base::ptr_t> m_drivers;


}; // End of DEM_Manager Class


/**
 * @class The_DEM_Manager
 *
 * @brief Singleton instance of the DEM_Manager.
*/
class The_DEM_Manager{

    public:

        /**
         * @brief Initialize the DEM Singleton Instance
        */
        static void Initialize();

        /**
         * @brief Get instance of DEM_Manager.
         *
         * @return Instance of the DEM_Manager.
        */
        static DEM_Manager::ptr_t Instance_Of();

    private:
        
        /**
         * Constructor
        */
        The_DEM_Manager();

        /**
         * Copy Constructor
        */
        The_DEM_Manager( The_DEM_Manager const& rhs );

        /**
         * Assignment Operator
        */
        void operator = ( The_DEM_Manager const& rhs )const;


}; /// End of The_DEM_Manager Instance


} // End of DEM Namespace
} // End of GEO Namespace

#endif
