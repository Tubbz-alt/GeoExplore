/**
 * @file    TEST_MetadataContainer.cpp
 * @author  Marvin Smith
 * @date    3/5/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/image/MetadataContainer.hpp>

using namespace GEO;


/*******************************************/
/*      Test the Metadata Constructor      */
/*******************************************/
TEST( MetadataContainer, Constructors )
{

    // TEST 01 (Empty Metadata Container)
    IMG::MetadataContainer container01;
    ASSERT_EQ( container01.Get_Metadata_List().size(), 0 );

}
   
/********************************************************/
/*            Test the Add Metadata Entry Method        */
/********************************************************/
TEST( MetadataContainer, Add_Metadata_Entry )
{
    // Create list
    IMG::MetadataContainer container;
    
    // Test 01 (Add string set)
    container.Add_Metadata_Entry("CORNER_TL_X", "120");
    ASSERT_EQ( container.Get_Metadata_List().size(), 1 );

}

/*******************************************/
/*          Test the Clear Method          */
/*******************************************/
TEST( MetadataContainer, Clear )
{
    // Create list
    IMG::MetadataContainer container;
    
    // Test 01 (Add string set)
    container.Add_Metadata_Entry("CORNER_TL_X", "120");
    container.Add_Metadata_Entry("CORNER_TL_Y", "130");
    ASSERT_EQ( container.Get_Metadata_List().size(), 2 );
    
    container.Clear();
    ASSERT_EQ( container.Get_Metadata_List().size(), 0 );


}

/********************************************************/
/*             Test the Query Metadata Value            */
/********************************************************/
TEST( MetadataContainer, Query_Metadata_Value )
{
    // Variables
    std::string value_str;
    double value_dbl;

    // Create Container
    IMG::MetadataContainer container;

    // TEST 01 (Query value in empty container)
    ASSERT_FALSE( container.Query_Metadata("CORNER_TL_X", value_str));
    ASSERT_FALSE( container.Query_Metadata("CORNER_TL_X", value_dbl));


}
