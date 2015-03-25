/** 
 * @file    A_Matrix.hpp
 * @author  Marvin Smith
 * @date    3/23/2015
*/
#ifndef __GEOEXPLORE_LIB_MATH_A_MATRIX_EIGEN_HPP__
#define __GEOEXPLORE_LIB_MATH_A_MATRIX_EIGEN_HPP__

// Eigen Libraries
#include <Eigen/Dense>

// C++ Standard Libraries
#include <string>

namespace GEO{
namespace MATH{

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
        inline int Rows()const{
            return m_matrix.rows();
        }


        /**
         * @brief Get the columns.
         *
         * @return Number of matrix columns.
        */
        inline int Cols()const{
            return m_matrix.cols();
        }

        
        /**
         * @brief Function Value Operator
         *
         * @param[in] row Row to get.
         * @param[in] col Column to get.
         *
         * @return Value at row and column.
        */
        double operator()( const int& row,
                           const int& col )const
        {
            return m_matrix(row,col);
        }


        /**
         * @brief Function Reference Operator
         *
         * @param[in] row Row to get.
         * @param[in] col Column to get.
         *
         * @return Reference to value at row and column.
        */
        double& operator()( const int& row,
                            const int& col )
        {
            return m_matrix(row,col);
        }
        

        /**
         * @brief Matrix Multiplication
         *
         * @param[in] other Other matrix to multiply.
         * 
         * @return Product of this matrix and the other
        */
        A_Matrix_Eigen operator* ( A_Matrix_Eigen const& other )const;
    
        
        /**
         * @brief Print to pretty string.
         *
         * @return Pretty string format.
        */
        std::string ToPrettyString()const;


    private:
        
        // Internal Matrix
        Eigen::MatrixXd m_matrix;


}; // End of A_Matrix_Eigen Class

} // End of MATH Namespace
} // End of GEO  Namespace

#endif
