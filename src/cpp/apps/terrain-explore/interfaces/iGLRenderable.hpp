/**
 * @file    iGLRenderable.hpp
 * @author  Josh Gleason
 * @date    5/18/2014
 */

#ifndef __SRC_APPS_TERRAINEXPLORE_INTERFACES_IGLRENDERABLE_HPP
#define __SRC_APPS_TERRAINEXPLORE_INTERFACES_IGLRENDERABLE_HPP

#include <glm/glm.hpp>
#include "../glwrappers/GLBuffer.hpp"

// Texture types
// Note: TEXTURE_SPECULAR and TEXTURE_BUMP maps aren't currently implemented.
const unsigned int TEXTURE_DIFFUSE  = 0x1;
const unsigned int TEXTURE_SPECULAR = 0x2;
const unsigned int TEXTURE_BUMP     = 0x4;

const unsigned int TEXTURE_TYPES[] = {TEXTURE_DIFFUSE, TEXTURE_SPECULAR, TEXTURE_BUMP};

// Locations of Attributes in shaders
const GLuint V_POSITION = 0;
const GLuint V_NORMAL   = 1;
const GLuint V_UVCOORD  = 2;
const GLuint V_TANGENT  = 3;
const GLuint V_BINORMAL = 4;
const GLuint V_COLOR    = 5;

/**
 * All combinations of types for a texture
 * DRAW_TEXTURE_ Qualifiers
 *    D : Diffuse texture   (0x1)
 *    S : Specular map      (0x2)
 *    B : Bump map          (0x4)
 * DRAW_MATERIAL
 *    Just material properties (no textures)
 */
enum DrawType {
    DRAW_MATERIAL       = 0x0,
    DRAW_TEXTURE_D      = TEXTURE_DIFFUSE,
    DRAW_TEXTURE_S      = TEXTURE_SPECULAR,
    DRAW_TEXTURE_DS     = TEXTURE_DIFFUSE | TEXTURE_SPECULAR,
    DRAW_TEXTURE_B      = TEXTURE_BUMP,
    DRAW_TEXTURE_DB     = TEXTURE_DIFFUSE | TEXTURE_BUMP,
    DRAW_TEXTURE_SB     = TEXTURE_SPECULAR | TEXTURE_BUMP,
    DRAW_TEXTURE_DSB    = TEXTURE_DIFFUSE | TEXTURE_SPECULAR | TEXTURE_BUMP
};

/// Uniform types
enum UniformType {
    MATERIALS           = 0,
    TEXBLEND            = 1
};

// uniform block binding points
const GLuint UB_MATRICES = 1;
const GLuint UB_LIGHT    = 2;
const GLuint UB_MATERIAL = 3;

// uniform block offsets based on std140 layout from OpenGL 4.1 specification
const GLintptr MAT_MVP_OFFSET     = 0;
const GLintptr MAT_MV_OFFSET      = sizeof(glm::mat4);
const GLintptr MAT_NORMAL_OFFSET  = sizeof(glm::mat4)*2;
const GLsizeiptr MAT_BUFFER_SIZE  = sizeof(glm::mat4)*3;

/*
// For reference, this is the definition of the Lights structure
struct LightInfo
{
    vec3 position;
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
};

// light properties
layout(std140) uniform Lights
{
    uniform int count;
    uniform LightInfo info[8];
} lights;
*/

// Array offsets for Lights based on std140 layout
const GLintptr LIGHT_COUNT_OFFSET          = 0;
const GLintptr LIGHT_ARRAY_OFFSET          = sizeof(glm::vec4);
const GLintptr LIGHT_ARRAY_POSITION_OFFSET = 0;
const GLintptr LIGHT_ARRAY_DIFFUSE_OFFSET  = sizeof(glm::vec4);
const GLintptr LIGHT_ARRAY_SPECULAR_OFFSET = sizeof(glm::vec4)*2;
const GLintptr LIGHT_ARRAY_AMBIENT_OFFSET  = sizeof(glm::vec4)*3;
const GLintptr LIGHT_ARRAY_STEP            = sizeof(glm::vec4)*4;
const int LIGHT_ARRAY_SIZE                 = 8; // max number of lights
const GLsizeiptr LIGHT_BUFFER_SIZE         = LIGHT_ARRAY_OFFSET + LIGHT_ARRAY_STEP * LIGHT_ARRAY_SIZE;

// Array offsets for Material properties based on std140 layout
const GLintptr MATERIAL_DIFFUSE_OFFSET   = 0;
const GLintptr MATERIAL_SPECULAR_OFFSET  = sizeof(glm::vec4);
const GLintptr MATERIAL_AMBIENT_OFFSET   = sizeof(glm::vec4)*2;
const GLintptr MATERIAL_SHININESS_OFFSET = sizeof(GLfloat)*11;
const GLintptr MATERIAL_TEXBLEND_OFFSET  = sizeof(GLfloat)*12;
const GLsizeiptr MATERIAL_BUFFER_SIZE    = sizeof(GLfloat)*13;

/**
 * @class iGLRenderable
 * @brief All classes which will be rendered using OpenGL must inherit this class.
 */
class iGLRenderable
{
public:
    /**
     * @brief Default Constructor
     */
    iGLRenderable() {};

    /**
     * @brief Virtual Destructor
     */
    virtual ~iGLRenderable() {};
    
    /**
     * @brief Get the model matrix which transforms the model from model space to world space.
     * @return Returns the model matrix
     */
    virtual const glm::mat4& getModelMatrix() = 0;

    /**
     * @brief Draw the model to the screen.
     * @param type The type of renderable object. See DrawType for valid values.
     */
    virtual void draw(DrawType type = DRAW_MATERIAL) = 0;

    /**
     * @brief  Set the uniform buffers before calling draw to ensure the model is
     *         placed in the correct world location and drawn with the correct materials.
     * @param type The type of renderable object. See DrawType for valid values.
     */
    virtual void setUniforms(GLBuffer &ubo, UniformType type = MATERIALS) = 0;
};

#endif // __SRC_APPS_TERRAINEXPLORE_INTERFACES_IGLRENDERABLE_HPP

