/**
 * @file    geo-render-utility.cpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/

// C++ Standard Libraries
#include <iostream>

// Render Utility Libraries
#include "core/Configuration_Options.hpp"
#include "core/Data_Container.hpp"
#include "gl_utils/OpenGL_Utilities.hpp"

// Create a Context Instance
UTILS::GL::OpenGL_Context::ptr_t gl_context;

// Create a data container instance
Data_Container::ptr_t data_container;

using namespace std;


/**
 * Initialize the OpenGL Context
*/
void Initialize_Context( Configuration_Options const& options );

/**
 * Run the Main Program
*/
void Run_Render_Program();

/**
 * Finalize OpenGL Context
*/
void Finalize_Context();


/**
 * Main Function
*/
int main( int argc, char* argv[] )
{
    
    // Parse the Command-Line Options
    Configuration_Options options;
    options.Initialize( argc, argv );
    
    // Load Data
    data_container = Data_Container::ptr_t(new Data_Container());
    data_container->Load_Data(options);
    
    // Initialize the Context
    Initialize_Context( options );
    
    // Run main program
    Run_Render_Program();

    // Finalize the Context
    Finalize_Context();

    return 0;
}


/**
 * Initialize the OpenGL Context
*/
void Initialize_Context( Configuration_Options const& options )
{

    // Create the context
    gl_context.reset(new UTILS::GL::OpenGL_Context());

    // Initialize
    gl_context->Initialize_Viewer( options );

}


/**
 * Run the render program
*/
void Run_Render_Program()
{
    // Start main loop
    do{




    }
	while( glfwGetKey(gl_context->Get_GLFW_Window(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(gl_context->Get_GLFW_Window()) == 0 );

}


/**
 * Finalize OpenGL COntext
*/
void Finalize_Context()
{

    // Close up
    gl_context->Finalize_Viewer();

}

