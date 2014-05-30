/**
 *    @file.   GDAL_Driver.cpp
 *    @Author  Marvin Smith
 *    @date.   5/3/2014
 */
#include "GDAL_Driver.hpp"

/// GeoExplore Libraries
#include <GeoExplore/utilities/StringUtilities.hpp>

namespace GEO {
namespace IO{
namespace GDAL{


/**
 * ImageDriverGDAL Constructor
*/
ImageDriverGDAL::ImageDriverGDAL(){

    // initialize the drivers
    m_driver = nullptr;
    m_dataset = nullptr;
}

/**
 * ImageDriverGDAL Constructor
*/
ImageDriverGDAL::ImageDriverGDAL( const boost::filesystem::path& pathname ){
    m_path = pathname;
    
    // initialize the drivers
    m_driver = nullptr;
    m_dataset = nullptr;
}

/**
 * Destructor
*/
ImageDriverGDAL::~ImageDriverGDAL(){

    if( isOpen() == true ){
        close();
    }
}

/**
 * Get the rows
*/
int ImageDriverGDAL::rows(){
    if( m_dataset == nullptr ){
        
        if( boost::filesystem::exists( m_path ) == true ){
            open();
            m_dataset->GetRasterYSize();
        }
        else{
            return 0;
        }
    }
    return m_dataset->GetRasterYSize();
}

/**
 * Get the columns
*/
int ImageDriverGDAL::cols(){
    if( m_dataset == nullptr ){
        if( boost::filesystem::exists( m_path ) == true ){
            open();
            m_dataset->GetRasterXSize();
        }
        else{
            return 0;
        }
    }
    return m_dataset->GetRasterXSize();
}

/**
 * Get the driver type
*/
ImageDriverType ImageDriverGDAL::type()const{
    return ImageDriverType::GDAL;
}

/**
 * Check if the driver is open
*/
bool ImageDriverGDAL::isOpen()const{
    if( m_dataset == NULL ){
        return false;
    }
    return true;
}

/**
 * Open the driver
*/
void ImageDriverGDAL::open( const boost::filesystem::path& pathname ){
    m_path = pathname;

    open();
}

/**
 * Open the driver
*/
void ImageDriverGDAL::open(){
    
    /// if the dataset is already open, then do nothing
    if( isOpen() == true ){
        std::cout << "error: dataset already open" << std::endl;
        return;
    }

    // make sure the file exists
    if( boost::filesystem::exists( m_path ) == false ){
        throw std::runtime_error( std::string(m_path.native() + " does not exist.").c_str());
    }

    /// Register the driver
    GDALAllRegister();

	// load the dataset 
    m_dataset = (GDALDataset*) GDALOpen( m_path.c_str(), GA_ReadOnly);
	
    // if dataset is null, then there was a problem
	if( m_dataset == NULL ){
        std::cout << "GDALOpen returned a null object." << std::endl;
		return;
	}
	
	// make sure we have pixel data inside the raster
	if( m_dataset->GetRasterCount() <= 0 ){
        std::cout << "File has no pixel data." << std::endl;
		return;
	}
	
	//extract the driver infomation
    m_driver = m_dataset->GetDriver();
    
}

/**
 * Close the driver
*/
void ImageDriverGDAL::close(){

    if( isOpen() == false ){
        GDALClose((GDALDatasetH)m_dataset);
        m_dataset = NULL;
        m_driver = NULL;
    }
}


std::string getShortDriverFromFilename( const boost::filesystem::path& filename ){

    // pull the extension
    std::string ext = filename.extension().native();
    std::string extl = string_toLower(ext);

    // png images
    if( extl == ".png" ){
        return "PNG";
    }
    
    // ntf images
    if( extl == ".ntf" || extl == ".ntif" ){
        return "NITF";
    }
    
    // jpeg images
    if( extl == ".jpg" || extl == "jpeg" ){
        return "JPEG";
    }

    return "";
}


} /// End of GDAL Namespace
} /// End of IO Namespace
} /// End of GEO Namespace

