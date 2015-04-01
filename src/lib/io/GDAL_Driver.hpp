/**
 * @file    GDAL_Driver.hpp
 * @author  Marvin Smith
 * @date    4/30/2014
*/
#ifndef __SRC_CPP_IO_GDALDRIVER_HPP__
#define __SRC_CPP_IO_GDALDRIVER_HPP__

/// C++ Standard Libraries
#include <iostream>
#include <type_traits>
#include <vector>


/// GeoExplore Libraries
#include "../coordinate/CoordinateConversion.hpp"
#include "../core/Exceptions.hpp"
#include "../core/A_Status.hpp"
#include "../image/ChannelType.hpp"
#include "../image/Image.hpp"
#include "../image/MemoryResource.hpp"
#include "../io/ImageDriverBase.hpp"
#include "../math/A_Matrix.hpp"
#include "../math/A_Point.hpp"
#include "../math/A_Rectangle.hpp"
#include "../math/Matrix_Conversions.hpp"
#include "../utilities/FilesystemUtilities.hpp"
#include "gdal_utils/GDAL_Utilities.hpp"


namespace GEO{
namespace IO{
namespace GDAL{


/**
 * @brief Convert generic ChannelType to a GDAL Type.
*/
template<typename CType>
GDALDataType ctype2gdaltype(){
    if( std::is_same<CType,IMG::ChannelTypeUInt8>::value ){
        return GDT_Byte;
    }
    if( std::is_same<CType,IMG::ChannelTypeUInt12>::value ){
        return GDT_UInt16;
    }
    if( std::is_same<CType,IMG::ChannelTypeUInt14>::value ){
        return GDT_UInt16;
    }
    if( std::is_same<CType,IMG::ChannelTypeUInt16>::value ){
        return GDT_UInt16;
    }
    if( std::is_same<CType,IMG::ChannelTypeUInt32>::value ){
        return GDT_UInt32;
    }
    if( std::is_same<CType,IMG::ChannelTypeDouble>::value ){
        return GDT_Float64;
    }

    return GDT_Unknown;
}


/**
 * @class ImageDriverGDAL
*/
template <typename ResourceType>
class ImageDriverGDAL : public ImageDriverBase<ResourceType>{

    public:

        /// Pixel Type
        typedef typename ResourceType::pixel_type pixel_type;


        /// Pointer Type
        typedef std::shared_ptr<ImageDriverGDAL<ResourceType>> ptr_t;
        
        
        /**
         * @brief Constructor
        */
        ImageDriverGDAL()
          :  ImageDriverBase<ResourceType>(),
             m_driver(nullptr),
             m_dataset(nullptr),
             m_current_status(Status(StatusType::FAILURE,CoreStatusReason::UNINITIALIZED,"Uninitialized."))
        {
        }
        
        
        /**
         * @brief Constructor given image pathname.
         *
         * @param[in] pathname Image pathname.
        */
        ImageDriverGDAL( const FS::FilesystemPath& pathname )
          : m_path(pathname),
            m_driver(nullptr),
            m_dataset(nullptr),
            m_current_status(Status(StatusType::FAILURE,CoreStatusReason::UNINITIALIZED,"Uninitialized."))
        {
        }

        
        /**
         * @brief Destructor
        */
        ~ImageDriverGDAL()
        {
            if( Is_Open() == true ){
                Close();
            }
        }
        

        /**
         * @brief Check if the driver is supported for write.
         *
         * @param[in] pathname Pathname to check.
         *
         * @return True if supported, false otherwise.
        */
        static bool Is_Write_Supported( FS::FilesystemPath const& pathname ){
            
            // Get the file type
            FS::FileType file_type = FS::Get_File_Type( pathname );

            // Check NITF
            if( file_type == FS::FileType::NITF ){ return true; }

            // Check TIFF
            if( file_type == FS::FileType::TIFF ){ return true; }
           
            // Otherwise, return false
            return false;
        }
        
        
        /**
         * @brief Check if the driver is supported for reading.
         *
         * @param[in] pathname to check.
         *
         * @return True if supported, false otherwise.
        */
        static bool Is_Read_Supported( FS::FilesystemPath const& pathname )
        {
            // Get the file type
            FS::FileType file_type = FS::Get_File_Type( pathname );

            // Check JPEG
            if( file_type == FS::FileType::JPEG ){ return true; }

            // Check JP2
            if( file_type == FS::FileType::JPEG2000 ){ return true; }

            // Check DTED
            if( file_type == FS::FileType::DTED ){ return true; }

            // Check SRTM
            if( file_type == FS::FileType::SRTM ){ return true; }

            // Check NITF
            if( file_type == FS::FileType::NITF ){ return true; }
            
            // Check TIFF
            if( file_type == FS::FileType::TIFF ){ return true; }

            // Otherwise, return false 
            return false;

        }
       

