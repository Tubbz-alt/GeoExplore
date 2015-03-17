#ifndef __GEOEXPLORE_MATH_A_RECTANGLE_HPP__
#define __GEOEXPLORE_MATH_A_RECTANGLE_HPP__

// Geo-Explore Libraries
#include "A_Polygon.hpp"

namespace GEO{

/**
 * @class A_Rectangle
*/
template< typename DataType >
class A_Rectangle : public A_Polygon<DataType> {

    public:
        
        /**
         * Constructor
        */
        A_Rectangle()
          : A_Polygon<DataType>()
        {

        }


}; /// End of A_Rectangle Class

// Typedefs
typedef A_Rectangle<double> A_Rectangle_d;

} // End of GEO Namespace


#endif

