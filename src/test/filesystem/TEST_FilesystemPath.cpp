/**
 * @file    TEST_FilesystemPath.cpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#include <gtest/gtest.h>

// C++ Standard Libraries
#include <fstream>
#include <iostream>

// GeoExplore Libraries
#include <filesystem/FilesystemPath.hpp>
#include <utilities.hpp>

// Boost Libraries
#include <boost/filesystem.hpp>


using namespace GEO;

/**
 * Create the requested file
*/
void Create_File( std::string const& pathname )
{
    std::ofstream fout;
    fout.open(pathname.c_str());
    fout << "Hello World" << std::endl;
    fout.close();

}

/**
 * Create the requested directory.
*/
void Create_Directory( std::string const& pathname )
{
    boost::filesystem::create_directory(boost::filesystem::path(pathname));
}



/**
 * Test the default constructor
*/
TEST( FilesystemPath, Constructor_default )
{
    FS::FilesystemPath path;

    ASSERT_FALSE( path.Exists());
    ASSERT_FALSE( path.Is_Regular_File());
    ASSERT_FALSE( path.Is_Directory());
    ASSERT_EQ( path.Get_Extension().ToString(), "" );
    

}

/**
 * Test Constructor given string
*/
TEST( FilesystemPath, Constructor_string )
{

    // Test directory
    FS::FilesystemPath path01("src");

    ASSERT_TRUE( path01.Exists() );
    ASSERT_TRUE( path01.Is_Directory());
    ASSERT_FALSE( path01.Is_Regular_File() );
    ASSERT_EQ( path01.Get_Extension().ToString(), "" );

    // Test Invalid path
    FS::FilesystemPath path02("Filethatdoesnotexist.cpp");
    ASSERT_FALSE( path02.Exists() );
    ASSERT_FALSE( path02.Is_Directory());
    ASSERT_FALSE( path02.Is_Regular_File() );
    ASSERT_EQ( path02.Get_Extension().ToString(), ".cpp" );

    // Test Valid Path
    FS::FilesystemPath path03("CMakeLists.txt");
    ASSERT_TRUE( path03.Exists() );
    ASSERT_FALSE( path03.Is_Directory() );
    ASSERT_TRUE( path03.Is_Regular_File() );
    ASSERT_EQ( path03.Get_Extension().ToString(), ".txt");
}

/**
 * Test the Assignment Operators 
*/
TEST( FilesystemPath, Assignment_Operators )
{
    // TEST 01 (file to file)
    FS::FilesystemPath path01("test01.txt");
    FS::FilesystemPath path02("test02.txt");
    FS::FilesystemPath path03("test03.txt");

    ASSERT_EQ( path01.ToString(), "test01.txt");
    ASSERT_EQ( path02.ToString(), "test02.txt");
    ASSERT_EQ( path03.ToString(), "test03.txt");
    
    path01 = path02 = path03;

    ASSERT_EQ( path01.ToString(), "test03.txt");
    ASSERT_EQ( path02.ToString(), "test03.txt");
    ASSERT_EQ( path03.ToString(), "test03.txt");

    // TEST 02 (char to file to file)
    path01 = path02 = "test04.txt";
    ASSERT_EQ( path01.ToString(), "test04.txt");
    ASSERT_EQ( path02.ToString(), "test04.txt");
    
    // TEST 03 (string to file to file)
    path01 = path02 = std::string("test05.txt");
    ASSERT_EQ( path01.ToString(), "test05.txt");
    ASSERT_EQ( path02.ToString(), "test05.txt");
    
    // TEST 04 (boost path to file to file)
    path01 = path02 = boost::filesystem::path("test06.txt");
    ASSERT_EQ( path01.ToString(), "test06.txt");
    ASSERT_EQ( path02.ToString(), "test06.txt");

}