        /**
         * @brief Check if the driver is open.
         *
         * @return True if the driver is open.
        */
        bool Is_Open()const
        {
            Status junk;
            return Is_Open(junk);
        }


        /**
          * @brief Check if the driver is open.
          *
          * @param[out] status Current program status.
          *
          * @return True if open. False otherwise.
          */
         bool Is_Open( Status& status )const{
            
            // Set the status
            status = m_current_status;

            // Check if dataset is null
            if( m_dataset == NULL ){
                return false;
            }
            return true;
         }


        /**
         * @brief Open the driver
        */
        virtual void Open()
        {

            /// if the dataset is already open, then do nothing
            if( Is_Open() == true ){
                std::cout << "error: dataset already open" << std::endl;
                return;
            }

            // make sure the file exists
            if( m_path.Exists() == false ){
                m_current_status = Status( StatusType::FAILURE, 
                                           CoreStatusReason::PATH_DOES_NOT_EXIST,
                                           "File does not exist.");
                return;
            }


            /// Register the driver
            GDALAllRegister();

        	// load the dataset 
            m_dataset = (GDALDataset*) GDALOpen( m_path.ToString().c_str(), GA_ReadOnly);
	
            // if dataset is null, then there was a problem
        	if( m_dataset == NULL ){
                m_current_status = Status( StatusType::FAILURE,
                                           GDALStatusReason::DATASET_INITIALIZATION_ERROR,
                                           "GDAL returned null object on open().");
		        return;
        	}
	
            // make sure we have pixel data inside the raster
            if( m_dataset->GetRasterCount() <= 0 ){
                m_current_status = Status( StatusType::FAILURE,
                                           GDALStatusReason::RASTER_CONTAINS_NO_PIXEL_DATA,
                                           "GDAL reports raster has no pixel data.");
                return;
            }
	
            //extract the driver infomation
            m_driver = m_dataset->GetDriver();
    
            // Status is good
            m_current_status = Status(StatusType::SUCCESS);
        }
        

        /**
         * @brief Open the driver given a filename.
         *
         * @param[in] pathname Image pathname to load the driver with.
        */
        virtual void Open( FS::FilesystemPath const& pathname )
        {
            m_path = pathname;
            Open();
        }


        /**
         * @brief Close the driver
        */
        void Close()
        {
            if( Is_Open() == false ){
                GDALClose((GDALDatasetH)m_dataset);
                m_dataset = NULL;
                m_driver = NULL;
            }
        }


        /**
         * @brief Get the OGR Spatial Reference Object.
         *
         * @param[out] ogr_reference OGR Spatial Reference Object.
         *
         * @return True if it exists, false otherwise.
        */
        bool Get_OGR_Spatial_Reference( OGRSpatialReference& ogr_reference )const{

            // Check that the dataset is not null
            if( m_dataset == NULL || m_dataset == nullptr ){
                return false;
            }

            // Get the Geo Reference
            char* wkt = (char*)m_dataset->GetProjectionRef();
            ogr_reference.importFromWkt(&wkt);

            // Return success;
            return true;
        }


        /**
         * @brief Get the GDAL ADF Geo Transform.
         *
         * @param[out] adfGeoTransform
         *
         * @return True if it exists, false otherwise.
        */
        bool Get_GDAL_Geo_Transform( double adfGeoTransform[6] )const{
            
            // make sure the dataset is not null
            if( m_dataset == NULL || m_dataset == nullptr ){
                return false;
            }

            // Get the geo transform
            if( m_dataset->GetGeoTransform( adfGeoTransform ) != CE_None ){
                return false;
            }

            // return success
            return true;
        }
        
        
        /**
         * @brief Return the driver type.
         *
         * @return Image driver type enumeration.
        */
        virtual ImageDriverType Get_ImageDriverType()const
        {
            return ImageDriverType::GDAL;
        }

        
        /**
         * @brief Return the number of rows.
         *
         * @return Number of rows in image.
        */
        virtual int Rows() const
        {
            if( m_dataset == nullptr || m_dataset == NULL ){
                return -1;    
            }
            return m_dataset->GetRasterYSize();
        }


