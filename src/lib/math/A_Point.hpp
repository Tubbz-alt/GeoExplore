/**
 * @file    A_Point.hpp
 * @author  Marvin Smith
 * @date    3/8/2015
*/
#ifndef __GEOEXPLORE_SRC_MATH_A_POINT_HPP__
#define __GEOEXPLORE_SRC_MATH_A_POINT_HPP__

namespace GEO{
namespace MATH{

/**
 * @class A_Point
*/
template <typename DataType, int Dimensions>
class A_Point{

    public:
        
        /// Datatype
        typedef DataType datatype;


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
         * @brief 2d constructor
         *
         * @param[in] x X Value.
         * @param[in] y Y Value.
        */
        A_Point( DataType const& x,
                 DataType const& y )
          : m_data(new DataType[Dimensions])
        {
            // Initialize
            for( int i=0; i<Dimensions; i++ ){
                m_data[i] = 0;
            }
            m_data[0] = x;
            m_data[1] = y;
        }
        
        
        /** 
         * @brief 3d constructor
         *
         * @param[in] x X Value.
         * @param[in] y Y Value.
         * @param[in] z Z Value.
        */
        A_Point( DataType const& x,
                 DataType const& y,
                 DataType const& z )
          : m_data(new DataType[Dimensions])
        {
            // Initialize
            for( int i=0; i<Dimensions; i++ ){
                m_data[i] = 0;
            }
            m_data[0] = x;
            m_data[1] = y;
            m_data[2] = z;
        }
        

        /** 
         * @brief Copy Constructor
         *
         * @param[in] other Other point to copy.
         */
        A_Point( A_Point<DataType,Dimensions>const& other )
          : m_data(new DataType[Dimensions])
        {
            for( int i=0; i<Dimensions; i++ ){
                m_data[i] = other[i];
            }
        }


        /** 
         * @brief Destructor
        */
        ~A_Point()
        {
            if( m_data != nullptr || m_data != NULL ){
                delete [] m_data;
                m_data = nullptr;
            }
        }
        

        /**
         * @brief Assignment Operator
         *
         * @param[in] other Other point to copy.
         *
         * @return Assigned point
        */
        A_Point<DataType,Dimensions>& operator = ( const A_Point<DataType,Dimensions>& other )
        {
            // Check this
            if( this == (&other) ){
                return (*this);
            }

            // copy data
            for( int i=0; i<Dimensions; i++ ){
                m_data[i] = other[i];
            }

            // Return 
            return (*this);
        }

        
        /**
         * @brief Assignment Operator
         *
         * @param[in] other Other point to copy.
         *
         * @return Assigned point
        */
        A_Point<DataType,Dimensions> operator = ( const A_Point<DataType,Dimensions>& other )const
        {
            // Check this
            if( this == (&other) ){
                return (*this);
            }

            // copy data
            for( int i=0; i<Dimensions; i++ ){
                m_data[i] = other[i];
            }

            // Return 
            return (*this);
        }


        /**
         * @brief Get Reference.
         *
         * @param[in] index Position to get.
         *
         * @return Reference to value at index.
        */
        DataType& operator[]( const int& index ){
            return m_data[index];
        }

        
        /**
         * @brief Get Value.
         *
         * @param[in] index Position to get.
         *
         * @return Value at index.
        */
        DataType operator[]( const int& index )const{
            return m_data[index];
        }


        /**
         * @brief Get the x value
         * 
         * @return X Value.
        */
        DataType x()const{
            return m_data[0];
        }


        /** 
         * @brief Set the x value.
         *
         * @return Reference to x value.
        */
        DataType& x(){
            return m_data[0];
        }


        /**
         * @brief Get the Y Value.
         *
         * @return Y value.
        */
        DataType y()const{
            return m_data[1];
        }


        /**
         * @brief Set the y value.
         *
         * @return Reference to y value.
        */
        DataType& y(){
            return m_data[1];
        }


        /**
         * @brief Get the z value.
         *
         * @return Z value.
        */
        DataType z()const{
            return m_data[2];
        }


        /**
         * @brief Get the z reference.
         *
         * @return Reference to z value.
        */
        DataType& z(){
            return m_data[2];
        }
                

        /**
         * @brief Dimensions.
         *
         * @return Dimensions of point.
        */
        static constexpr int Dims(){
            return Dimensions;
        }


        /**
         * @brief Addition Operator
         * 
         * @param[in] other Other point to add.
         *
         * @return Sum of this point and the other point.
        */
        A_Point<DataType,Dimensions> operator + ( const A_Point<DataType,Dimensions>& other )const{
            
            // Create output point
            A_Point<DataType,Dimensions> output;
            for( int i=0; i<Dimensions; i++ ){
                output[i] = m_data[i] + other[i];
            }

            // return output point
            return output;
        }
        
        
        /**
         * @brief Subtraction Operator
         * 
         * @param[in] other Other point to subtraction.
         *
         * @return Difference of this point and the other point.
        */
        A_Point<DataType,Dimensions> operator - ( const A_Point<DataType,Dimensions>& other )const{
            
            // Create output point
            A_Point<DataType,Dimensions> output;
            for( int i=0; i<Dimensions; i++ ){
                output[i] = m_data[i] - other[i];
            }

            // return output point
            return output;
        }


    private:
        
        /// Data
        DataType* m_data;


}; /// End of A_Point Class

// Template Aliases
template <typename DataType> using A_Point2 = A_Point<DataType,2>;
template <typename DataType> using A_Point3 = A_Point<DataType,3>;

// Typedefs
typedef A_Point<double,2>   A_Point2d;
typedef A_Point<float,2>    A_Point2f;
typedef A_Point<int32_t,2>  A_Point2i;
typedef A_Point<int16_t,2>  A_Point2s;
typedef A_Point<uint8_t,2>  A_Point2u;

typedef A_Point<double,3>    A_Point3d;
typedef A_Point<float,3>     A_Point3f;
typedef A_Point<int32_t,3>   A_Point3i;
typedef A_Point<int16_t,3>   A_Point3s;
typedef A_Point<uint8_t,3>   A_Point3u;

} // End of MATH Namespace
} // End of GEO  Namespace 

#endif
