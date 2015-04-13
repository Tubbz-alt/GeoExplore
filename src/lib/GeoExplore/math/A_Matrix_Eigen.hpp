/** 
 * @file    A_Matrix.hpp
 * @author  Marvin Smith
 * @date    3/23/2015
*/
#ifndef __GEOEXPLORE_LIB_MATH_A_MATRIX_EIGEN_HPP__
#define __GEOEXPLORE_LIB_MATH_A_MATRIX_EIGEN_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>

namespace GEO{
namespace MATH{
namespace EIGEN3{

/**
 * @class A_Matrix_Eigen_Impl
*/
class A_Matrix_Eigen_Impl;

} // End of EIGEN3 Namespace


/**
 * @class A_Matrix_Eigen
*/
class A_Matrix_Eigen{

    public:
        
        /**
         * @brief Constructor
        */
        A_Matrix_Eigen();

        
        /**
         * @brief Constructor given rows and columns.
         *
         * @param[in] rows Matrix rows.
         * @param[in] cols Matrix cols.
        */
        A_Matrix_Eigen( const int& rows,
                        const int& cols );


        /**
         * @brief Get the rows
         * 
         * @return Number of matrix rows.
        */
        int Rows()const;


        /**
         * @brief Get the columns.
         *
         * @return Number of matrix columns.
        */
        int Cols()const;

        
        /**
         * @brief Function Value Operator
         *
         * @param[in] row Row to get.
         * @param[in] col Column to get.
         *
         * @return Value at row and column.
        */
        double operator()( const int& row,
                           const int& col )const;


        /**
         * @brief Function Reference Operator
         *
         * @param[in] row Row to get.
         * @param[in] col Column to get.
         *
         * @return Reference to value at row and column.
        */
        double& operator()( const int& row,
                            const int& col );
        
        
        /**
         * @brief Bracket Value Operator
         *
         * @param[in] index Index position (Row-Major)
         *
         * @return Value of matrix at position.
         */
        double operator[]( const int& index )const;
        
        
        /**
         * @brief Bracket Value Operator
         *
         * @param[in] index Index position (Row-Major)
         *
         * @return Value of matrix at position.
         */
        double& operator[]( const int& index );


        /**
         * @brief Matrix Multiplication
         *
         * @param[in] other Other matrix to multiply.
         * 
         * @return Product of this matrix and the other
        */
        A_Matrix_Eigen operator* ( A_Matrix_Eigen const& other )const;
    
        
        /**
         * @brief Compute the matrix transpose.
         *
         * @return Transpose of the matrix.
         */
        A_Matrix_Eigen Transpose()const;


        /**
         * @brief Compute the Matrix Inverse.
         *
         * @return Inverse of the current matrix.
        */
        A_Matrix_Eigen Inverse( const double& eps = 0.000001 )const;

        
        /**
         * @brief Print to pretty string.
         *
         * @return Pretty string format.
        */
        std::string ToPrettyString()const;


    private:
    
        // Class Name
        std::string m_class_name;

        // Internal Matrix
        std::shared_ptr<EIGEN3::A_Matrix_Eigen_Impl> m_matrix;


}; // End of A_Matrix_Eigen Class

} // End of MATH Namespace
} // End of GEO  Namespace

#endif
