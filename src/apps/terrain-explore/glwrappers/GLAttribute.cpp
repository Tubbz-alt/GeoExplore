/**
 * @file    GLAttribute.cpp
 * @author  Josh Gleason
 * @date    5/18/2014
 */

//  Class Prototype headers
#include "GLAttribute.hpp"

// Default Constructor
GLAttribute::GLAttribute(GLint pos) :
    m_attribute(pos)
{}

// Destructor
GLAttribute::~GLAttribute()
{}

// Initialize the attribute. Either \ref init or \ref tellLocation.
bool GLAttribute::init(GLProgram program, const std::basic_string<GLchar>& name)
{
    m_attribute = program.getAttributeLocation(name);
    return m_attribute != -1;
}

// Explicitly initialize the attribute with it's location. This is a nice function if you
// explicitly define your attribute locations in a shader.
void GLAttribute::tellLocation(GLint loc)
{
    m_attribute = loc;
}

// Enable the attribute.
void GLAttribute::enable()
{
    glEnableVertexAttribArray(m_attribute);
}

// Disable the attribute.
void GLAttribute::disable()
{
    glDisableVertexAttribArray(m_attribute);
}

// Load buffer data into the attribute.
void GLAttribute::loadBufferData(int count, unsigned long step, unsigned long offset,
        GLenum type, GLboolean normalize)
{
    glVertexAttribPointer(m_attribute, count, type, normalize, step, reinterpret_cast<void*>(offset));
}

// Get the index of the attribute.
GLint GLAttribute::getAttributeIdx() const
{
    return m_attribute;
}

