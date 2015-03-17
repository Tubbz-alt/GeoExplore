/**
 *    @file    CoordinateMGRS.hpp
 *    @author  Marvin Smith
 *    @date    5/10/2014
*/
#ifndef __SRC_CPP_COORDINATE_COORDINATEMGRS_HPP__
#define __SRC_CPP_COORDINATE_COORDINATEMGRS_HPP__

/// GeoExplore Libraries
#include "../core/Enumerations.hpp"
#include "CoordinateBase.hpp"

namespace GEO{
namespace CRD{

/**
 * @class CoordinateMGRS
*/
template <typename DATATYPE>
class CoordinateMGRS : public CoordinateBase<DATATYPE>{

    public:
        
        /// Typedef the datatype
        typedef DATATYPE datatype;

        /// Create the pointer type
        typedef std::::shared_ptr<CoordinateMGRS<DATATYPE> > ptr_t;


        /**
         * Default Constructor
        */
        CoordinateMGRS() : CoordinateBase<DATATYPE>(){}


    private:




}; /// End of CoordinateMGRS Class


} /// End of CRD Namespace
} /// End of GEO Namespace


#endif