/**
 * Test the Less-Than Operator
*/
TEST( FilesystemPath, Less_Than_Operator ){

    ASSERT_FALSE( FS::FilesystemPath("./foo") < FS::FilesystemPath("./foo"));
    ASSERT_TRUE( FS::FilesystemPath("./foo") < FS::FilesystemPath("./foo1"));
    ASSERT_TRUE( FS::FilesystemPath("bar") < FS::FilesystemPath("foo"));
    ASSERT_FALSE( FS::FilesystemPath("foo") < FS::FilesystemPath("bar"));

}

/**
 * Test the Equivalent Operators 
*/
TEST( FilesystemPath, Equivalent_Operators)
{

    // Path List
    FS::FilesystemPath path01("path01.txt");
    FS::FilesystemPath path02("path02.txt");
    FS::FilesystemPath path03("path02.txt");
    FS::FilesystemPath path04("path03.txt");
    FS::FilesystemPath path05("./path03.txt");
    FS::FilesystemPath path06("./../path03.txt");
    FS::FilesystemPath path07 = FS::FilesystemPath::Get_Current_Path().Append(path04);
    FS::FilesystemPath path08 = FS::FilesystemPath::Get_Current_Path().Append(path05);
    FS::FilesystemPath path09 = FS::FilesystemPath::Get_Current_Path().Append(path06);

    // TEST 01 (two invalid paths)
    ASSERT_FALSE( path01 == path02 );

    // TEST 02 (two same paths)
    ASSERT_TRUE( path01 == path01 );
    ASSERT_TRUE( path02 == path02 );
    ASSERT_TRUE( path03 == path03 );
    ASSERT_TRUE( path02 == path03 );
    ASSERT_TRUE( path03 == path02 );

    // TEST 03 (absolute vs relative path [same])
    ASSERT_FALSE( path05 == path07 );
    ASSERT_FALSE( path05 == path08 );
    ASSERT_FALSE( path07 == path08 );
    ASSERT_FALSE( path09 == path08 );
    ASSERT_FALSE( path08 == path09 );
    ASSERT_FALSE( path09 == path07 );
    ASSERT_FALSE( path07 == path09 );

    ASSERT_TRUE( FS::FilesystemPath("CMakeLists.txt") == FS::FilesystemPath::Get_Current_Path().Append("CMakeLists.txt"));


}

/**
 * Get the basename
*/
TEST( FilesystemPath, Get_Basename )
{

    // Get our current parent directory
    std::string system_parent = getenv("PWD");
    std::string system_base_path = string_trim(System_Call(std::string("basename ") + system_parent));

    // Test against parent
    ASSERT_EQ( FS::FilesystemPath::Get_Current_Path().Append("file.txt").Get_Basename().ToString(), "file.txt");
    ASSERT_EQ( FS::FilesystemPath("hello/world.txt").Get_Basename().ToString(), "world.txt");
    ASSERT_EQ( FS::FilesystemPath("hello/there/world.txt").Get_Basename().ToString(), "world.txt");

}

/**
 * Get the parent
*/
TEST( FilesystemPath, Get_Parent ){

    // Get our current parent directory
    std::string system_parent = getenv("PWD");
    std::string system_base_path = string_trim(System_Call(std::string("basename ") + system_parent));

    // Test against parent
    ASSERT_EQ( FS::FilesystemPath::Get_Current_Path().Append("file.txt").Get_Parent().ToString(), system_parent);
    ASSERT_EQ( FS::FilesystemPath("hello/world.txt").Get_Parent().ToString(), "hello");
    ASSERT_EQ( FS::FilesystemPath("hello/there/world.txt").Get_Parent().ToString(), "hello/there");

}


/**
 * Test the append method
*/
TEST( FilesystemPath, Append ){
    
    // Create some paths
    FS::FilesystemPath path01("foo");
    FS::FilesystemPath path02("bar");
    ASSERT_EQ( path01.Append(path02).ToString(), "foo/bar");

}

