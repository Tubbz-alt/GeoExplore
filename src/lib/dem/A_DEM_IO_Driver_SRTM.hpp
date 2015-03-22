#ifndef __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_SRTM_HPP__
#define __GEOEXPLORE_SRC_DEM_A_DEM_IO_DRIVER_SRTM_HPP__

// C++ Standard Libraries
#include <memory>

// GeoExplore Libraries
#include "../coordinate/CoordinateGeographic.hpp"
#include "../coordinate/CoordinateUTM.hpp"
#include "A_DEM_IO_Driver_Base.hpp"

namespace GEO{
namespace DEM{

/**
 * @class A_DEM_IO_Driver_SRTM
*/
class A_DEM_IO_Driver_SRTM : public A_DEM_IO_Driver_Base{

    public:
        
        
        /**
         * Check if elevation value is covered
        */
        virtual bool Coverage( CRD::CoordinateGeographic_d const& coordinate )const{
            return false;
        }
        
        /**
         * Check if elevation value is covered
        */
        virtual bool Coverage( CRD::CoordinateUTM_d const& coordinate )const{
            return false;
        }

        
        /**
         * @brief Return the DEM Driver Type.
         *
         * @return DEM_IO_Driver_Type.
        */
        inline virtual DEM_IO_Driver_Type Get_DEM_IO_Driver_Type()const{
            return DEM_IO_Driver_Type::SRTM;
        }


}; // End of A_DEM_IO_Driver_SRTM

} // End of DEM Namespace
} // End of GEO Namespace

#endif
