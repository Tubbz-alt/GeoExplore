/**
 * @file    OpenGL_Utilities.hpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#ifndef __GEOEXPLORE_APPS_GEO_RENDER_UTILITY_GL_UTILS_OPENGL_UTILITIES_HPP__
#define __GEOEXPLORE_APPS_GEO_RENDER_UTILITY_GL_UTILS_OPENGL_UTILITIES_HPP__

// C++ Standard Libraries
#include <string>

// OpenGL
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GeoExplore Libraries
#include "../../../lib/core.hpp"

// Render Utility Libraries
#include "../core/Configuration_Options.hpp"


namespace UTILS{
namespace GL{

/**
 * @class OpenGL_Camera
*/
class OpenGL_Camera{

    public:
        
        /**
         * @brief Constructor
        */
        OpenGL_Camera();


    private:
        
        /// Class Name
        std::string m_class_name;


}; // End of OpenGL_Camera

/**
 * @class OpenGL_Context
*/
class OpenGL_Context{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<OpenGL_Context> ptr_t;
    
        /**
         * @brief Constructor
        */
        OpenGL_Context();

        /**
         * @brief Initialize OpenGL and GLFW
        */
        void Initialize_Viewer( Configuration_Options const& options );
        
        /**
         * @brief Finalize the OpenGL Viewer
        */
        void Finalize_Viewer();

        /**
         * Get the GLFX Window
        */
        inline GLFWwindow* Get_GLFW_Window()const{
            return m_viewer_window;
        }


    private:
        
        /// Class Name
        std::string m_class_name;

        /// Camera
        OpenGL_Camera m_camera;

        /// Program ID
        GLuint m_program_id;
        
        /// GLFW Window
        GLFWwindow* m_viewer_window;

        /// GLFW Window Size
        GEO::A_Size<int> m_viewer_window_size;

        /// GLFW Window Name
        std::string m_viewer_window_name;
        

}; // End of OpenGL_Context Class

} // End of GL    Namespace
} // End of UTILS Namespace

#endif

