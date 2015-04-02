/**
 * @file    SRTM_Utilities.cpp
 * @author  Marvin Smith
 * @date    4/1/2015
*/
#include "SRTM_Utilities.hpp"

namespace GEO{
namespace DEM{
namespace SRTM{

/**
 * Convert Coordinate to SRTM Pixel Coordinate.
 */
MATH::A_Point2d Coordinate_To_SRTM_Pixel( CRD::CoordinateGeographic_d const& coordinate,
                                          MATH::A_Rectangle2d const&         extent,
                                          int const&                         rows,
                                          int const&                         cols,
                                          Status&                            status )
{

    // Check the bounds
    if( coordinate.latitude_degrees()  < extent.BL().y() ||
        coordinate.latitude_degrees()  > extent.TR().y() ||
        coordinate.longitude_degrees() < extent.BL().x() ||
        coordinate.longitude_degrees() > extent.TR().y() )
    {
        status = Status( StatusType::FAILURE, 
                         DemStatusReason::OUT_OF_BOUNDS,
                         "Out of bounds." );
        return MATH::A_Point2d(-1,-1);
    }

    // Compute the pixel size
    double pixel_size_x = extent.Width() / cols;
    double pixel_size_y = extent.Height() / rows;

    // Get the ratio
    double ratioX = (coordinate.longitude_degrees() - extent.BL().x()) / extent.Width();
    double ratioY = (extent.TL().y() - coordinate.latitude_degrees() ) / extent.Height();
    //double ratioX = (coordinate.longitude_degrees() - extent.BL().x() - (pixel_size_x / 2.0)) / extent.Width();
    //double ratioY = (extent.TL().y() - coordinate.latitude_degrees()  - (pixel_size_y / 2.0)) / extent.Height();
    
    // Compute the pixel
    MATH::A_Point2d output;
    output.x() = cols * ratioX;
    output.y() = rows * ratioY;

    // Return success
    status = Status(StatusType::SUCCESS);
    return output;
}


} // End of SRTM Namespace
} // End of DEM  Namespace
} // End of GEO  Namespace

