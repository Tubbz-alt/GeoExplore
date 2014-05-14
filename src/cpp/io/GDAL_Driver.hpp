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
#include <GeoExplore/core/Exceptions.hpp>
#include <GeoExplore/image/ChannelType.hpp>
#include <GeoExplore/image/MemoryResource.hpp>

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
        void getImageData( boost::shared_ptr<PixelType[]>& image_data, const int& image_data_size ){
            
            // if the dataset is not open, then do nothing
            if( isOpen() == false ){
                std::cout << "warning: dataset is not open." << std::endl;
                return;
            }

            // make sure the vector is properly sized
            if( image_data_size != (rows()*cols())){
                throw GEO::GeneralException("Error: image data must be pre-allocated to the required size.", __FILE__, __LINE__);
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


                        if( m_dataset->GetRasterCount() == 1 && image_data[0].dims() == 3 ){
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
boost::shared_ptr<PixelType[]> load_image_data( const boost::filesystem::path& image_pathname, int& rowCount, int& colCount ){
   
    // create the GDAL Driver
    GDAL_Driver::ptr_t gdal_driver( new GDAL_Driver(image_pathname));

    // open the dataset
    gdal_driver->open();

    // make sure our loader did not have any major issues
    if( gdal_driver->isValid() == false ){
        rowCount = 0;
        colCount = 0;
        return nullptr;
    }

    // create the main container with the expected size
    colCount = gdal_driver->cols();
    rowCount = gdal_driver->rows();
    

    // create the pixeldata
    boost::shared_ptr<PixelType[]> pixeldata( new PixelType[rowCount * colCount]);

    // pass the container to the driver
    gdal_driver->getImageData( pixeldata, rowCount * colCount );

    return pixeldata;
}

/**
 * Load an image and return a resource
*/
template<typename PixelType>
MemoryResource<PixelType> load_image( const boost::filesystem::path& image_pathname ){

    /// create the output
    MemoryResource<PixelType> output;

    // get the pixel data
    int rowSize, colSize;
    boost::shared_ptr<PixelType[]> pixels = load_image_data<PixelType>( image_pathname, rowSize, colSize );

    output.setPixelData( pixels, rowSize, colSize );

    // return the resource
    return output;
}

} /// End of GDAL Namespace
} /// End of IO Namespace
} /// End of GEO Namespace


#endif
