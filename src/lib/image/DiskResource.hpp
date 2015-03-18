/**
 * @file    DiskResource.hpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#ifndef __SRC_CPP_IMAGE_DISKRESOURCE_HPP__
#define __SRC_CPP_IMAGE_DISKRESOURCE_HPP__

/// GeoExplore Libraries
#include "BaseResource.hpp"
#include "Image.hpp"
#include "../core/Exceptions.hpp"
#include "../io/ImageDriverBase.hpp"

/// Boost C++ Libraries
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>


namespace GEO{
namespace IMG{

/**
 * @class DiskResource
*/
template <typename PixelType>
class DiskResource : public BaseResource<PixelType> {

    public:
        

        /**
         * Default Constructor
        */
        DiskResource() : m_image_driver(nullptr){

        }
        
        /**
         * Constructor given an image to load
        */
        DiskResource( boost::filesystem::path const& pathname ){

            // look for the proper driver to load
             
        }

        /**
         * Pixel Accessor
        */
        virtual PixelType operator()( const int& x, const int& y )const{
            return m_image_driver->getPixel<PixelType>(x, y);
        }

        /**
         * Pixel Reference Accessor
        */
        virtual PixelType& operator()(const int& x, const int& y ){
            throw std::runtime_error("PixelType& operator() Not Implemented in DiskResource.hpp");
        }
        
        /**
         * Pixel Accessor
        */
        virtual PixelType operator[]( const int& x )const{
            return m_image_driver->getPixel<PixelType>(x%cols(), x/cols());
        }

        /**
         * Pixel Reference Accessor
        */
        virtual PixelType& operator[]( const int& x ){
            std::runtime_error("PixelType& operator[] Not Implemented in DiskResource.hpp");
        }

        /**
         * Return the number of rows
         *
         * @return row count
        */
        virtual int rows()const{
            return m_image_driver->rows();
        }

        /**
         * Return the number of columns
         * 
         * @return column count
        */
        virtual int cols()const{
            return m_image_driver->cols();
        }
    
        /**
         * Return the number of channels
        */
        virtual int channels()const{
            return PixelType().dims();
        }

        /**
         * Set the driver
        */
        void setDriver( boost::shared_ptr<IO::ImageDriverBase>& image_driver ){
            m_image_driver = image_driver;
        }


    private:

        /// Specified image driver
        boost::shared_ptr<GEO::IO::ImageDriverBase> m_image_driver;



}; /// End of DiskResource Class

// Define the typedef alias
template <typename PixelType> using DiskImage = Image_<PixelType,GEO::IMG::DiskResource<PixelType> >;

} /// End of IMG Namespace
} /// End of GEO Namespace

#endif