        /**
         * @brief Return the number of columns.
         *
         * @return Number of columns in image.
        */
        virtual int Cols() const{
            if( m_dataset == nullptr || m_dataset == NULL){
                return -1;
            }
            return m_dataset->GetRasterXSize();
        }


        /**
         * @brief Get image pixel data.
         * 
         * @param[in] image_data Reference to pixel data.
         * @param[in] image_data_size Size of the image pixel buffer
         */
        void Get_Pixels( std::shared_ptr<std::vector<pixel_type> >& image_data, 
                         const int& image_data_size )
        {
            
            // if the dataset is not open, then do nothing
            if( Is_Open() == false )
            {
                std::cout << "warning: dataset is not open." << std::endl;
                return;
            }

            // make sure the vector is properly sized
            if( image_data_size != (Rows()*Cols()))
            {
                throw GEO::GeneralException("Error: image data must be pre-allocated to the required size.", __FILE__, __LINE__);
            }
        
        
            // get image dimensions
            int xsize = Cols();
            int ysize = Rows();

            // start iterating through each band
            float* pafScanline;
            double value;
    
            // get driver type
            std::string driverType;
            if( m_driver->GetDescription() != NULL )
            {
                driverType = m_driver->GetDescription();
            }

            // set the bit depth if we are nitf
            int NITF_ABPP=16;
            if( driverType == "NITF" )
            {
                if( m_dataset->GetMetadataItem("NITF_ABPP") != NULL )
                {
                    std::string abpp = m_dataset->GetMetadataItem("NITF_ABPP");
                    if( abpp == "12" )
                    {
                        NITF_ABPP=12;
                    }
                    else if( abpp == "14" )
                    {
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
                            value = IMG::range_cast<IMG::ChannelTypeUInt8, typename pixel_type::channeltype>( pafScanline[c] );
                        } else if( (gdalDataType == GDT_Int16 || gdalDataType == GDT_UInt16 ) || (NITF_ABPP == 12 )){
                            value = IMG::range_cast<IMG::ChannelTypeUInt12,typename pixel_type::channeltype>( pafScanline[c] );
                        } else if( gdalDataType == GDT_Int16 || gdalDataType == GDT_UInt16 ){
                            value = IMG::range_cast<IMG::ChannelTypeUInt16,typename pixel_type::channeltype>( pafScanline[c] );                        
                        } else {
                            value = pafScanline[c];
                        }


                        if( m_dataset->GetRasterCount() == 1 && (*image_data)[0].Dims() == 3 ){
                            (*image_data)[r*xsize + c] = value;
                        }
                        else {
                            (*image_data)[r*xsize + c][i] = value;
                        }
                    }

                    // clear data
                    CPLFree( pafScanline );
                }
            }
        
        }

        /**
         * Get the pixel value
        */
        virtual pixel_type Get_Pixel( const int& row, 
                                      const int& col )
        {
            
            // make sure the driver is open 
            if( Is_Open() == false ){
                Open();
            }
            
            // create output
            pixel_type output;

            // iterate over each channel
            float data;
            double value;
            for( int i=0; i<m_dataset->GetRasterCount(); i++ ){
            
                // create raster band
                GDALRasterBand* band = m_dataset->GetRasterBand(i+1);
                
                // get raster datatype
                int gdalDataType = band->GetRasterDataType();
                

                // read data
                band->RasterIO( GF_Read, col, row, 1, 1, &data, 1, 1, GDT_Float32, 0, 0);

                /// Convert datatypes
                if( gdalDataType == GDT_Byte ){
                    value = IMG::range_cast<IMG::ChannelTypeUInt8, typename pixel_type::channeltype>( data );
                //} else if( (gdalDataType == GDT_Int16 || gdalDataType == GDT_UInt16 ) || (NITF_ABPP == 12 )){
                //    value = IMG::range_cast<IMG::ChannelTypeUInt12,typename pixel_type::channeltype>( data );
                } else if( gdalDataType == GDT_Int16 || gdalDataType == GDT_UInt16 ){
                    value = IMG::range_cast<IMG::ChannelTypeUInt16,typename pixel_type::channeltype>( data );                        
                } else {
                    value = data;
                }

                    
                // if the current channel is less than the total channels for the pixeltype
                if( i <= output.Dims() && output.Dims() > 1 ){
                    output[i] = value;
                }
                // otherwise, just set it equal
                else{
                    output = value;
                }
            }

            return output;
        }


