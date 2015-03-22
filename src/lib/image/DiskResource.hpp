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


namespace GEO{
namespace IMG{

/**
 * @class DiskResource
*/
template <typename PixelType>
class DiskResource : public BaseResource<PixelType> {

    public:
        
        /// Pixel Type
        typedef PixelType pixel_type;


        /// Pointer Type
        typedef std::shared_ptr<DiskResource<PixelType>> ptr_t;


        /**
         * @brief Constructor
        */
        DiskResource() 
            : m_image_driver(nullptr)
        {
        }
        

        /**
         * @brief Constructor given an image to load.
         *
         * @param[in] pathname Image to load.
        */
        DiskResource( boost::filesystem::path const& pathname )
        {
        }


        /**
         * @brief Pixel Access Operator.
         *
         * @param[in] row Row to fetch.
         * @param[in] col Column to fetch.
         * 
         * @return Pixel value at the position.
        */
        virtual PixelType operator()( const int& row, 
                                      const int& col )const
        {
            return m_image_driver->Get_Pixel(row, col);
        }


        /**
         * @brief Pixel Reference Access Operator.
         *
         * @param[in] row Row to fetch.
         * @param[in] col Column to fetch.
         * 
         * @return Reference to pixel value at position.
        */
        virtual PixelType& operator()( const int& row, 
                                       const int& col )
        {
            throw std::runtime_error("PixelType& operator() Not Implemented in DiskResource.hpp");
        }
        
        
        /**
         * @brief Pixel Access Operator
         *
         * @param[in] index Position to access.
         *
         * @return Value of pixel at index.
        */
        virtual PixelType operator[]( const int& index )const
        {
            return m_image_driver->Get_Pixel( index % Cols(), index / Cols());
        }


        /**
         * @brief Pixel Reference Access Operator.
         *  
         * @param[in] index Position to access.
         *
         * @return Reference to pixel at position.
        */
        virtual PixelType& operator[]( const int& index )
        {
            std::runtime_error("PixelType& operator[] Not Implemented in DiskResource.hpp");
        }


        /**
         * @brief Return the number of rows
         *
         * @return row count
        */
        virtual int Rows()const{
            return m_image_driver->Rows();
        }


        /**
         * @brief Return the number of columns
         * 
         * @return column count
        */
        virtual int Cols()const{
            return m_image_driver->Cols();
        }
    

        /**
         * @brief Return the number of channels.
         *
         * @return Channel Count.
        */
        virtual int Channels()const{
            return PixelType().Dims();
        }


        /**
         * @brief Set the image io driver.
         * 
         * @param[in] image_driver Driver to set.
        */
        void Set_Driver( typename IO::ImageDriverBase<DiskResource<PixelType>>::ptr_t image_driver )
        {
            m_image_driver = image_driver;
        }


    private:

        /// Specified image driver
        typename IO::ImageDriverBase<DiskResource<PixelType>>::ptr_t  m_image_driver;



}; /// End of DiskResource Class

// Define the typedef alias
template <typename PixelType> using DiskImage = Image_<PixelType,GEO::IMG::DiskResource<PixelType> >;

} /// End of IMG Namespace
} /// End of GEO Namespace

#endif
