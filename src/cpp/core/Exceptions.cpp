/**
 * @file    Exceptions.cpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#include "Exceptions.hpp"

namespace GEO{

/**
 * NotImplementedException Constructor
*/
NotImplementedException::NotImplementedException( std::string const& module,
                                                  std::string const& filename,
                                                  int const& lineNumber ) : 
                                                        m_module(module), 
                                                        m_filename(filename),
                                                        m_lineNumber(lineNumber){}


} /// End of GEO Namespace