        /**
         * @brief Read an image from file.
         *
         * @param[in] pathname Image pathname.
         *
         * @return Image resource.
        */
        virtual typename IMG::MemoryResource<pixel_type>::ptr_t Read_Image(  FS::FilesystemPath const& pathname )
        {

            /// create the output
            typename IMG::MemoryResource<pixel_type>::ptr_t output(new IMG::MemoryResource<pixel_type>());

            // Open the dataset
            Open();

            // Make sure we had no major issues
            if( Is_Open() == false ){
                return output;
            }

            // create the pixeldata
            std::shared_ptr<std::vector<pixel_type> > pixeldata( new std::vector<pixel_type>(Rows() * Cols()));

            // pass the container to the driver
            Get_Pixels( pixeldata, Rows()*Cols() );


            output->Set_Pixel_Data( pixeldata, 
                                    Rows(), 
                                    Cols() );

            // return the resource
            return output;
        }
        
        
        /**
         * @brief Write an image to a GDAL format.
         *
         * @param[in] output_image Output image to write.
         * @param[in] pathname Image path to write to.
        */ 
        void Write_Image( IMG::Image_<pixel_type,ResourceType>const&  output_image,  
                          FS::FilesystemPath const& pathname )
        {

            // Identify the driver
            std::string driverShortName = Get_Short_Driver_From_Filename(pathname);
            if( driverShortName == "" ){
                throw std::runtime_error(pathname.ToString() + std::string(" does not have a supported gdal driver."));
            }

            // Get the gdal driver
            GDALDriver* gdal_driver = GetGDALDriverManager()->GetDriverByName(driverShortName.c_str());
    
            // make sure the driver can create images
            if( CSLFetchBoolean( gdal_driver->GetMetadata(), GDAL_DCAP_CREATE, FALSE )){
                if( CSLFetchBoolean( gdal_driver->GetMetadata(), GDAL_DCAP_CREATECOPY, FALSE )){
                    throw std::runtime_error(driverShortName + " Driver cannot create or copy images.");
                }
                throw std::runtime_error(driverShortName + " Driver cannot write images.");
            }
    
            // run create
            GDALDataset* dataset = gdal_driver->Create( pathname.ToString().c_str(), 
                                                        100,//output_image.cols(), 
                                                        100,//output_image.rows(), 
                                                        1,//output_image.channels(),
                                                        GDT_Byte,
                                                        NULL
                                                       );
    
            // iterate over each channel
            for( size_t i=0; i<output_image.Channels(); i++ ){
                GDALRasterBand* band = dataset->GetRasterBand(i+1);
                for( size_t x=0; x<output_image.Cols(); x++ )
                for( size_t y=0; y<output_image.Rows(); y++ ){
                    band->RasterIO( GF_Write, 0, 0, x, y, &output_image(y,x)[i], 1, 1, GDT_Byte, 0, 0);
                }
            }

            // close the dataset
            GDALClose(dataset);
        }


