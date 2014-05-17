/**
 * @file    ImageDriverBase.hpp
 * @author  Marvin Smith
 * @date    5/11/2014
*/
#ifndef __GEOEXPLORE_IO_IMAGEDRIVERBASE_HPP__
#define __GEOEXPLORE_IO_IMAGEDRIVERBASE_HPP__

namespace GEO{

class ImageDriverBase{

    public:
        
        /**
         * Force every driver to test the magic number to see if it supports it
        */
        bool compareMagicNumber( const std::string& magicNumber )const;



}; /// End of ImageDriverBase Class

} /// End of GEO Namespace

#endif
