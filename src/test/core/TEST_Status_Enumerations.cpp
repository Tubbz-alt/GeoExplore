/**
 * @file    TEST_Status_Enumerations.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/core/Status_Enumerations.hpp"

using namespace GEO;

/**
 * Test the status types 
*/
TEST( StatusType, values ){

    ASSERT_EQ( static_cast<uint16_t>(StatusType::SUCCESS), 0 );
    ASSERT_EQ( static_cast<uint16_t>(StatusType::WARNING), 1 );
    ASSERT_EQ( static_cast<uint16_t>(StatusType::FAILURE), 2 );

}


/** 
* Test the status reason
*/
TEST( StatusReason, values ){

    ASSERT_EQ( static_cast<uint32_t>(StatusReason::NO_ERROR), 0 );
    ASSERT_EQ( static_cast<uint32_t>(CoreStatusReason::UNKNOWN), 1 );
    ASSERT_EQ( static_cast<uint32_t>(CoreStatusReason::UNINITIALIZED), 2 );
    ASSERT_EQ( static_cast<uint32_t>(CoreStatusReason::PATH_DOES_NOT_EXIST), 3 );
}