        /**
         * @brief Compute Image Extent
         *
         * @param[in] pathname Path to image file.
         * @param[out] status Status of the operation.
         */
        template<typename CoordinateModuleType>
        static MATH::A_Rectangle<CoordinateModuleType> 
                                    Compute_Image_Extent( FS::FilesystemPath const& pathname,
                                                          Status&                   status )
        {
            
            // Make sure it is read supported
            if( Is_Read_Supported( pathname ) == false ){
                status = Status( StatusType::FAILURE, 
                                 CoreStatusReason::FILE_NOT_SUPPORTED,
                                 "File not GDAL Readable.");
                return MATH::A_Rectangle<CoordinateModuleType>();
            }

            // Create a driver
            ImageDriverGDAL<ResourceType> driver(pathname);

            // Open the driver
            driver.Open();

            // Get the GDAL Geo Transform
            double adfGeoTransform[6];
            if( driver.Get_GDAL_Geo_Transform( adfGeoTransform ) == false ){
                status = Status( StatusType::FAILURE, 
                                 CoreStatusReason::GENERAL_IO_ERROR,
                                 "GDAL Transform Does Not Exist.");
                return MATH::A_Rectangle<CoordinateModuleType>();
            }

            // Build the output rectangle
            MATH::A_Rectangle<CoordinateModuleType> output;

            // Define our pixels
            MATH::A_Point2d world_tl = GDAL_Pixel_To_World( MATH::A_Point2d(             0,             0), adfGeoTransform );
            MATH::A_Point2d world_tr = GDAL_Pixel_To_World( MATH::A_Point2d( driver.Cols(),             0), adfGeoTransform );
            MATH::A_Point2d world_bl = GDAL_Pixel_To_World( MATH::A_Point2d(             0, driver.Rows()), adfGeoTransform );
            MATH::A_Point2d world_br = GDAL_Pixel_To_World( MATH::A_Point2d( driver.Cols(), driver.Rows()), adfGeoTransform );
            

            // Get the Projection
            OGRSpatialReference oSRS;
            driver.Get_OGR_Spatial_Reference( oSRS );

            // Get the Datum 
            Datum datum_type = Datum::WGS84;

            // Check if geographic
            if( oSRS.IsGeographic() ){
                 
                // Convert to the coordinate type
                CoordinateModuleType geo_tl = CRD::convert_coordinate<CoordinateModuleType>( CRD::CoordinateGeographic_d( world_tl.y(), world_tl.x(), 0, datum_type ));
                CoordinateModuleType geo_tr = CRD::convert_coordinate<CoordinateModuleType>( CRD::CoordinateGeographic_d( world_tr.y(), world_tr.x(), 0, datum_type ));
                CoordinateModuleType geo_bl = CRD::convert_coordinate<CoordinateModuleType>( CRD::CoordinateGeographic_d( world_bl.y(), world_bl.x(), 0, datum_type ));
                CoordinateModuleType geo_br = CRD::convert_coordinate<CoordinateModuleType>( CRD::CoordinateGeographic_d( world_br.y(), world_br.x(), 0, datum_type ));
                
                // Compute Bounds
                double minX = std::min( geo_tl.x(), std::min( geo_tr.x(), std::min( geo_bl.x(), geo_br.x())));
                double minY = std::min( geo_tl.y(), std::min( geo_tr.y(), std::min( geo_bl.y(), geo_br.y())));
                double maxX = std::max( geo_tl.x(), std::max( geo_tr.x(), std::max( geo_bl.x(), geo_br.x())));
                double maxY = std::max( geo_tl.y(), std::max( geo_tr.y(), std::max( geo_bl.y(), geo_br.y())));
                
                // Pass to rectangle
                output = MATH::A_Rectangle<CoordinateModuleType>( CoordinateModuleType( MATH::A_Point2d( minX, minY ) ), 
                                                                  CoordinateModuleType( MATH::A_Point2d( maxX, maxY ) ));
            
                // If we are utm, set the zone
                Add_Zone_To_Rectangle( output, geo_tl ); 
            }

            // Check if projected
            else if( oSRS.IsProjected() ){

                // Close the driver
                driver.Close();

                // Set the status
                status = Status( StatusType::FAILURE, 
                                 GDALStatusReason::UNKNOWN_PROJECTION_TYPE,
                                 std::string("Unknown projection type: ") + std::string(driver.m_dataset->GetProjectionRef()));
                
                // Return error
                return MATH::A_Rectangle<CoordinateModuleType>();
                
            }

            // Otherwise, I am wrong and need further help
            else{

                // Set the status
                status = Status( StatusType::FAILURE, 
                                 GDALStatusReason::UNKNOWN_PROJECTION_TYPE,
                                 std::string("Unknown projection type: ") + std::string(driver.m_dataset->GetProjectionRef()));

                // Close driver
                driver.Close();

                // return empty rectangle
                return MATH::A_Rectangle<CoordinateModuleType>();
            }

            // Close the driver
            driver.Close();
            
            // Return the output
            return output;
        }
        
    private:
        
        /// Filename
        FS::FilesystemPath m_path;

        /// Driver
        GDALDriver* m_driver;

        /// Dataset
        GDALDataset* m_dataset;
        
        /// IO Status
        Status m_current_status;


}; /// End of ImageDriverGDAL Class


} /// End of GDAL Namespace
} /// End of IO Namespace
} /// End of GEO Namespace


#endif
