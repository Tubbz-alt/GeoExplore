#ifndef __GEOEXPLORE_SRC_MATH_A_SIZE_HPP__
#define __GEOEXPLORE_SRC_MATH_A_SIZE_HPP__

/// C++ Libraries
#include <cinttypes>

namespace GEO{

/**
 * @class A_Size
*/
template <typename DataType>
class A_Size{

    public:
        
        /**
         * Constructor
        */
        A_Size()
          : m_width(0),
            m_height(0)
        {
        }

        /**
         * Constructor
        */
        A_Size( const DataType& width,
                const DataType& height )
          : m_width(width),
            m_height(height)
        {

        }
    
        /**
         * @brief Get the Width
        */
        DataType Width()const{
            return m_width;
        }


        /**
         * @brief Get the Height
        */
        DataType Height()const{
            return m_height;
        }


    private:
        
        /// Width
        DataType m_width;

        /// Height
        DataType m_height;


}; /// End of A_Size Class


// Typedefs
typedef A_Size<double>      A_Size_d;
typedef A_Size<uint32_t>    A_Size_i;

} /// End of GEO Namespace

#endif
