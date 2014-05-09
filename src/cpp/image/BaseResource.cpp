/**
 * @file    BaseResource.cpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#include "BaseResource.hpp"

namespace GEO{

/**
 * Get reference
*/
double BaseResource::operator[]const( const int& idx )const{
    throw NotImplmentedException("BaseResource::operator[]", __FILE__, __LINE__);
}

/**
 * Get reference
*/
double& BaseResource::operator[]( const int& idx )const{
    throw NotImplementedException("BaseResource::operator[]&", __FILE__, __LINE__);
}

} /// End of GEO Namespace
