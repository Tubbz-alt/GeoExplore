/**
 *    @file    CoordinateMGRS.hpp
 *    @author  Marvin Smith
 *    @date    5/10/2014
*/
#ifndef __SRC_CPP_COORDINATE_COORDINATEMGRS_HPP__
#define __SRC_CPP_COORDINATE_COORDINATEMGRS_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>
#include <GeoExplore/coordinate/CoordinateBase.hpp>

namespace GEO{

/**
 * @class CoordinateMGRS
*/
template <typename DATATYPE>
class CoordinateMGRS : public CoordinateBase<DATATYPE>{

    public:
        
        /// Typedef the datatype
        typedef DATATYPE datatype;

        /// Create the pointer type
        typedef boost::shared_ptr<CoordinateMGRS<DATATYPE> > ptr_t;


        /**
         * Default Constructor
        */
        CoordinateMGRS() : CoordinateBase<DATATYPE>(){}


    private:




}; /// End of CoordinateMGRS Class


} /// End of GEO Namespace


#endif
