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
         * Create Elevation Tile
        */
        template <typename CoordinateType,
                  typename ElevationDataType>
        typename An_Elevation_Tile<CoordinateType,ElevationDataType>::ptr_t Create_Elevation_Tile( CoordinateType const& min_corner,
                                                                                                   A_Size_i const& image_size,
                                                                                                   const double& gsd )
        {
            // Create elevation tile
            typename An_Elevation_Tile<CoordinateType,ElevationDataType>::ptr_t tile = nullptr;
            
            // Compute max corner
            CoordinateType max_corner = min_corner + CoordinateType( image_size.Width() * gsd, 
                                                                     image_size.Height() * gsd );

            // Iterate over drivers
            for( int didx=0; didx<m_drivers.size(); didx++ ){

                // Check if driver has coverage
                if( m_drivers[didx]->Coverage( min_corner, max_corner ) == true ){
                    return m_drivers[didx]->Create_Elevation_Tile(  min_corner, 
                                                                    image_size, 
                                                                    gsd );   
                }

            }

            // return tile
            return tile;

        }

        /**
         * Add DEM Driver
        */
        void Add_DEM_IO_Driver( A_DEM_IO_Driver_Base::ptr_t driver );

    private:

        /// DEM Driver
        std::vector<A_DEM_IO_Driver_Base::ptr_t> m_drivers;


}; // End of DEM_Manager Class

class The_DEM_Manager{

    public:

        /**
         * Initialize
        */
        static void Initialize();

        /**
         * Get instance of DEM_Manager
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


} // End of GEO Namespace

#endif
