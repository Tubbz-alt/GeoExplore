/**
 * @file    A_Status.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include "A_Status.hpp"

namespace GEO{

/**
 * Status Constructor
*/
Status::Status( StatusType  const& status_type )
  : m_status_type(status_type),
    m_status_reason(StatusReason::NO_ERROR),
    m_status_details("")
{
}


/**
 * Constructor
*/
Status::Status( StatusType   const& status_type, 
                StatusReason const& status_reason,
                std::string const&  status_details )
  : m_status_type(status_type),
    m_status_reason(status_reason),
    m_status_details(status_details)
{

}

/**
 * Get the status type
*/
StatusType Status::Get_Status_Type()const{
    return m_status_type;
}

/**
 * Get the status reason
*/
StatusReason Status::Get_Status_Reason()const{
    return m_status_reason;
}


/**
 * Get the status details
*/
std::string Status::Get_Status_Details()const{
    return m_status_details;
}



} // End of GEO Namespace

