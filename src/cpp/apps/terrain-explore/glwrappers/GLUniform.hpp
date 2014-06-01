/**
 * @file    GLUniform.hpp
 * @author  Josh Gleason
 * @date    5/31/2014
 */

#ifndef __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLUNIFORM_HPP
#define __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLUNIFORM_HPP

// Include OpenGL and standard libraries
#include <GL/glew.h>
#include <string>

#include "GLProgram.hpp"

/// The various types of uniforms
enum GLUniformType {
    INT_V, UINT_V, FLOAT_V, DOUBLE_V,
    VEC2UI_V, VEC3UI_V, VEC4UI_V,
    VEC2I_V, VEC3I_V, VEC4I_V,
    VEC2F_V, VEC3F_V, VEC4F_V,
    VEC2D_V, VEC3D_V, VEC4D_V,
    INT, UINT, FLOAT, DOUBLE,
    VEC2UI, VEC3UI, VEC4UI,
    VEC2I, VEC3I, VEC4I,
    VEC2F, VEC3F, VEC4F,
    VEC2D, VEC3D, VEC4D,
    MAT2F, MAT3F, MAT4F, MAT2X3F, MAT3X2F, MAT2X4F, MAT4X2F, MAT3X4F, MAT4X3F,
    MAT2D, MAT3D, MAT4D, MAT2X3D, MAT3X2D, MAT2X4D, MAT4X2D, MAT3X4D, MAT4X3D
};

// example if T is glm::mat4 then setFunc should be glProgramUniform4f
class GLUniform
{
public:
    GLUniform();
    GLUniform(GLProgram program, const std::basic_string<GLchar>& name, GLUniformType type);
    GLUniform(const GLUniform &rhs);
    ~GLUniform();
    GLUniform& operator=(const GLUniform& rhs);

    // must be called before using others
    /**
     * @brief Initialize the class.
     * @param program The program where the uniform is linked.
     * @param    name The name of the uniform.
     * @param    type The type of Uniform. See GLUniformType for valid types.
     * @return If uniform name is found in the program then return true. False otherwise.
     */
    bool init(GLProgram program, const std::basic_string<GLchar>& name, GLUniformType type);

    /**
     * @brief Load data into uniform, doesn't load into OpenGT yet (call GLUniform::set for that).
     * @param      data The data to load into the uniform.
     * @param     count The number of elements in data. This can be either an array or single value.
     * @param transpose If data is stored in column major, this should be GL_FALSE, if row major
     *                  this should be GL_TRUE.
     * Template type <B>T</B> should be a non-pointer type.
     */
    template <typename T>
    void loadData(const T &data, GLint count = 1, GLboolean transpose = GL_FALSE)
    {
        if ( m_data != nullptr )
            delete [] m_data;

        m_size = sizeof(T);
        m_count = count;
        m_transpose = transpose;

        m_data = new char[count*m_size];

        // copy data
        const char *dataPtr = reinterpret_cast<const char*>(&data);
        for ( int i = 0; i < m_count*m_size; ++i )
            m_data[i] = dataPtr[i];
    }

    /**
     * @brief Get the data that has been loaded into the uniform. Use this function for
     *        array data.
     * @return A const reference to the data array stored in the uniform.
     */
    template <typename T>
    const T* getDataArray() const
    {
        return reinterpret_cast<T*>(m_data);
    }
   
    /**
     * @brief Get the data that has been loaded into the uniform. Use this function for
     *        non-array data.
     * @return A const reference to the data in the uniform.
     */
    template <typename T>
    const T& getData() const
    {
        return *reinterpret_cast<T*>(m_data);
    }

    /**
     * @brief Load uniform into OpenGL using correct function based on uniform type.
     */
    void set();

    /**
     * @brief Check if data is being transposed.
     * @return GL_TRUE if being transposed, GL_FALSE if not.
     */
    GLboolean isTransposed() const { return m_transpose; }
    
    /**
     * @brief Get the type of the uniform.
     * @return Returns one of the valid values of GLUniformType.
     */
    GLUniformType getType() const { return m_type; }

    /**
     * @brief Get the number of elements stored in the uniform.
     * @return Number of elements stored in the uniform.
     */
    int getLength() const { return m_count; }

    /**
     * @brief Get the name of the uniform.
     * @return The GLstring name of the uniform.
     */
    const std::basic_string<GLchar>& getName() const { return m_name; }

    // check if the uniform has been initialized
    /**
     * @brief Check if uniform class has been initialized.
     * @return True if GLUniform::init was successfuly, false otherwize.
     */
    bool isInitialized() const { return m_isInitialized; }

    /**
     * @brief Static utility function which loads a uniform with data that is not meant to be changed.
     *
     * @param   program The program where the uniform is linked.
     * @param      name The name of the uniform.
     * @param      type The type of Uniform. See GLUniformType for valid types.
     * @param      data The data to load into the uniform.
     * @param     count The number of elements in data. This can be either an array or single value.
     * @param transpose If data is stored in column major, this should be GL_FALSE, if row major
     *                  this should be GL_TRUE.
     * @return If uniform name is found in the program and successfuly loaded and set then return true.
     *         Returns false otherwise.
     *
     * This bypasses the need to create and keep track of a GLUniform object but is slow so should only
     * be used for uniforms which never change.
     */
    template <typename T>
    static bool setUniform(const GLProgram& program, const std::basic_string<GLchar>& name, GLUniformType type, const T& data, size_t count = 1, GLboolean transpose = GL_FALSE)
    {
        GLUniform uniform;
        if ( !uniform.init(program, name, type) )
            return false;
        uniform.loadData(data, count, transpose);
        uniform.set();
        return true;
    }

protected:
    /// Type of uniform
    GLUniformType             m_type;
    /// The program which the uniform belongs to
    GLProgram                 m_program;
    /// The OpenGL index of the uniform
    GLint                     m_uniform;
    /// Flag to keep track of if data should be transposed when passing to OpenGL
    GLboolean                 m_transpose;
    /// The number of elements in m_data
    GLint                     m_count;
    /// Should be used for size of each member in m_data but isn't currently used.
    int                       m_size;
    /// Flag to keep track of successful GLUniform::init
    bool                      m_isInitialized;

    /// The name of the uniform
    std::basic_string<GLchar> m_name;
    /// The data for the uniform. This is just staged data, not necessarily loaded into OpenGL until GLUniform::set is called.
    char*                     m_data;
};

#endif // __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLUNIFORM_HPP

