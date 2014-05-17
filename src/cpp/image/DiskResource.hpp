/**
 * @file    DiskResource.hpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#ifndef __SRC_CPP_IMAGE_DISKRESOURCE_HPP__
#define __SRC_CPP_IMAGE_DISKRESOURCE_HPP__

/// GeoExplore Libraries
#include <GeoExplore/image/BaseResource.hpp>
#include <GeoExplore/io/ImageDriverBase.hpp>

/// C++ Standard Libraries
#include <boost/shared_ptr.hpp>


namespace GEO{

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
         * Return the number of rows
         *
         * @return row count
        */
        virtual int rows()const{
            return 0;
        }

        /**
         * Return the number of columns
         * 
         * @return column count
        */
        virtual int cols()const{
            return 0;
        }
    
        /**
         * Return the number of channels
        */
        virtual int channels()const{
            return PixelType().dims();
        }

    private:

        /// Specified image driver
        boost::shared_ptr<GEO::IO::ImageDriverBase> m_image_driver;



}; /// End of DiskResource Class

} /// End of GEO Namespace

#endif
