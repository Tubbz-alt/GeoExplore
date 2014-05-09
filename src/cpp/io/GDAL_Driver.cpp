/**
 *    @file.   GDAL_Driver.cpp
 *    @Author  Marvin Smith
 *    @date.   5/3/2014
 */
#include "GDAL_Driver.hpp"

namespace GEO {
namespace IO{
namespace GDAL{

/**
 * GDAL Driver constructor
*/
GDAL_Driver::GDAL_Driver( const boost::filesystem::path& pathname ){

    /// set the pathname
    m_path = pathname;

    // set the validity flag
    m_valid = false;

    // set the gdal objects
    m_driver = NULL;
    m_dataset = NULL;


}

/**
 * Destructor
*/
GDAL_Driver::~GDAL_Driver(){

    // check if the driver is open
    if( isOpen() == true ){
        close();
    }
}


/**
 * Check file validity
 */
bool GDAL_Driver::isValid()const{
    return m_valid;
}

/**
 * Get image row count
*/
int GDAL_Driver::rows()const{

    if( isOpen() == false ){
        return -1;
    }
    return m_dataset->GetRasterYSize();
}

/**
 * Get image column count
*/
int GDAL_Driver::cols()const{

    if( isOpen() == false ){
        return -1;
    }
    return m_dataset->GetRasterXSize();
}

/**
 * Open the dataset
*/
void GDAL_Driver::open(){

    /// if the dataset is already open, then do nothing
    if( isOpen() == true ){
        std::cout << "error: dataset already open" << std::endl;
        return;
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
    
    // set the valid flag
    m_valid = true;

}

/**
 * Close Dataset
 */
void GDAL_Driver::close(){

    if( isOpen() == false ){
        GDALClose((GDALDatasetH)m_dataset);
        m_dataset = NULL;
        m_driver = NULL;
    }

}

/**
 * Check if dataset is open
 */
bool GDAL_Driver::isOpen()const{
    return (m_dataset != NULL);
}


} /// End of GDAL Namespace
} /// End of IO Namespace
} /// End of GEO Namespace

