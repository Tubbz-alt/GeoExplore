/**
 * @file    GDAL_Driver.hpp
 * @author  Marvin Smith
 * @date    4/30/2014
*/
#ifndef __SRC_CPP_IO_GDALDRIVER_HPP__
#define __SRC_CPP_IO_GDALDRIVER_HPP__

/// C++ Standard Libraries
#include <vector>

/// Boost C++ Libraries
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

/// GDAL Libraries
#include <gdal/cpl_conv.h>
#include <gdal/gdal_priv.h>

/// GeoExplore Libraries
#include <GeoExplore/image/ChannelType.hpp>

namespace GEO{
namespace IO{
namespace GDAL{

/**
 * @class GDAL_Driver
*/
class GDAL_Driver{

    public:
        
        /// create a shared object
        typedef boost::shared_ptr<GDAL_Driver> ptr_t;
        
        /**
         * Parameterized Constructor
        */
        GDAL_Driver( const boost::filesystem::path& image_pathname );

        /**
         * Destructor
        */
        ~GDAL_Driver();

        /**
         * Check validity
        */
        bool isValid()const;

        /**
         * Get number of rows
        */
        int rows()const;

        /**
         * Get number of columns
        */
        int cols()const;
        
        /**
         * Get image data
         */
        template<typename PixelType>
        void getImageData( std::vector<PixelType>& image_data ){
            
            // if the dataset is not open, then do nothing
            if( isOpen() == false ){
                std::cout << "warning: dataset is not open." << std::endl;
                return;
            }

            // make sure the vector is properly sized
            if( image_data.size() != (rows()*cols())){
                image_data.resize( rows()*cols());
            }
        
        
            // get image dimensions
            int xsize = cols();
            int ysize = rows();

            // start iterating through each band
            float* pafScanline;
            double value;
    
            // get driver type
            std::string driverType;
            if( m_driver->GetDescription() != NULL ){
                driverType = m_driver->GetDescription();
            }

            // set the bit depth if we are nitf
            int NITF_ABPP=16;
            if( driverType == "NITF" ){
                if( m_dataset->GetMetadataItem("NITF_ABPP") != NULL ){
                    std::string abpp = m_dataset->GetMetadataItem("NITF_ABPP");
                    if( abpp == "12" ){
                        NITF_ABPP=12;
                    }
                    else if( abpp == "14" ){
                        NITF_ABPP=14;
                    }
                }
            }


            for( int i=0; i<m_dataset->GetRasterCount(); i++ ){
                
                // create raster band
                GDALRasterBand* band = m_dataset->GetRasterBand(i+1);
                
                // get raster datatype
                int gdalDataType = band->GetRasterDataType();
                
                // iterate over every row
                for( int r=0; r<ysize; r++ ){

                    // initialize data
                    pafScanline = (float*) CPLMalloc(sizeof(float) * xsize);
                    
                    // read data
                    band->RasterIO( GF_Read, 0, r, xsize, 1, pafScanline, xsize, 1, GDT_Float32, 0, 0);

                    

                    //add data to vector
                    for( size_t c=0; c<xsize; c++ ){
                        
                        /// Convert datatypes
                        if( gdalDataType == GDT_Byte ){
                            value = range_cast<ChannelTypeUInt8, typename PixelType::channeltype>( pafScanline[c] );
                        } else if( (gdalDataType == GDT_Int16 || gdalDataType == GDT_UInt16 ) || (NITF_ABPP == 12 )){
                            value = range_cast<ChannelTypeUInt12,typename PixelType::channeltype>( pafScanline[c] );
                        } else if( gdalDataType == GDT_Int16 || gdalDataType == GDT_UInt16 ){
                            value = range_cast<ChannelTypeUInt16,typename PixelType::channeltype>( pafScanline[c] );                        
                        } else {
                            value = pafScanline[c];
                        }


                        if( m_dataset->GetRasterCount() == 1 && image_data.front().dims() == 3 ){
                            image_data[r*xsize + c] = value;
                        }
                        else {
                            image_data[r*xsize + c][i] = value;
                        }
                        

                    }

                    // clear data
                    CPLFree( pafScanline );


                }
            }
        
        }

        /**
         * Open image data
         */
        void open( );
        
        /**
         * Close Dataset
         */
        void close();

        /**
         * Check if the dataset is open
         */
        bool isOpen()const;
        

    private:

        /// Location of file
        boost::filesystem::path m_path;
        
        /// Valid flag
        bool m_valid;

        /// GDAL Driver
        GDALDriver* m_driver;

        /// GDAL Dataset
        GDALDataset* m_dataset;


}; /// End of GDAL_Driver class

/**
 * Read an image and return the image data
*/
template <typename PixelType>
std::vector<PixelType> load_image_data( const boost::filesystem::path& image_pathname, int& rowCount ){
   
    // create the GDAL Driver
    GDAL_Driver::ptr_t gdal_driver( new GDAL_Driver(image_pathname));

    // open the dataset
    gdal_driver->open();

    // make sure our loader did not have any major issues
    if( gdal_driver->isValid() == false ){
        return std::vector<PixelType>();
    }

    // create the main container with the expected size
    int cols = gdal_driver->cols();
    rowCount = gdal_driver->rows();
    

    // create the pixeldata
    std::vector<PixelType> pixeldata( rowCount * cols);

    // pass the container to the driver
    gdal_driver->getImageData( pixeldata );

    return pixeldata;
}


} /// End of GDAL Namespace
} /// End of IO Namespace
} /// End of GEO Namespace


#endif