/**
 * Test the relative method
*/
TEST( FilesystemPath, Get_Relative )
{

    // Get the current path
    FS::FilesystemPath cwd = FS::FilesystemPath::Get_Current_Path();
    
    // Get our expected value
    std::string exp_value = cwd.Append("CMakeLists.txt").ToString();
    exp_value = exp_value.substr(1,exp_value.size()-1);

    // Check
    ASSERT_EQ( exp_value, cwd.Append("CMakeLists.txt").Get_Relative().ToString() );
    ASSERT_EQ( FS::FilesystemPath("./CMakeLists.txt").ToString(), "./CMakeLists.txt");
}


/**
 * Test the canonical method
*/
TEST( FilesystemPath, Get_Canonical )
{

    // Get the current path
    FS::FilesystemPath cwd = FS::FilesystemPath::Get_Current_Path();
    
    // Get our expected value
    std::string exp_value = cwd.Append("CMakeLists.txt").ToString();

    // Create test paths
    FS::FilesystemPath test01("CMakeLists.txt");
    FS::FilesystemPath test02("src/../CMakeLists.txt");
    FS::FilesystemPath test03 = cwd.Append("src/../CMakeLists.txt");

    // Test 
    ASSERT_EQ( test01.Get_Canonical().ToString(), exp_value);
    ASSERT_EQ( test02.Get_Canonical().ToString(), exp_value);
    ASSERT_EQ( test03.Get_Canonical().ToString(), exp_value);

}

/**
 * Test the Get-Contents Method
*/
TEST( FilesystemPath, Get_Contents ){
    
    // Get the Current Working Directory
    FS::FilesystemPath cwd = FS::FilesystemPath::Get_Current_Path();

    //////////////////////////////////////////////////
    //    TEST 01 (Bad path - Does not exist)
    FS::FilesystemPath path01("paththatdoesnotexist");

    // Make sure returned path list is empty
    std::vector<FS::FilesystemPath> results_01 = path01.Get_Contents();
    ASSERT_EQ( results_01.size(), 0 );

    /////////////////////////////////////////////////
    //    TEST 02 (File - Should return empty)
    FS::FilesystemPath path02("src/lib/CMakeLists.txt");

    // Make sure returned path list is empty
    std::vector<FS::FilesystemPath> results_02 = path02.Get_Contents();
    ASSERT_EQ( results_02.size(), 0 );

    //    TEST 03 (Directory - All files, not recursive, relative )
    FS::FilesystemPath path03 = cwd.Append("data/unit-tests/filesystem-test");

    // Make sure the list returns 5 items
    std::vector<FS::FilesystemPath> results_03 = path03.Get_Contents(".*", false, FS::PathFormatType::RELATIVE);
    ASSERT_EQ( results_03.size(), 5 );
    ASSERT_EQ( results_03[0].ToString(), "dir01");
    ASSERT_EQ( results_03[1].ToString(), "dir02");
    ASSERT_EQ( results_03[2].ToString(), "dir03");
    ASSERT_EQ( results_03[3].ToString(), "file01.txt" );
    ASSERT_EQ( results_03[4].ToString(), "file02.txt" );

    //    TEST 04 (Directory - All files, not recursive, absolute )
    std::vector<FS::FilesystemPath> results_04 = path03.Get_Contents(".*", false, FS::PathFormatType::ABSOLUTE);
    ASSERT_EQ( results_04.size(), 5 );
    ASSERT_EQ( results_04[0].ToString(), cwd.ToString() + "/data/unit-tests/filesystem-test/dir01");
    ASSERT_EQ( results_04[1].ToString(), cwd.ToString() + "/data/unit-tests/filesystem-test/dir02");
    ASSERT_EQ( results_04[2].ToString(), cwd.ToString() + "/data/unit-tests/filesystem-test/dir03");
    ASSERT_EQ( results_04[3].ToString(), cwd.ToString() + "/data/unit-tests/filesystem-test/file01.txt" );
    ASSERT_EQ( results_04[4].ToString(), cwd.ToString() + "/data/unit-tests/filesystem-test/file02.txt" );


    // TEST 05 (Directory - pattern [.txt] , recursive, relative)    
    std::vector<FS::FilesystemPath> results_05 = path03.Get_Contents(".*\\.txt", true, FS::PathFormatType::RELATIVE);
    ASSERT_EQ( results_05.size(), 4 );
    ASSERT_EQ( results_05[0].ToString(), "file01.txt" );
    ASSERT_EQ( results_05[1].ToString(), "file02.txt" );
    ASSERT_EQ( results_05[2].ToString(), "file03.txt" );
    ASSERT_EQ( results_05[3].ToString(), "file10.txt" );

    //    TEST 04 (Directory - pattern [..jpg], recursive, absolute )
    std::vector<FS::FilesystemPath> results_06 = path03.Get_Contents(".*\\.jpg", true, FS::PathFormatType::ABSOLUTE);
    ASSERT_EQ( results_06.size(), 2 );
    ASSERT_EQ( results_06[0].ToString(), cwd.ToString() + "/data/unit-tests/filesystem-test/dir02/file06.jpg");
    ASSERT_EQ( results_06[1].ToString(), cwd.ToString() + "/data/unit-tests/filesystem-test/dir03/file07.jpg");


}

