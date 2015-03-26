/**
 * @file    A_Status.hpp
 * @date    3/22/2015
 * @author  Marvin Smith
 */
#ifndef __GEOEXPLORE_LIB_CORE_A_STATUS_HPP__
#define __GEOEXPLORE_LIB_CORE_A_STATUS_HPP__
 
// GeoExplore Libraries
#include "Status_Enumerations.hpp"

// C++ Standard Libraries
#include <string>

namespace GEO{

/**
 * @class Status
*/
class Status{

    public:
        
        /**
         * @brief Constructor
        */
        Status();

        
        /**
         * @brief Constructor
         *
         * @param[in] status_type Status type code.
        */
        Status( StatusType  const& status_type );


        /**
         * @brief Constructor.
         *
         * @param[in] status_type Status type code.
         * @param[in] status_reason Status reason code.
         * @param[in] status_details Status string.
        */
        Status( StatusType    const& status_type, 
                StatusReason  const& status_reason, 
                std::string   const& status_details );

        /**
         * @brief Constructor
         *
         * @param[in] status_type Status type code.
         * @param[in] status_reason Status reason code.
         * @param[in] status_details Status details.
        */
        template< typename REASON>
        Status( StatusType  const& status_type,
                REASON      const& status_reason,
                std::string const& status_details )
          : m_status_type(status_type),
            m_status_reason(static_cast<StatusReason>(status_reason)),
            m_status_details(status_details)
        {
        }
        /**
         * @brief Get the status type.
        */
        StatusType Get_Status_Type()const;


        /**
         * @brief Get the status reason
        */
        StatusReason  Get_Status_Reason()const;


        /**
         * @brief Get the status details.
         *
         * @return Status details.
        */
        std::string Get_Status_Details()const;

    private:
        
        /// Status Type
        StatusType m_status_type;

        /// Status Reason
        StatusReason m_status_reason;

        /// Status Details
        std::string m_status_details;

}; // End of Status Class


} // End of GEO Namespace

#endif
