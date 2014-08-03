/**
 * @file    Options.cpp
 * @author  Marvin Smith
 * @date    8/2/2014
*/
#include "Options.hpp"

/**
 * @brief Set the Application Name
*/
void Options::Set_Application_Name( boost::filesystem::path const& application_name ){
    m_application_name = application_name;
}

/**
 * @brief Get the Application Name
*/
boost::filesystem::path Options::Get_Application_Name()const{
    return m_application_name;
}

