/**
 * @file    A_Matrix_Eigen.cpp
 * @author  Marvin Smith
 * @date    3/23/2015
*/
#include "A_Matrix_Eigen.hpp"

// C++ Standard Libraries
#include <sstream>

// GeoExplore Libraries
#include "eigen3_utils.hpp"


namespace GEO{
namespace MATH{

/***************************************/
/*              Constructor            */
/***************************************/
A_Matrix_Eigen::A_Matrix_Eigen()
 : m_class_name("A_Matrix_Eigen"),
   m_matrix(EIGEN3::A_Matrix_Eigen_Impl::ptr_t(new EIGEN3::A_Matrix_Eigen_Impl(0,0)))
{
}


/***************************************/
/*              Constructor            */
/***************************************/
A_Matrix_Eigen::A_Matrix_Eigen( const int& rows,
                                const int& cols )
 : m_class_name("A_Matrix_Eigen"),
   m_matrix(EIGEN3::A_Matrix_Eigen_Impl::ptr_t(new EIGEN3::A_Matrix_Eigen_Impl(rows,cols)))
{
}


/*************************************/
/*      Get the Number of Rows       */
/*************************************/
int A_Matrix_Eigen::Rows()const{
    return m_matrix->Rows();
}


/****************************************/
/*      Get the Number of Columns       */
/****************************************/
int A_Matrix_Eigen::Cols()const{
    return m_matrix->Cols();
}


/***************************************/
/*       Function Value Operator       */
/***************************************/
double A_Matrix_Eigen::operator()( const int& row,
                                   const int& col )const
{
    return m_matrix->m_matrix(row,col);
}


/*******************************************/
/*       Function Reference Operator       */
/*******************************************/
double& A_Matrix_Eigen::operator()( const int& row,
                                    const int& col )
{
    return m_matrix->m_matrix(row,col);
}


/*******************************************************/
/*              Multiplication Operator                */
/*******************************************************/
A_Matrix_Eigen A_Matrix_Eigen::operator* ( A_Matrix_Eigen const& other )const{
    
    // Create output matrix
    A_Matrix_Eigen output;
    output.m_matrix->m_matrix = (m_matrix->m_matrix * other.m_matrix->m_matrix);
    
    return output;
}


/*************************************************/
/*              To Pretty String                 */
/*************************************************/
std::string A_Matrix_Eigen::ToPrettyString()const{

    std::stringstream sin;
    for( int r=0; r<Rows(); r++ ){
        for( int c=0; c<Cols(); c++ ){
            sin << m_matrix->m_matrix(r,c);
            if( c <= (Cols()-1) ){ 
                sin << ", ";
            }
        } 
        sin << std::endl;
    }
    return sin.str();
}

} // End of MATH Namespace
} // End of GEO  Namespace

