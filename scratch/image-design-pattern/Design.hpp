#ifndef __DESIGN_HPP__
#define __DESIGN_HPP__

/// C++ Standard Library
#include <cinttypes>
#include <iostream>

/// Boost C++ Library
#include <boost/shared_ptr.hpp>

using namespace std;

/**
 * @class ChannelType
*/
template <typename DataType, int BitDepth> 
class ChannelType{

    public:

        /// Type of data
        typedef DataType datatype;

        /// Min Value
        datatype minValue = 0;

        /// Max Value
        datatype maxValue = 1;

}; /// End of ChannelType Generic Class

/**
 * @class ChannelType
 * Double class specification
*/
template<>
class ChannelType<double,1>{

    public:
        
        /// Type of data
        typedef double datatype;

        /// Min Value
        datatype minValue = 0;

        /// Max Value
        datatype maxValue = 1;

}; /// End of ChannelType Double Specification

/**
 * @class ChannelType UInt8 Specification
 */
template<>
class ChannelType<uint8_t,8>{

    public:
        
        /// Type of data
        typedef uint8_t datatype;

        /// Min Value
        datatype minValue = 0;

        /// Max Value
        datatype maxValue = 255;

}; /// End of ChannelType UInt8

/**
 * @class ChannelType UInt12 Specification
 */
template<>
class ChannelType<uint16_t,12>{

    public:
        
        /// Type of data
        typedef uint16_t datatype;

        /// Min Value
        datatype minValue = 0;

        /// Max Value
        datatype maxValue = 4095;

}; /// End of ChannelType UInt12

/**
 * @class ChannelType UInt16 Specification
 */
template<>
class ChannelType<uint16_t,16>{

    public:
        
        /// Type of data
        typedef uint16_t datatype;

        /// Min Value
        datatype minValue = 0;

        /// Max Value
        datatype maxValue = 65535;

}; /// End of ChannelType UInt16

/// ChannelType Typedefs
typedef ChannelType<double,1>    ChannelTypeDouble;
typedef ChannelType<uint8_t,8>   ChannelTypeUInt8;
typedef ChannelType<uint16_t,12> ChannelTypeUInt12;
typedef ChannelType<uint16_t,16> ChannelTypeUInt16;
    

/**
 * @class PixelBase
*/
template <typename DerivedType, typename ChannelType>
class PixelBase{
    
    public:
        
        PixelBase(){}

}; /// End of PixelBase Class

/**
 * @class PixelRGB
*/
template <typename ChannelType>
class PixelRGB : public PixelBase<PixelRGB<ChannelType>,ChannelType>{

    public:
        
        /// Type of pixel
        typedef typename ChannelType::datatype datatype;

        /// Default Constructor
        PixelRGB(){}
    
        /// Information
        datatype m_data[3];
        

}; /// End of PixelRGB Class

/// Create a bunch of typdefs for different pixel types
typedef PixelRGB<ChannelTypeDouble>  PixelRGB_d;
typedef PixelRGB<ChannelTypeUInt8>   PixelRGB_u8;
typedef PixelRGB<ChannelTypeUInt12>  PixelRGB_u12;
typedef PixelRGB<ChannelTypeUInt16>  PixelRGB_u16;

/**
 * @class PixelGray
*/
template <typename ChannelType>
class PixelGray : public PixelBase<PixelGray<ChannelType>,ChannelType>{

    public:
        
        /// Type of pixel
        typedef typename ChannelType::datatype datatype;

        /// Default Constructor
        PixelGray(){}
    
        /// Information
        datatype m_data[3];
        

}; /// End of PixelRGB Class


/// Create a bunch of typdefs for different pixel types
typedef PixelGray<ChannelTypeDouble>  PixelGray_d;
typedef PixelGray<ChannelTypeUInt8>   PixelGray_u8;
typedef PixelGray<ChannelTypeUInt12>  PixelGray_u12;
typedef PixelGray<ChannelTypeUInt16>  PixelGray_u16;

/**
 * Driver Type
*/
class ImageDriver {
    
    public:
    
        /// Pointer Type
        typedef boost::shared_ptr<ImageDriver> ptr_t;

        /**
         * Default Constructor
        */
        ImageDriver(){
            cout << "ImageDriver Constructor " << endl;
        }

        /**
         * Get the row count
        */
        virtual int rows()const = 0;

        /**
         * Get the column count
        */
        virtual int cols()const = 0;

}; /// End of ImageDriver class

