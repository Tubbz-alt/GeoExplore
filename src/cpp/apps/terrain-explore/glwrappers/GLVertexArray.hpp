/**
 * @file    GLVertexArray.hpp
 * @author  Josh Gleason
 * @date    5/31/2014
 */

#ifndef __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLVERTEXARRAY_HPP
#define __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLVERTEXARRAY_HPP

// Include OpenGL
#include <GL/glew.h>
#include <boost/shared_array.hpp>

/**
 * @brief This classes is very bare bones and manages a vertex array object (VAO).
 */
class GLVertexArray
{
public:
    /**
     * @brief Default constructor.
     */
    GLVertexArray();

    /**
     * @brief Destructor.
     */
    ~GLVertexArray();

    /**
     * @brief Assignment operator, uses removeBeforeDelete before copying data.
     * @param rhs The right hand side argument to be copied.
     * @return Returns *this.
     */
    GLVertexArray& operator=(const GLVertexArray& rhs);

    /**
     * @brief Create Vertex Array Objects.
     * @param count The number of VAOs to create.
     */
    void create(GLsizei count = 1);

    /**
     * @brief Bind a VAO.
     * @brief idx The index of the VAO to bind. Should be in range of [0, count-1] after GLVertexArray::create has been called.
     */
    void bind(int idx = 0);

    /**
     * @brief Static Utility function that unbinds the currently bound VAO.
     */
    static void unbindAll();
protected:

    /**
     * @brief Used by destructor to remove VAO if no references exist before deleting the class.
     */
    void removeBeforeDelete();

    /// The list of VAO OpenGL indices
    boost::shared_array<GLuint> m_vao;

    /// The number of VAO indices held by m_vao
    GLsizei                     m_count;
};

#endif // __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLVERTEXARRAY_HPP

