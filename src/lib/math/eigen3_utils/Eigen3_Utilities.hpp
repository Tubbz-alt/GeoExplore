/**
 * @file    Eigen3_Utilities.hpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#ifndef __GEOEXPLORE_LIB_MATH_EIGEN3_UTILS_EIGEN3_UTILITIES_HPP__
#define __GEOEXPLORE_LIB_MATH_EIGEN3_UTILS_EIGEN3_UTILITIES_HPP__

// Eigen Libraries
#include <Eigen/Dense>

// C++ Standard Libraries
#include <memory>


namespace GEO{
namespace MATH{
namespace EIGEN3{

/**
 * @class A_Matrix_Eigen_Impl
 *
 * Implementation for the Eigen matrix.  This is built to avoid 
 * requiring the user to include eigen in other applications.
*/
class A_Matrix_Eigen_Impl{

    public:

        /// Pointer Type
        typedef std::shared_ptr<A_Matrix_Eigen_Impl> ptr_t;
        
        /**
         * @brief Constructor.
         *
         * Builds a matrix with 0 rows and 0 columns.
        */
        A_Matrix_Eigen_Impl();


        /**
         * @brief Constructor
         *
         * @param[in] rows Number of matrix rows.
         * @param[in] cols Number of matrix cols.
         */
        A_Matrix_Eigen_Impl( const int& rows,
                             const int& cols );


        /**
         * @brief Get the number of rows.
         *
         * @return Number of rows.
        */
        inline int Rows()const{
            return m_matrix.rows();
        }

        
        /**
         * @brief Get the number of columns.
         *
         * @return Number of columns.
        */
        inline int Cols()const{
            return m_matrix.cols();
        }


        /// Eigen Matrix    
        Eigen::MatrixXd m_matrix;

    private:
        
        /// Class Name
        std::string m_class_name;

}; // End of A_Matrix_Eigen_Impl Class




} // End of EIGEN3 Namespace
} // End of MATH   Namespace
} // End of GEO    Namespace

#endif
