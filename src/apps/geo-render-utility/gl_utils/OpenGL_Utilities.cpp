/**
 * @file    OpenGL_Utilities.cpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#include "OpenGL_Utilities.hpp"

// C++ Standard Libraries
#include <cstdlib>
#include <iostream>

namespace UTILS{
namespace GL{


/**
 * Constructor
*/
OpenGL_Camera::OpenGL_Camera()
 : m_class_name("OpenGL_Camera")
{
}


/**
 * Constructor
*/
OpenGL_Context::OpenGL_Context()
 : m_class_name("OpenGL_Context"),
   m_camera(OpenGL_Camera()),
   m_program_id(0),
   m_viewer_window(nullptr),
   m_viewer_window_size(GEO::A_Size<int>(2000,1000)),
   m_viewer_window_name("Geo-Explore Render Utility")
{
}


/**
 * Initialize the viewer
*/
void OpenGL_Context::Initialize_Viewer( Configuration_Options const& options )
{
    // Update default values
    m_viewer_window_name = options.Get_Viewer_Window_Name();
    m_viewer_window_size = GEO::A_Size<int>(options.Get_Viewer_Window_Size());

    // Initialise GLFW
	if( !glfwInit() )
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		std::exit(-1);
	}

    // Create the window hints
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


	// Open a window and create its OpenGL context
	m_viewer_window = glfwCreateWindow( m_viewer_window_size.Width(),
                                        m_viewer_window_size.Height(),
                                        m_viewer_window_name.c_str(),
                                        NULL,
                                        NULL );
	
    if( m_viewer_window == NULL ){
		std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials." << std::endl;
		glfwTerminate();
	    std::exit(-1);
    }
	glfwMakeContextCurrent(m_viewer_window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		std::exit(-1);
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode( m_viewer_window, GLFW_STICKY_KEYS, GL_TRUE);

}


/**
 * Finalize the Viewer
*/
void OpenGL_Context::Finalize_Viewer()
{
    // Close OpenGL window and terminate GLFW
	glfwTerminate();


}


} // End of GL    Namespace
} // End of UTILS Namespace

