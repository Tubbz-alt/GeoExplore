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

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

// GeoExplore Libraries
#include "../../../lib/core.hpp"

// Render Utility Libraries
#include "../core/Configuration_Options.hpp"
#include "../core/Data_Container.hpp"


// Global data container instance
extern Data_Container::ptr_t data_container;


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

        
        /**
         * @brief Set the Camera Position
         *
         * @param[in] data_center Center of the image.
         * @param[in] camera_elevation Elevation of the camera
         */
        void Set_Camera_Position( glm::vec3 const& tile_center, float const& camera_elevation );


        /**
         * @brief Update the Camera Transform.
         *
         * @return Updated Camera Transform.
         */
        glm::mat4 Update_Camera_Transform();
        

        /**
         * @brief Zoom the Camera
         *
         * @param[in] distance Distance to zoom the camera
        */
        void Zoom( const float& distance );
        

        /**
         * @brief Pan the Camera
         *
         * @param[in] x_distance X Distance to move.
         * @param[in] y_distance Y Distance to move.
         */
        void Pan( const float& x_distance,
                  const float& y_distance );


        /**
         * @brief Pitch the camera.
         *
         * @param[in] Rotation angle.
        */
        void Pitch( const float& pitch_angle );


    private:
        
        /// Class Name
        std::string m_class_name;

        /// Camera Origin
        glm::vec3 m_camera_origin;

        /// Camera Look-At Point
        glm::vec3 m_camera_lookat;

        /// Camera Axis
        glm::vec3 m_camera_axis;


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
         * @brief Run the OpenGL Viewer.
        */
        void Run_Viewer();


        /**
         * @brief Update the Projection
         *
         * @return Updated Camera Projection.
         */
        glm::mat4 Update_Projection();


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
        

        /**
         * @brief Get the Camera
         *
         * @return OpenGL Camera Reference
        */
        inline OpenGL_Camera& Get_Camera(){
            return m_camera;
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
        
        /// Color Buffer
        GLuint m_color_buffer;

        /// Color Buffer Size
        GLuint m_color_buffer_size;

        /// Vertex Buffer
        GLuint m_vertex_buffer;
        
        /// Vertex Buffer Size
        int m_vertex_buffer_size;

        /// Model View ID
        GLuint m_model_view_id;
        
        /// Model View Projection
        glm::mat4 m_model_view_projection;
    
        /// Vertex Position ID
        GLuint m_vertex_position_model_space_id;

        /// Vertex Color ID
        GLuint m_vertex_color_id;

        /// Vertex and Color Data
        float* m_terrain_data;
        float* m_terrain_color_data;

        /// Field of View
        float m_field_of_view;

}; // End of OpenGL_Context Class




/**
 * @brief Load Shaders into Memory
 *
 * @param[in] vertex_shader_path File path to vertex shader.
 * @param[in] fragement_shader_path File path to fragment shader.
 * @param[out] program_id OpenGL Program ID.
 *
 * @return Status of the operation.
*/
Status Load_Shaders( FS::FilesystemPath const& vertex_shader_path,
                     FS::FilesystemPath const& fragment_shader_path,
                     GLuint& program_id );


} // End of GL    Namespace
} // End of UTILS Namespace

#endif

