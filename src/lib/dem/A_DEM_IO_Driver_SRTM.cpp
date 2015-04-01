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
        if( m_srtm_pathnames[i].Is_Regular_File() == true )
        {
            Check_And_Add_SRTM_File( m_srtm_pathnames[i] );
        }

        // If the path is a directory, then iterate
        else if( m_srtm_pathnames[i].Is_Directory() == true ){
            
            // Get list of files
            std::vector<FS::FilesystemPath> pathlist = m_srtm_pathnames[i].Get_Contents(".*\\.hgt", true, FS::PathFormatType::ABSOLUTE);
            for( int pidx=0; pidx<pathlist.size(); pidx++ ){
                Check_And_Add_SRTM_File( pathlist[pidx] );
            }

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


/******************************************************************************/
/*             Check if a file is in the SRTM format and add if so.           */
/******************************************************************************/
void A_DEM_IO_Driver_SRTM::Check_And_Add_SRTM_File( FS::FilesystemPath const& pathname )
{
    // Status
    Status status;

    // Add to list of files
    if( pathname.Is_Regular_File() && FS::Get_File_Type(pathname) == FS::FileType::SRTM )
    {
        
        // Compute the extent
        MATH::A_Rectangle<CRD::CoordinateGeographic_d> extent = IO::GDAL::ImageDriverGDAL<resource_type>::Compute_Image_Extent<CRD::CoordinateGeographic_d>( pathname, status ); 
        
        // Convert to rectangle of points
        MATH::A_Rectangle2d rect_extent( MATH::A_Point2d(extent.BL().x(), extent.BL().y()), extent.Width(), extent.Height());
        
        
        // Add the path list
        if( status.Get_Status_Type() == StatusType::SUCCESS ){
            m_srtm_file_list.push_back(pathname);
            m_srtm_file_extents.push_back(rect_extent);
        }
    }
}


/***********************************************/
/*            Check Terrain Coverage           */
/***********************************************/
bool A_DEM_IO_Driver_SRTM::Coverage( CRD::CoordinateGeographic_d const& coordinate )const
{

    // Iterate through each extent
    for( size_t i=0; i<m_srtm_file_extents.size(); i++ )
    {
        if( m_srtm_file_extents[i].Inside( MATH::A_Point2d(coordinate.longitude_degrees(),
                                                           coordinate.latitude_degrees())) )
        {
            return true;
        }
    }

    // Iterate through file list
    return false;
}


/***********************************************/
/*            Check Terrain Coverage           */
/***********************************************/
bool A_DEM_IO_Driver_SRTM::Coverage( CRD::CoordinateGeographic_d const& min_coordinate,
                                     CRD::CoordinateGeographic_d const& max_coordinate )const
{

    // Overlap area eps
    const double eps = 0.0001;

    // Create a rectangle
    MATH::A_Rectangle2d bbox( MATH::A_Point2d(std::min(min_coordinate.longitude_degrees(), max_coordinate.longitude_degrees()),
                                              std::max(min_coordinate.latitude_degrees(),  max_coordinate.latitude_degrees())),
                              std::fabs( min_coordinate.x() - max_coordinate.x()),
                              std::fabs( min_coordinate.y() - max_coordinate.y()));

    MATH::A_Rectangle2d overlap;
    MATH::A_Rectangle2d shared_area;

    // Iterate through file list
    for( size_t i=0; i<m_srtm_file_extents.size(); i++ ){

        // Check if the boxes overlap
        overlap =  m_srtm_file_extents[i].Intersection(bbox);
        if( overlap.Area() > 0 ){
            
            // Get the different between this extent and the bbox
            shared_area = overlap.Union(bbox);
            
            // If the intersection and the union have the same area
            // then the boxes must overlap
            if( std::fabs(shared_area.Area() - overlap.Area()) <= eps ){
                return true;
            }
        }
    }

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

