/**
 * @file    MemoryResource.hpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#ifndef __SRC_CPP_IMAGE_MEMORYRESOURCE_HPP__
#define __SRC_CPP_IMAGE_MEMORYRESOURCE_HPP__


namespace GEO{


/**
 * @class MemoryResource
*/
template <typename PixelType>
class MemoryResource : public BaseResource {

    public:

        /**
         * Get the pixel value
        */
        virtual PixelType operator[]const( const int& idx )const{
            return m_data[idx];
        }

        /**
         * Get the pixel reference
        */
        virtual PixelType& operator[]( const int& idx ){
            return m_data[idx];
        }
        

    private:

        /// List of pixels
        std::vector<PixelType> m_data;

}; /// End of MemoryResource Class

} /// End of GEO Namespace

#endif
