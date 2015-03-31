/**
 * @file    GDU_Render.cpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#include "GDU_Render.hpp"


/**
 * Render the terrain
*/
void Render_Terrain( GDU_Options& options )
{
    // Log Entry 
    std::cout << "Rendering Terrain Image" << std::endl; 

    // Status Variable
    Status status;

    // Get the center coordinate
    const CRD::CoordinateUTM_d center_coordinate = options.Get_Render_Center_Coordinate();

    // Get the GSD
    const double gsd = options.Get_Render_GSD();

    // Get the Image Size
    A_Size<int> image_size = options.Get_Render_Image_Size();

    // Compute the Min Corner
    CRD::CoordinateUTM_d min_corner = center_coordinate - MATH::A_Point3d( (image_size.Width()/2.0)  * gsd, 
                                                                           (image_size.Height()/2.0) * gsd,
                                                                                    0 );

    // Get an instance of the terrain manager
    DEM::DEM_Manager::ptr_t dem_manager = DEM::The_DEM_Manager::Instance_Of();

    // Generate the elevation tile
    DEM::ElevationTileUTM_d::ptr_t elevation_tile = dem_manager->Create_Elevation_Tile(  min_corner,
                                                                                         image_size,
                                                                                         gsd,
                                                                                         status );

    // make sure the operation succeeded
    if( status.Get_Status_Type() != StatusType::SUCCESS ){
        std::cerr << "error: Operation failed. Details: " << status.Get_Status_Details() << std::endl;
        std::exit(-1);
    }

}


