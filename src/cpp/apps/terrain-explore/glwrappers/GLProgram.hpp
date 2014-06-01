/**
 * @file    Program.hpp
 * @author  Josh Gleason
 * @date    5/31/2014
 */

#ifndef __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLPROGRAM_HPP
#define __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLPROGRAM_HPP

#include <GL/glew.h>
#include <memory>
#include <string>
#include <map>

// Forward declaration of class GLShader
class GLShader;

/**
 * @brief This class is resposible for managing an OpenGL program object.
 */
class GLProgram
{
public:
    /// String which holds GLchar type
    typedef std::basic_string<GLchar> GLstring;
    
    /**
     * @brief Constructor of GLProgram
     */
    GLProgram();

    // Default copy constructor is sufficient

    /**
     * @brief Destructor.
     * 
     * If this object holds the last instance of the program, then the program is flagged for deletion.
     */
    ~GLProgram();

    /**
     * @brief Assignment operator. Deletes current program if reference count drops to zero.
     * @param rhs The right hand side argument to be copied.
     * @return Returns *this
     */
    GLProgram& operator=(const GLProgram &rhs);

    /**
     * @brief Initialize the class by creating a new program shader program.
     */
    void init();

    /**
     * @brief Attach a shader to the program. Only works if program is not linked.
     * @param shader A compiled shader.
         * @return If true then shader was attached successfully. Call GLProgram::getLastError if
     *         false.
     */
    bool attachShader(const GLShader &shader);
    
    /**
     * @brief Detach a shader from the program. Only works if program is not linked.
     * @param shader A compiled shader that is attached to the program.
     * @return If true then shader was detached successfully. Call GLProgram::getLastError if
     *         false.
     */
    bool detachShader(const GLShader &shader);

    // bind attribute locations must be done before linking
    /**
     * @brief Bind attribute to particular location. Must be done before linking.
     * @param     name The name of the attribute.
     * @param location The desired location index. Must be in range [0,GL_MAX_VERTEX_ATTRIBS-1]
     * @return If true then attribute was bound. If false, call GLProgram::getLastError to
     *         retreive error information.
     */
    bool bindAttributeLocation(const GLstring& name, GLuint location);

    /**
     * @brief Link the program.
     * @return If true then program successfully linked. If false, call GLProgram::getLastError
     *         to retreive error information.
     *
     * Must be called after a vertex and fragment shader are attached. GLProgram::use can
     * not be used until after the program is linked.
     */
    bool link();

    /**
     * @brief Return the most recent error.
     * @return String describing most recent error associated with this object.
     */
    const std::string& getLastError() const;

    /**
     * @brief Make this program the current OpenGL program.
     */
    void use();

    /**
     * @brief Static utility function which sets current program to nothing'
     */
    static void resetUsed();

    /**
     * @brief Query the shader for the uniform location.
     * @param name The name of the uniform.
     * @return The index of the uniform. If -1 then uniform was not found.
     */
    GLint getUniformLocation(const GLstring& name);

    /**
     * @brief Query the shader for the attribute location.
     * @param name The name of the attribute.
     * @return The index of the attribute. If -1 then attribute was not found.
     */
    GLint getAttributeLocation(const GLstring& name);

    /**
     * @brief Gets the program's OpenGL index. Should only be used for debugging.
     * @return The OpenGL program index.
     */
    GLuint getProgramIdx() const;
protected:
    /// The container type for attributes and uniforms.
    typedef std::map<GLstring,GLint> StringMap;

    /// The index of the OpenGL program.
    std::shared_ptr<GLuint> m_program;

    /// The string message containing the most recent error message.
    std::string m_err;

    /// Partial list of attributes which are updated as needed. Makes looking up
    /// attribute locations by name faster.
    std::shared_ptr<StringMap> m_attributes;
    /// Partial list of uniform which are updated as needed. Makes looking up
    /// uniform locations by name faster.
    std::shared_ptr<StringMap> m_uniforms;

    /// Flag keeping track of link status.
    bool m_linked;
};

#endif // __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLPROGRAM_HPP

