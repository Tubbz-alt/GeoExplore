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



/**
 * MemoryResourceNotInitializedException
*/
MemoryResourceNotInitializedException::MemoryResourceNotInitializedException( const std::string& filename, 
                                                                              const int& lineNumber )
                                                                                  : m_filename(filename), 
                                                                                    m_lineNumber(lineNumber){}


/**
 * GeneralException Constructor
*/
GeneralException::GeneralException( std::string const& message,
                                    std::string const  filename,
                                    int const& lineNumber ) : 
                                               m_message(message),
                                               m_filename(filename),
                                               m_lineNumber(lineNumber){}


} /// End of GEO Namespace

