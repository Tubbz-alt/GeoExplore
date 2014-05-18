/**
 * @file    GLAttributes.hpp
 * @author  Josh Gleason
 * @date    5/18/2014
 */

#ifndef __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLATTRIBUTE_HPP
#define __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLATTRIBUTE_HPP

// Include OpenGL
#include <GL/glew.h>

// Local Dependencies
#include "GLProgram.hpp"

/**
 * @brief The GLAttribute class is responsible for managing an OpenGL attribute.
 */
class GLAttribute
{
public:
    /**
     * @brief   Default Constructor
     * @param   pos     Optionally initialize the attribute with its index. If this
     *                  parameter is a valid index then \ref init and
     *                  \ref tellLocation don't need to be called.
     */
    GLAttribute(GLint pos = -1);

    /**
     * @brief   Destructor
     */
    ~GLAttribute();

    /**
     * @brief   Initialize the attribute. Either \ref init or \ref tellLocation.
     * @param   program A valid GLProgram with an attribute matching the given name
     * @param   name    The name of the attribute.
     * @return  Returns true if successful or false if attribute fails to be obtained.
     */
    bool init(GLProgram program, const std::basic_string<GLchar>& name);

    /**
     * @brief   Explicitly initialize the attribute with it's location.
     * This is a nice function if you explicitly define your attribute locations in a shader.
     */
    void tellLocation(GLint loc);

    /**
     * @brief   Enable the attribute.
     */
    void enable();

    /**
     * @brief   Disable the attribute.
     */
    void disable();

    /**
     * @brief   Load buffer data into the attribute.
     * @param       count   The number of components per generic vertex attribute. Must be 1,2,3, or 4.
     * @param        step   The byte offset between consecutive generic vertex attributes. If stride is 0,
     *                      the generic vertex attributes are understood to be tightly packed into the array.
     * @param      offset   The distance to the first generic vertex in the array.
     * @param        type   The type of the data being loaded. Valid types are GL_BYTE, GL_UNSIGNED_BYTE,
     *                      GL_SHORT, GL_UNSIGNED_SHORT, GL_FIXED, or GL_FLOAT
     * @param   normalize   Normalize the data if set to GL_TRUE.
     */
    void loadBufferData(int count, unsigned long step, unsigned long offset = 0,
            GLenum type = GL_FLOAT, GLboolean normalize = GL_FALSE);

    /**
     * @brief   Get the index of the attribute.
     * @return  Returns the index of the attribute.
     */
    GLint getAttributeIdx() const;
protected:
    
    /// The index of the OpenGL attribute
    GLint  m_attribute;

}; // GLAttribute

#endif // __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLATTRIBUTE_HPP

