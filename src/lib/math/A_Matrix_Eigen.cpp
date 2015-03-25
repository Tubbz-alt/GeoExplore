/**
 * @file    A_Matrix_Eigen.cpp
 * @author  Marvin Smith
 * @date    3/23/2015
*/
#include "A_Matrix_Eigen.hpp"

// C++ Standard Libraries
#include <sstream>

namespace GEO{
namespace MATH{

/**
 * Constructor
*/
A_Matrix_Eigen::A_Matrix_Eigen()
 : m_matrix(0,0)
{
}

/**
 * Constructors
*/
A_Matrix_Eigen::A_Matrix_Eigen( const int& rows,
                                const int& cols )
 : m_matrix(rows,cols)
{
}

/**
 * Multiplication Operator
*/
A_Matrix_Eigen A_Matrix_Eigen::operator* ( A_Matrix_Eigen const& other )const{
    
    // Create output matrix
    A_Matrix_Eigen output;
    output.m_matrix = (m_matrix * other.m_matrix);
    
    return output;
}

/**
 * To Pretty String
*/
std::string A_Matrix_Eigen::ToPrettyString()const{

    std::stringstream sin;
    for( int r=0; r<Rows(); r++ ){
        for( int c=0; c<Cols(); c++ ){
            sin << m_matrix(r,c);
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