/**
 * GDAL Driver
*/
class GDAL_Driver : public ImageDriver {
    
    public:
        
        /**
         * Default Constructor
        */
        GDAL_Driver(){
            cout << "GDAL_Driver constructor" << endl;
        }

        /**
         * Get the number of rows
        */
        int rows()const{ return 10; } 

        /**
         * Get the number of columns
        */
        int cols()const{ return 12; }


}; /// End of GDAL Driver Class

/**
 * @class ResourceType
*/
template <typename DerivedType, typename PixelType>
class BaseResource{

    public:
        
        /**
         * Default Constructor
        */
        BaseResource(){
            cout << "BaseResource Constructor" << endl;
        }
        
        /**
         * Get the column count
        */
        virtual int cols()const = 0;

        /**
         * Get the row count
        */
        virtual int rows()const = 0;

}; /// End of BaseResourceType Class

/**
 * @class MemoryResource
*/
template<typename PixelType>
class MemoryResource : public BaseResource<MemoryResource<PixelType>,PixelType>{

    public:
        
        /**
         * Default Constructor
        */
        MemoryResource(){
            cout << "MemoryResource Constructor" << endl;    
        }

        /**
         * Get the number of rows
        */
        virtual int rows()const{ return 5; }

        /**
         * Get the number of cols
        */
        virtual int cols()const{ return 4; }
         


}; /// End of MemoryResource 

/**
 * @class Disk Resource
*/
template<typename PixelType>
class DiskResource : public BaseResource<DiskResource<PixelType>,PixelType>{
    
    public:
        
        /**
         * Default Constructor
        */
        DiskResource(){
            cout << "DiskResource Constructor" << endl;    
            
            // pretending we loaded the image
            m_driver =  ImageDriver::ptr_t(new GDAL_Driver);
        }

        /**
         * Get the number of rows
        */
        virtual int rows()const{ return m_driver->rows(); }

        /**
         * Get the number of columns
        */
        virtual int cols()const{ return m_driver->cols(); }

        /// Driver for the resource
        ImageDriver::ptr_t m_driver;

}; /// End of DiskResource

/**
 * @class MetadataBase
*/
class MetadataContainerBase {

    public:

        /// Pointer Type
        typedef boost::shared_ptr<MetadataContainerBase> ptr_t;

        /**
         * Default Constructor
        */
        MetadataContainerBase(){
            cout << "MetadataContainerBase Constructor" << endl;
        }

}; /// End of MetadataBase Class

/**
 * @class MetadataContainer
*/
class MetadataContainer : public MetadataContainerBase{

    public:
        
        /**
         * Default Constructor
        */
        MetadataContainer(){
            cout << "MetadataContainer Constructor" << endl;
        }

}; /// End of MetadataContainer Class

/**
 * @class Image_ 
*/
template <typename PixelType, typename ResourceType>
class Image_{

    public:
        
        /// Type of pixel
        typedef PixelType pixeltype;

        /// Type of channel
        typedef typename PixelType::datatype datatype;

        /**
         * Image Constructor
        */
        Image_() : m_metadata(new MetadataContainer){
            cout << "Image_ Constructor" << endl;
        }
        
        /**
         * Print the number of rows
        */
        int rows()const{ return m_resource.rows(); }

        /**
         * Print the number of columns
        */
        int cols()const{ return m_resource.cols(); }

    protected:
      
        /// Resource information
        ResourceType m_resource;
        
        /// Metadata container
        MetadataContainerBase::ptr_t m_metadata;

}; /// End of Image_ class

/// Create a Fat Set of Template Aliases
template <typename PixelType> using Image     = Image_<PixelType,MemoryResource<PixelType> >;
template <typename PixelType> using DiskImage = Image_<PixelType,DiskResource<PixelType> >;


template<typename PixelType, typename ResourceType>
class OrthoImage_ : public Image_<PixelType, ResourceType>{

    public:
        
        /**
         * Default Constructor
        */
        OrthoImage_(){
            cout << "OrthoImage_ Constructor" << endl;
        }
    
       /// get the coordinate position
       void pixel2world(){
           cout << "pixel x,y maps to X,Y" << endl;
       }
         

}; /// End of OrthoImage Class

/// Create Aliases for OrthoImage_
template <typename PixelType> using OrthoImage     = OrthoImage_<PixelType, MemoryResource<PixelType> >;
template <typename PixelType> using OrthoDiskImage = OrthoImage_<PixelType, DiskResource<PixelType> >;

#endif
