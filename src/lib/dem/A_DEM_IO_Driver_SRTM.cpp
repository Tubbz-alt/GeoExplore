/**
 * @file    A_DEM_IO_Driver_SRTM.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include "A_DEM_IO_Driver_SRTM.hpp"

// GeoExplore Libraries
#include "../../lib/coordinate/CoordinateConversion.hpp"
#include "../../lib/utilities/FilesystemUtilities.hpp"


namespace GEO{
namespace DEM{


/*************************************************************/
/*                      Constructor                          */
/*************************************************************/
A_DEM_IO_Driver_SRTM::A_DEM_IO_Driver_SRTM( FS::FilesystemPath const& pathname )
  : A_DEM_IO_Driver_Base(),
    m_class_name("A_DEM_IO_Driver_SRTM"),
    m_initialization_status(Status(StatusType::FAILURE,CoreStatusReason::UNINITIALIZED, "Uninitialized."))
{
    // Add the pathnames
    m_srtm_pathnames.push_back( pathname );
}


/*************************************************************/
/*                      Constructor                          */
/*************************************************************/
A_DEM_IO_Driver_SRTM::A_DEM_IO_Driver_SRTM( std::vector<FS::FilesystemPath> const& pathnames )
  : A_DEM_IO_Driver_Base(),
    m_class_name("A_DEM_IO_Driver_SRTM"),
    m_initialization_status(Status(StatusType::FAILURE,CoreStatusReason::UNINITIALIZED, "Uninitialized.")),
    m_srtm_pathnames(pathnames)
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
    
    // Misc Variables
    Status temp_status;

    // Make sure we have paths
    if( m_srtm_pathnames.size() <= 0 ){
        m_initialization_status = Status( StatusType::FAILURE,
                                          DemStatusReason::NO_SRTM_PATHS,
                                          "No SRTM Files to Initialize.");
        return m_initialization_status;
    }

    
    // Iterate over each path
    for( int i=0; i<(int)m_srtm_pathnames.size(); i++ ){

        // Make sure path exists
        if( m_srtm_pathnames[i].Exists() != true ){
            //std::cerr << "error: SRTM Path (" << m_srtm_pathnames[i].ToString() << ") does not exist. Skipping." << std::endl;
            continue;
        }

        // If the path is a regular SRTM File, then process
        if( m_srtm_pathnames[i].Is_Regular_File() == true  &&
            FS::Get_File_Type(m_srtm_pathnames[i]) == FS::FileType::SRTM )
        {

            // Add to list of files
            m_srtm_file_list.push_back(m_srtm_pathnames[i]);

        }

        // If the path is a directory, then iterate
        else if( m_srtm_pathnames[i].Is_Directory() == true ){
            
            // Get list of files
            //boost::filesystem::recursive_directory_iterator it(m_srtm_pathname);
            //for( ; it != boost::filesystem::recursive_directory_iterator(); it++ ){
            
                // Get path
                //boost::filesystem::path temp_path = it->path();

                // Check if srtm
                //if( FS::Get_File_Type(temp_path) == FS::FileType::SRTM ){

                    // Get the extent of the file

                    // Add the path to the list
                    //m_srtm_file_list.push_back(temp_path);
                //}
            //}
        }

        // Otherwise, we have an issue
        else{
            std::cerr << "error: Unknown configuration. Skipping path." << std::endl;
            continue;
        }
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


/***********************************************/
/*            Check Terrain Coverage           */
/***********************************************/
bool A_DEM_IO_Driver_SRTM::Coverage( CRD::CoordinateGeographic_d const& min_coordinate,
                                     CRD::CoordinateGeographic_d const& max_coordinate )const
{

    // Iterate through file list
    return false;
        
}


/*************************************************************/
/*                   Query Elevation Tile                    */
/*************************************************************/
double A_DEM_IO_Driver_SRTM::Query_Elevation_Meters( CRD::CoordinateGeographic_d const& coordinate,
                                                     Status& status )const
{

    // Get the elevation
    double elevation_meters = 0;

    // Return success
    status = Status(StatusType::SUCCESS);

    return elevation_meters;

}


/*************************************************************/
/*                   Query Elevation Tile                    */
/*************************************************************/
double A_DEM_IO_Driver_SRTM::Query_Elevation_Meters( CRD::CoordinateUTM_d const& coordinate,
                                                     Status& status )const
{

    // Convert to Geographic
    CRD::CoordinateGeographic_d coord_geog = CRD::convert_coordinate<CRD::CoordinateGeographic_d>(coordinate);
    
    // run geographic query
    return Query_Elevation_Meters( coord_geog, status );

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

