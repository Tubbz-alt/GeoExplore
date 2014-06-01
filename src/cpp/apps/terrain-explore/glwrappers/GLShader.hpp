/**
 * @file    GLShader.hpp
 * @author  Josh Gleason
 * @date    5/31/2013
 */

#ifndef __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLSHADER_HPP
#define __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLSHADER_HPP

// Include OpenGL and some standard headers
#include <GL/glew.h>
#include <memory>
#include <string>

/**
 * @brief This class is responsible for managing an OpenGL shader.
 */
class GLShader
{
public:
    /**
     * @brief Default constructor.
     */
    GLShader();

    /**
     * @brief Destructor.
     *
     * If this object contains the last instance of the shader, then it is flagged for deletion.
     */
    ~GLShader();

    /**
     * @brief Compile a shader from a file.
     * @param filename The path to the shader source code.
     * @param shaderType The type of shader to compile, one of the following:
     *   GL_VERTEX_SHADER,
     *   GL_FRAGMENT_SHADER,
     *   GL_GEOMETRY_SHADER,
     *   GL_TESS_CONTROL_SHADER,
     *   GL_TESS_EVALUATION_SHADER
     * @return True on success, false on failure. To get error log use GLShader::getLastError
     */
    bool compileFromFile(const char* filename, GLenum shaderType);

    /**
     * @brief Get compile error as a string. Only useful if GLShader::compileFromFile fails.
     * @return A string containing the most recent compile error.
     */
    const std::string& getLastError() const;
    
protected:
    /// String containing the most recent error.
    std::string m_err;

    /// The shader index
    std::shared_ptr<GLuint> m_shader;

    /// The type of shader
    GLenum m_type;

    /// Give access to GLProgram class.
    friend class GLProgram;
};

#endif // __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLSHADER_HPP

