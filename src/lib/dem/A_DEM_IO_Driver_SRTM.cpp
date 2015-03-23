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


/**
 * Constructor
*/
A_DEM_IO_Driver_SRTM::A_DEM_IO_Driver_SRTM( boost::filesystem::path const& pathname )
  : m_srtm_pathname( pathname )
{
}


/**
 * Initialize
*/
Status A_DEM_IO_Driver_SRTM::Initialize(){
    
    // Make sure the path exists
    if( boost::filesystem::exists(m_srtm_pathname) == false ){
        return Status( StatusType::FAILURE, 
                       CoreStatusReason::PATH_DOES_NOT_EXIST,
                       "SRTM path does not exist.");
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
                m_srtm_file_list.push_back(temp_path);
            }
        }
    }
    else{
        return Status( StatusType::FAILURE, 
                       CoreStatusReason::PATH_DOES_NOT_EXIST,
                       "SRTM path does not exist.");
        
    }

    // Make sure we have some files
    if( m_srtm_file_list.size() <= 0 ){
        return Status( StatusType::FAILURE, 
                       CoreStatusReason::PATH_DOES_NOT_EXIST,
                       "Directory contains no SRTM files.");

    }
    
    // Return success
    return Status( StatusType::SUCCESS );

}


/**
 * Create Elevation Tile
*/
ElevationTileUTM_d::ptr_t  A_DEM_IO_Driver_SRTM::Create_Elevation_Tile( CRD::CoordinateUTM_d const&  min_corner,
                                                                        A_Size<int>     const&  tile_size,
                                                                        double          const&  gsd )
{

    return nullptr;
}

        
/**
 * Create Elevation tile
*/
ElevationTileUTM_d::ptr_t A_DEM_IO_Driver_SRTM::Create_Elevation_Tile( CRD::CoordinateGeographic_d const&  min_corner,
                                                                       A_Size<int>            const&  tile_size,
                                                                       double                 const&  gsd )
{

    return nullptr;
}


} // End of DEM Namespace
} // End of GEO Namespace

