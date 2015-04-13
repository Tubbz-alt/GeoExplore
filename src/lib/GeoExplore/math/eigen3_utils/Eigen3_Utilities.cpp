/**
 * @file    Eigen3_Utilities.cpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#include "Eigen3_Utilities.hpp"

namespace GEO{
namespace MATH{
namespace EIGEN3{


/********************************/
/*         Constructor          */
/********************************/
A_Matrix_Eigen_Impl::A_Matrix_Eigen_Impl()
  : m_matrix(0,0),
    m_class_name("A_Matrix_Eigen_Impl")
{
}



/********************************/
/*         Constructor          */
/********************************/
A_Matrix_Eigen_Impl::A_Matrix_Eigen_Impl( const int& rows,
                                          const int& cols )
  : m_matrix(rows,cols),
    m_class_name("A_Matrix_Eigen_Impl")
{
}





} // End of EIGEN3 Namespace
} // End of MATH   Namespace
} // End of GEO    Namespace

