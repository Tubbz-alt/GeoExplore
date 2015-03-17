#ifndef __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLCOMPLETEPROGRAM_HPP
#define __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLCOMPLETEPROGRAM_HPP

#include "GLProgram.hpp"

class GLCompleteProgram : public GLProgram
{
public:
    GLCompleteProgram();

    bool loadAndLink(const char* vshader, const char* fshader, const char* gshader = nullptr);
};

#endif // __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLCOMPLETEPROGRAM_HPP

