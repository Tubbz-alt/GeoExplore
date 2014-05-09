/**
 * @file    BaseResource.hpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#ifndef __SRC_CPP_IMAGE_BASERESOURCE_HPP__
#define __SRC_CPP_IMAGE_BASERESOURCE_HPP__


namespace GEO{


/**
 * @class BaseResource
*/
class BaseResource{

    public:
        
        /**
         * Return the pixel value
        */
        virtual double operator[]( const int& idx )const;

        /**
         * Return the pixel reference
        */
        virtual double& operator[]( const int& idx );



}; /// End of BaseResource Class

} /// End of GEO Namespace

#endif
