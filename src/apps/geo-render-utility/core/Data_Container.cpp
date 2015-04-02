/**
 * @brief  Data_Container.cpp
 * @author Marvin Smith
 * @date   3/27/2015
*/
#include "Data_Container.hpp"

// C++ Standard Libraries
#include <cstdlib>

// GeoExplore Libraries
#include <coordinate/CoordinateUTM.hpp>
#include <image/transforms/ImageTransformColorMap.hpp>
#include <io/opencv_utils/OpenCV_Utilities.hpp>


/******************************************/
/*              Constructor               */
/******************************************/
Data_Container::Data_Container()
  : m_class_name("Data_Container"),
    m_dem_manager(nullptr)
{

}


/******************************************/
/*             Load the data              */
/******************************************/
void Data_Container::Load_Data( const Configuration_Options& options )
{
    // Status
    Status status;

    // Initialize Terrain Manager
    m_dem_manager = DEM::DEM_Manager::ptr_t(new GEO::DEM::DEM_Manager());

    // Get the driver list
    std::vector<DEM::A_DEM_IO_Driver_Base::ptr_t> dem_driver_list = options.Get_DEM_Driver_List();
    
    // Add the drivers to the dem manager
    m_dem_manager->Add_DEM_IO_Drivers( dem_driver_list );

    // Check status
    if( m_dem_manager->Get_Number_Of_DEM_IO_Drivers() <= 0 ){
        std::cerr << "error: No DEM IO Drivers registered." << std::endl;
        std::exit(-1);
    }
    
    // Set image size
    A_Size<int> image_size(1000,1000);

    // Get the center coordinate
    CRD::CoordinateUTM_d center_coordinate = options.Get_Render_Center_Coordinate();

    // Get the GSD
    double gsd = options.Get_Render_GSD();

    // Subtract the offset to get the min corner
    MATH::A_Point3d offset( image_size.Width()  * gsd, 
                            image_size.Height() * gsd );

    
    CRD::CoordinateUTM_d min_coordinate = center_coordinate - offset;


    // Generate the image list
    IMG::Image<IMG::PixelRGBA_u8>::ptr_t temp_image(new IMG::Image<IMG::PixelRGBA_u8>(image_size));

    // Create a terrain tile
    DEM::ElevationTileUTM_d::ptr_t elevation_tile = m_dem_manager->Create_Elevation_Tile( min_coordinate,
                                                                                          image_size,
                                                                                          gsd,
                                                                                          status );

    // Check the status
    if( status.Get_Status_Type() != StatusType::SUCCESS ){
        std::cerr << "error: Problem creating tile: Details: " << status << std::endl;
        std::exit(-1);
    }

    // Build the color map
    IMG::A_Color_Map<IMG::PixelGray_df,IMG::PixelRGBA_u8> color_map;
    color_map.Add_Color_Pair( IMG::PixelGray_df(4350), IMG::PixelRGBA_u8(255, 0, 0));
    color_map.Add_Color_Pair( IMG::PixelGray_df(4400), IMG::PixelRGBA_u8(0, 255, 0));
    color_map.Add_Color_Pair( IMG::PixelGray_df(4412), IMG::PixelRGBA_u8(0, 0, 255));

    // Create a Color Mapper
    IMG::Image<IMG::PixelGray_df>::ptr_t elevation_image = elevation_tile->Get_Image_Ptr();
    status = IMG::Compute_Color_Map<IMG::PixelGray_df,IMG::PixelRGBA_u8>( elevation_image,
                                                                          temp_image,
                                                                          color_map,
                                                                          options.Get_Max_Threads() );

    m_image_list.push_back(temp_image);
}