/**
 * Test the Get Current Directory
*/
TEST( FilesystemPath, Get_Current_Path ){

    // Get the current path
    std::string system_cwd = getenv("PWD");
    FS::FilesystemPath exp_path(system_cwd);
    FS::FilesystemPath act_path = FS::FilesystemPath::Get_Current_Path();
    ASSERT_TRUE( exp_path == act_path );
}

/**
 * Test the Delete Method
*/
TEST( FilesystemPath, Delete )
{
    
    // Status
    Status status;

    // TEST 01 (Delete file that does not exist.)
    FS::FilesystemPath test01("path-that-does-not-exist.txt");
    status = test01.Delete();
    ASSERT_EQ( status.Get_Status_Type(), StatusType::FAILURE );
    ASSERT_EQ( (int)status.Get_Status_Reason(), static_cast<int>(CoreStatusReason::PATH_DOES_NOT_EXIST) );

    // TEST 02 (Delete file that does exist.)
    FS::FilesystemPath test02("test02-file.txt");
    Create_File( test02.ToString() );

    // Make sure file exists
    ASSERT_TRUE( test02.Exists() );
    status = test02.Delete();
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    ASSERT_FALSE( test02.Exists() );

    // TEST 03 (Delete Directory)
    FS::FilesystemPath test03("test03-directory");
    Create_Directory( test03.ToString() );
    Create_File( test03.Append("file.txt").ToString() );
    ASSERT_TRUE( test03.Exists() );
    status = test03.Delete();
    ASSERT_EQ( status.Get_Status_Type(), StatusType::FAILURE );
    ASSERT_EQ( (int)status.Get_Status_Reason(), static_cast<int>(CoreStatusReason::PATH_UNABLE_TO_DELETE) );
    ASSERT_TRUE( test03.Exists() );
    test03.Delete_All();
    ASSERT_FALSE( test03.Exists() );
    
}


/**
 * Test the Delete Method
*/
TEST( FilesystemPath, Delete_All )
{
    // Status
    Status status;

    // TEST 01 (Delete file that does not exist.)
    FS::FilesystemPath test01("path-that-does-not-exist.txt");
    status = test01.Delete_All();
    ASSERT_EQ( status.Get_Status_Type(), StatusType::FAILURE );
    ASSERT_EQ( (int)status.Get_Status_Reason(), static_cast<int>(CoreStatusReason::PATH_DOES_NOT_EXIST) );

    // TEST 02 (Delete file that does exist.)
    FS::FilesystemPath test02("test02-file.txt");
    Create_File( test02.ToString() );

    // Make sure file exists
    ASSERT_TRUE( test02.Exists() );
    status = test02.Delete_All();
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    ASSERT_FALSE( test02.Exists() );

    // TEST 03 (Delete Directory)
    FS::FilesystemPath test03("test03-directory");
    Create_Directory( test03.ToString() );
    Create_File( test03.Append("file.txt").ToString() );
    ASSERT_TRUE( test03.Exists() );
    status = test03.Delete_All();
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    ASSERT_FALSE( test03.Exists() );
}


