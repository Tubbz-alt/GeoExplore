/**
 * @file    A_Point.hpp
 * @author  Marvin Smith
 * @date    3/8/2015
*/
#ifndef __GEOEXPLORE_SRC_MATH_A_POINT_HPP__
#define __GEOEXPLORE_SRC_MATH_A_POINT_HPP__

namespace GEO{

/**
 * @class A_Point
*/
template <typename DataType, int Dimensions>
class A_Point{

    public:

        /**
         * @brief Constructor
        */
        A_Point( )
          : m_data(new DataType[Dimensions])
        {
            // Initialize values
            for( int i=0; i<Dimensions; i++ ){
                m_data[i] = 0;
            }
        }

        /**
         * Get Reference
        */
        DataType& operator[]( const int& index ){
            return m_data[index];
        }

        /**
         * Get Value
        */
        DataType operator[]( const int& index )const{
            return m_data[index];
        }
            
        /**
         * @brief Dimensions
        */
        static constexpr int Dims(){
            return Dimensions;
        }

    private:
        
        /// Data
        DataType* m_data;


}; /// End of A_Point Class


// Typedefs
typedef A_Point<double,3> A_Point3d;
typedef A_Point<float,3>  A_Point3f;
typedef A_Point<uint8_t,3>  A_Point3u;

} /// End of Namespace GEO

#endif
