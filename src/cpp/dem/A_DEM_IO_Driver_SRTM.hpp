#ifndef __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_SRTM_HPP__
#define __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_SRTM_HPP__

// C++ Standard Libraries
#include <memory>

/**
 * @class A_DEM_IO_Driver_SRTM
*/
class A_DEM_IO_Driver_SRTM : public A_DEM_IO_Driver_Base{

    public:
        
        
        /**
         * Check if elevation value is covered
        */
        virtual bool Coverage( CoordinateGeographic_d const& coordinate )const{
            return false;
        }
        
        /**
         * Check if elevation value is covered
        */
        virtual bool Coverage( CoordinateUTM_d const& coordinate )const{
            return false;
        }



}; /// End of A_DEM_IO_Driver_SRTM


#endif
