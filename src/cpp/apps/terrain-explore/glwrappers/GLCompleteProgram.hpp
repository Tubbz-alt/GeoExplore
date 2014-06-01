/**
 * @file    GLCompleteProgram.hpp
 * @author  Josh Gleason
 * @date    5/31/2014
 */

#ifndef __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLCOMPLETEPROGRAM_HPP
#define __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLCOMPLETEPROGRAM_HPP

// Local Depedencies
#include "GLProgram.hpp"

/**
 * @brief  The GLCompleteProgram class is responsible for managin all aspects of
 *         an OpenGL program object, including loading and linking the program.
 */
class GLCompleteProgram : public GLProgram
{
public:
    /**
     * @brief   Default Constructor
     */
    GLCompleteProgram();

    /**
     * @brief   Get a program ready to be used loading compiling and linking all shaders.
     * @param   vshader  The filename of the vertex shader.
     * @param   fshader  The filename of the fragment shader.
     * @param   gshader  Optionally use a geometry shader.
     */
    bool loadAndLink(const char* vshader, const char* fshader, const char* gshader = nullptr);
};

#endif // __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLCOMPLETEPROGRAM_HPP

