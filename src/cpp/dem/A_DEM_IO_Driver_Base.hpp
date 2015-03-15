#ifndef __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_BASE_HPP__
#define __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_BASE_HPP__

// C++ Standard Libraries
#include <memory>


// GeoExplore Libraries
#include "../coordinate/CoordinateGeographic.hpp"
#include "../coordinate/CoordinateUTM.hpp"

namespace GEO{

/**
 * @class A_DEM_IO_Driver_Base
*/
class A_DEM_IO_Driver_Base{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_DEM_IO_Driver_Base> ptr_t;
        

        /**
         * Check if elevation value is covered
        */
        virtual bool Coverage( CoordinateGeographic_d const& coordinate )const = 0;
        
        /**
         * Check if elevation value is covered
        */
        virtual bool Coverage( CoordinateUTM_d const& coordinate )const = 0;


}; /// End of A_DEM_IO_Driver_Base

} // End of GEO Namespace

#endif
