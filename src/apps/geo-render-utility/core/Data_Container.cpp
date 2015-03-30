/**
 * @brief  Data_Container.cpp
 * @author Marvin Smith
 * @date   3/27/2015
*/
#include "Data_Container.hpp"

// C++ Standard Libraries
#include <cstdlib>


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
    // Initialize Terrain Manager
    m_dem_manager = GEO::DEM::DEM_Manager::ptr_t(new GEO::DEM::DEM_Manager());

    // Get the driver list
    std::vector<GEO::DEM::A_DEM_IO_Driver_Base::ptr_t> dem_driver_list = options.Get_DEM_Driver_List();
    
    // Add the drivers to the dem manager
    m_dem_manager->Add_DEM_IO_Drivers( dem_driver_list );

    // Check status
    if( m_dem_manager->Get_Number_Of_DEM_IO_Drivers() <= 0 ){
        std::cerr << "error: No DEM IO Drivers registered." << std::endl;
        std::exit(-1);
    }



}

