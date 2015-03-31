/**
 * @file    A_DEM_IO_Driver_SRTM.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include "A_DEM_IO_Driver_SRTM.hpp"

// GeoExplore Libraries
#include "../../lib/utilities/FilesystemUtilities.hpp"


namespace GEO{
namespace DEM{


/*************************************************************/
/*                      Constructor                          */
/*************************************************************/
A_DEM_IO_Driver_SRTM::A_DEM_IO_Driver_SRTM( boost::filesystem::path const& pathname )
  : m_class_name("A_DEM_IO_Driver"),
    m_initialization_status(Status(StatusType::FAILURE,CoreStatusReason::UNINITIALIZED, "Uninitialized.")),
    m_srtm_pathname( pathname )
{
}


/*************************************************************/
/*                  Check if Initialized                     */
/*************************************************************/
bool A_DEM_IO_Driver_SRTM::Is_Initialized( Status& status )const
{
    // Set the status
    status = m_initialization_status;

    // Check status
    if( m_initialization_status.Get_Status_Type() != StatusType::SUCCESS ){
        return false;
    }
    return true;
}


/*************************************************************/
/*                         Initialize                        */
/*************************************************************/
Status A_DEM_IO_Driver_SRTM::Initialize(){
    
    // Make sure the path exists
    if( boost::filesystem::exists(m_srtm_pathname) == false ){
        m_initialization_status = Status( StatusType::FAILURE, 
                                          CoreStatusReason::PATH_DOES_NOT_EXIST,
                                          "SRTM path does not exist.");
        return m_initialization_status;
    }

    
    // If the path is a file, then check if SRTM
    if( boost::filesystem::is_regular_file(m_srtm_pathname) == true &&
        FS::Get_File_Type(m_srtm_pathname) == FS::FileType::SRTM )
    {
        m_srtm_file_list.push_back(m_srtm_pathname);
    }


    // If the path is a directory, search for files
    else if( boost::filesystem::is_directory(m_srtm_pathname) == true ){
        
        // Get list of files
        boost::filesystem::recursive_directory_iterator it(m_srtm_pathname);
        for( ; it != boost::filesystem::recursive_directory_iterator(); it++ ){
            
            // Get path
            boost::filesystem::path temp_path = it->path();

            // Check if srtm
            if( FS::Get_File_Type(temp_path) == FS::FileType::SRTM ){

                // Get the extent of the file

                // Add the path to the list
                m_srtm_file_list.push_back(temp_path);
            }
        }
    }
    else{
        m_initialization_status = Status( StatusType::FAILURE, 
                                          CoreStatusReason::PATH_DOES_NOT_EXIST,
                                          "SRTM path does not exist.");
        return m_initialization_status;
    }


    // Make sure we have some files
    if( m_srtm_file_list.size() <= 0 ){
        m_initialization_status = Status( StatusType::FAILURE, 
                                          CoreStatusReason::PATH_DOES_NOT_EXIST,
                                          "Directory contains no SRTM files.");
        return m_initialization_status;
    }

    
    // Return success
    m_initialization_status = Status( StatusType::SUCCESS );
    return m_initialization_status;

}


/*************************************************************/
/*                   Create Elevation Tile                   */
/*************************************************************/
ElevationTileUTM_d::ptr_t  A_DEM_IO_Driver_SRTM::Create_Elevation_Tile( CRD::CoordinateUTM_d const&  min_corner,
                                                                        A_Size<int>          const&  tile_size,
                                                                        double               const&  gsd,
                                                                        Status&                      status )
{

    
    status = Status(StatusType::FAILURE, CoreStatusReason::NOT_IMPLEMENTED, "Not Implemented");

    return nullptr;
}

        
/*************************************************************/
/*                  Create Elevation tile                    */
/*************************************************************/
ElevationTileUTM_d::ptr_t A_DEM_IO_Driver_SRTM::Create_Elevation_Tile( CRD::CoordinateGeographic_d const&  min_corner,
                                                                       A_Size<int>                 const&  tile_size,
                                                                       double                      const&  gsd,
                                                                       Status&                             status )
{
    
    status = Status(StatusType::FAILURE, CoreStatusReason::NOT_IMPLEMENTED, "Not Implemented");

    return nullptr;
}


} // End of DEM Namespace
} // End of GEO Namespace

