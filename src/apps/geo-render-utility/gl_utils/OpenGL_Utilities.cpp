/**
 * @file    OpenGL_Utilities.cpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#include "OpenGL_Utilities.hpp"

// C++ Standard Libraries
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace UTILS{
namespace GL{


/**
 * Constructor
*/
OpenGL_Camera::OpenGL_Camera()
 : m_class_name("OpenGL_Camera"),
   m_camera_origin(0, 0, 4),
   m_camera_lookat(0, 0,   0),
   m_camera_axis(0, -1, 0)
{
}


/**
 * Set the Camera Position
*/
void OpenGL_Camera::Set_Camera_Position( glm::vec3 const& tile_position,
                                         float const&  camera_elevation )
{
    // set the camera lookat point
    m_camera_lookat = tile_position;

    // Set the camera origin
    m_camera_origin = tile_position;
    m_camera_origin[2] += camera_elevation;

}

/**
 * Update the Camera Transform
*/
glm::mat4 OpenGL_Camera::Update_Camera_Transform()
{
    return glm::lookAt( m_camera_origin, 
                        m_camera_lookat, // and looks at the origin
						m_camera_axis  // Head is up (set to 0,-1,0 to look upside-down)
                      );
}


/**
 * @brief Zoom the camera
 */
void OpenGL_Camera::Zoom( const float& distance )
{
    // Compute the direction of the camera 
    glm::vec3 principle_axis = glm::normalize(m_camera_lookat - m_camera_origin);

    // Add to origin
    m_camera_origin += distance * principle_axis;
}


/**
 * Pan the camera
*/
void OpenGL_Camera::Pan( const float& x_distance,
                         const float& y_distance )
{
    // Compute the direction of the camera
    glm::vec3 principle_axis = glm::normalize(m_camera_origin - m_camera_lookat);

    // Up axis
    glm::vec3 up_axis = glm::normalize(-1.0f * m_camera_axis);

    // Compute Result
    glm::vec3 right_axis = glm::normalize(glm::cross( up_axis, principle_axis ));
    
    // Add to origin and lookat
    glm::vec3 result = (y_distance * up_axis) + (x_distance * right_axis);
    m_camera_origin += result;
    m_camera_lookat += result;
}


