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
using namespace GEO;


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
 * @brief GLFW Keyboard Callback Handler.
 *
 * @param[in] window Window to manage.
 * @param[in] key Keyboard key pressed.
 * @param[in] scancode
 * @param[in] action
 * @param[in] mods
*/
void Keyboard_Callback( GLFWwindow* window, 
                        int key, 
                        int scancode, 
                        int action, 
                        int mods );

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

    // Set the callback
    glfwSetKeyCallback( gl_context->Get_GLFW_Window(),
                        Keyboard_Callback);
}


/**
 * Run the render program
*/
void Run_Render_Program()
{

    gl_context->Run_Viewer(); 
}


/**
 * Finalize OpenGL COntext
*/
void Finalize_Context()
{

    // Close up
    gl_context->Finalize_Viewer();

}


/**
 * Keyboard Callback
*/
void Keyboard_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    const float horizontal_distance = 100;
    const float zoom_distance = 100;

    // Zoom out
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        gl_context->Get_Camera().Zoom(-zoom_distance);
        gl_context->Update_Projection();
    }

    // Zoom In
    if( key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        gl_context->Get_Camera().Zoom(zoom_distance);
        gl_context->Update_Projection();
    }

    // Pan Left
    if( key == GLFW_KEY_LEFT && action == GLFW_PRESS )
    {
        gl_context->Get_Camera().Pan( horizontal_distance, 0);
        gl_context->Update_Projection();
    }
    
    // Pan Right
    if( key == GLFW_KEY_RIGHT && action == GLFW_PRESS )
    {
        gl_context->Get_Camera().Pan( -horizontal_distance, 0);
        gl_context->Update_Projection();
    }
    
    // Pan Up
    if( key == GLFW_KEY_UP && action == GLFW_PRESS )
        gl_context->Get_Camera().Pan( 0,horizontal_distance);
        gl_context->Update_Projection();
    {
    }
    
    // Pan Down
    if( key == GLFW_KEY_DOWN && action == GLFW_PRESS )
    {
        gl_context->Get_Camera().Pan( 0, -horizontal_distance);
        gl_context->Update_Projection();
    }

    // Pitch Up
    if(key == GLFW_KEY_W && action == GLFW_PRESS )
    {
        gl_context->Get_Camera().Pitch(0.2);
        gl_context->Update_Projection();
    }
    
    // Pitch Down
    if(key == GLFW_KEY_S && action == GLFW_PRESS )
    {
        gl_context->Get_Camera().Pitch(-0.2);
        gl_context->Update_Projection();
    }

    // Yaw Left
    if( key == GLFW_KEY_A && action == GLFW_PRESS )
    {
        gl_context->Get_Camera().Yaw(-0.1);
        gl_context->Update_Projection();
    }

    // Yaw Right
    if( key == GLFW_KEY_D && action == GLFW_PRESS )
    {
        gl_context->Get_Camera().Yaw(0.1);
        gl_context->Update_Projection();
    }
    
    // Roll Left
    if( key == GLFW_KEY_J && action == GLFW_PRESS )
    {
        gl_context->Get_Camera().Roll(-0.1);
        gl_context->Update_Projection();
    }

    // Roll Right
    if( key == GLFW_KEY_L && action == GLFW_PRESS )
    {
        gl_context->Get_Camera().Roll(0.1);
        gl_context->Update_Projection();
    }


}



