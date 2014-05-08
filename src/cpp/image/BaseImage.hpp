/**
 *    @file    BaseImage.hpp
 *    @author  Marvin Smith
 *    @date    5/6/2014
*/
#ifndef __SRC_CPP_IMAGE_BASEIMAGE_HPP__
#define __SRC_CPP_IMAGE_BASEIMAGE_HPP__


namespace GEO {

/**
 * @class BaseImage
*/
template <typename PixelType>
class BaseImage{

    public: 

        /// define our pixeltype
        typedef PixelType pixeltype;

         /// define the datatype
         typedef typename pixeltype::channeltype;

        /**
         * Default Constructor
        */
        BaseImage (){}

        private:

            /// internal pixel data
            

};  /// End of BaseImage Class

} /// End of namespace GEO

#endif