/**
 * Pitch the camera
*/
void OpenGL_Camera::Pitch( const float& angle )
{
    
    // Compute the direction of the camera
    glm::vec3 principle_axis = glm::normalize(m_camera_origin - m_camera_lookat);

    // Up axis
    glm::vec3 up_axis = glm::normalize(-1.0f * m_camera_axis);

    // Compute Result
    glm::vec3 right_axis = glm::normalize(glm::cross( up_axis, principle_axis ));
    
    // Compute difference vector
    glm::vec3 axis = m_camera_origin - m_camera_lookat;

    // Rotate the difference vector
    glm::vec3 rotated_axis = glm::rotate( axis, angle, right_axis );
    
    // Compute the new offset
    glm::vec3 offset = axis - rotated_axis;

    // Add to the origin
    m_camera_origin += offset;
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
   m_viewer_window_name("Geo-Explore Render Utility"),
   m_field_of_view(45)
{
}


/**
 * Initialize the viewer
*/
void OpenGL_Context::Initialize_Viewer( Configuration_Options const& options )
{
    // Status
    Status status;

    // Make sure the data container is not null
    if( data_container == nullptr ){
        std::cerr << "error: Data container is null" << std::endl;
        std::exit(-1);
    }
    
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
    
    // Load the shaders
    status = Load_Shaders( options.Get_Vertex_Shader_Path(),
                           options.Get_Fragment_Shader_Path(),
                           this->m_program_id );

    if( status.Get_Status_Type() != StatusType::SUCCESS ){
        std::cerr << "Unable to load shaders. Details: " << status;
        std::exit(-1);
    }

    // Initialize the buffer data
    
    // Get the MVP handle
    m_model_view_id = glGetUniformLocation(m_program_id, "MVP");

    // Get the buffer handles
    m_vertex_position_model_space_id = glGetAttribLocation( m_program_id, "vertexPosition_modelspace");
    m_vertex_color_id = glGetAttribLocation( m_program_id, "vertexColor");
    
    // Get the tile center coordinate
    CRD::CoordinateUTM_d tile_center_coordinate = data_container->Get_Tile_Center();
    glm::vec3 tile_center( (float)tile_center_coordinate.easting_meters(),
                           (float)tile_center_coordinate.northing_meters(),
                           (float)tile_center_coordinate.altitude_meters());
    float camera_elevation = 500;
    m_camera.Set_Camera_Position( tile_center, camera_elevation );

    m_vertex_buffer_size = data_container->Get_Terrain_Buffer( m_terrain_data );
    m_color_buffer_size  = data_container->Get_Terrain_Color_Buffer( m_terrain_color_data );
    

    glGenBuffers(1, &m_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer );
	glBufferData(GL_ARRAY_BUFFER, m_vertex_buffer_size * sizeof(float), m_terrain_data, GL_STATIC_DRAW );

	glGenBuffers(1, &m_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_color_buffer_size * sizeof(float), m_terrain_color_data, GL_STATIC_DRAW);

    // Update the transform
    m_model_view_projection = Update_Projection(); 

}


/**
 * Update the projection
*/
glm::mat4 OpenGL_Context::Update_Projection(){
    
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(m_field_of_view, 4.0f / 3.0f, 0.1f, 1000.0f);
	
    // Camera matrix
	glm::mat4 View  = m_camera.Update_Camera_Transform();
   
    // Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	
    // Our ModelViewProjection : multiplication of our 3 matrices
	m_model_view_projection = Projection * View * Model; 

    return m_model_view_projection;
}


/**
 * Run the OpenGL Viewer.
*/
void OpenGL_Context::Run_Viewer()
{
    // Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	
    // Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
    
	do{
        
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(m_program_id);


		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv( m_model_view_id, 1, GL_FALSE, &m_model_view_projection[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(m_vertex_position_model_space_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer );
		glVertexAttribPointer(
			m_vertex_position_model_space_id, // The attribute we want to configure
			3,                           // size
			GL_FLOAT,                    // type
			GL_FALSE,                    // normalized?
			0,                           // stride
			(void*)0                     // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(m_vertex_color_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_color_buffer);
		glVertexAttribPointer(
			m_vertex_color_id,             // The attribute we want to configure
			3,                           // size
			GL_FLOAT,                    // type
			GL_FALSE,                    // normalized?
			0,                           // stride
			(void*)0                     // array buffer offset
		);

		// Draw the triangleS !
		glDrawArrays(GL_TRIANGLES, 0, m_vertex_buffer_size ); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray( m_vertex_position_model_space_id );
		glDisableVertexAttribArray( m_vertex_color_id );

		// Swap buffers
		glfwSwapBuffers(m_viewer_window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(m_viewer_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose( m_viewer_window ) == 0 );

}	



/**
 * Finalize the Viewer
*/
void OpenGL_Context::Finalize_Viewer()
{
    // Kill the VBO and shaders
    glDeleteBuffers( 1, &m_vertex_buffer );
    glDeleteBuffers( 1, &m_color_buffer );

    // Kill the OpenGL Program
    glDeleteProgram(m_program_id);

    // Close OpenGL window and terminate GLFW
	glfwTerminate();

    // Clear buffer data
    delete [] m_terrain_data;
    delete [] m_terrain_color_data;
}

/**
 * Load Shaders.
*/
Status Load_Shaders( FS::FilesystemPath const& vertex_shader_path,
                     FS::FilesystemPath const& fragment_shader_path,
                     GLuint& program_id )
{

    // Create the shaders
	GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_path.ToString().c_str(), std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		std::stringstream sin;
        sin << "Impossible to open " << vertex_shader_path.ToString() << ". Are you in the right directory.";
		return Status(StatusType::FAILURE, CoreStatusReason::PATH_DOES_NOT_EXIST, sin.str());
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_path.ToString().c_str(), std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}else{
		std::stringstream sin;
        sin << "Impossible to open " << fragment_shader_path.ToString() << ". Are you in the right directory.";
		return Status(StatusType::FAILURE, CoreStatusReason::PATH_DOES_NOT_EXIST, sin.str());
	}




	GLint Result = GL_FALSE;
	int InfoLogLength;



	// Compile Vertex Shader
	std::cout << "Compiling shader : " << vertex_shader_path.ToString() << std::endl;
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	program_id = glCreateProgram();
	glAttachShader(program_id, VertexShaderID);
	glAttachShader(program_id, FragmentShaderID);
	glLinkProgram(program_id);

	// Check the program
	glGetProgramiv(program_id, GL_LINK_STATUS, &Result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(program_id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
    
    // Destroy the temp shader ID.
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

    // Return Success
    return Status(StatusType::SUCCESS);
}



} // End of GL    Namespace
} // End of UTILS Namespace

