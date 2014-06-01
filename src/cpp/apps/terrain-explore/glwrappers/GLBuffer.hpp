/**
 * @file    GLBuffer.hpp
 * @author  Josh Gleason
 * @date    5/31/2014
 */

#ifndef __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLBUFFER_H
#define __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLBUFFER_H

// Include boost sharred array and glew
#include <boost/shared_array.hpp>
#include <GL/glew.h>

/**
 * @brief   The GLBuffer class is responsible for managing one or more OpenGL buffer object.
 */
class GLBuffer
{
public:
    /**
     * @brief   Constructor.
     */
    GLBuffer();

    /**
     * @brief   Destructor.
     *
     * If this object is the GLBuffer holding the last instance of the m_buffers pointer
     * then the buffer is deleted
     */
    ~GLBuffer();

    /**
     * @brief Generate new buffers, the size of n. This must be called before binding.
     * @param     n The size of the new buffer to be created.
     * @return True on success, false on failure.
     */
    bool generate(GLsizei n = 1);

    /**
     * @brief Bind a buffer object
     * @param       idx The index of the buffer to bind
     * @param    target One of the following:
     *   GL_ARRAY_BUFFER,
     *   GL_ATOMIC_COUNTER_BUFFER,
     *   GL_COPY_READ_BUFFER_BINDING,
     *   GL_COPY_WRITE_BUFFER_BINDING,
     *   GL_DRAW_INDIRECT_BUFFER,
     *   GL_ELEMENT_ARRAY_BUFFER,
     *   GL_PIXEL_PACK_BUFFER,
     *   GL_PIXEL_UNPACK_BUFFER,
     *   GL_TEXTURE_BUFFER,
     *   GL_TRANSFORM_FEEDBACK_BUFFER,
     *   GL_UNIFORM_BUFFER.
     */
    void bind(GLenum target, GLsizei idx = 0);
 
    /**
     * @brief Binds a buffer object to an indexed buffer target. This must be called
     *        after bind in order to get correct target
     * @param  bindingPoint The index of the binding point within the array. Must be smaller than
     *                      GL_MAX_UNIFORM_BUFFER_BINDINGS.
     * @param           idx The index of the buffer to bind.
     * 
     * This function binds the buffer object to the binding point at <B>bindingPoint</B>. For each
     * type of <B>target</B> (see \ref GLBuffer::bind) there is a list of buffer binding points,
     * as well as a single general binding point. These binding points can be use to bind
     * multiple blocks of data to reference data in the same buffers. The diagram below describes
     * the memory layout of binding a buffer to a binding point, then binding multiple
     * uniform blocks to the same binding point.
     *
     * \image html BindBufferBlock.jpg "Buffer binding point example"
     *
     * <B>\noref %Image Source: <a href="http://www.lighthouse3d.com/tutorials/glsl-core-tutorial/3490-2/">www.lighthouse3d.com</a></B>
     */
    void bindBase(GLuint bindingPoint, GLsizei idx = 0);

    /**
     * @brief Initialize a data store for the buffer with nothing in it. Buffer
     * @param  size The size <B>in bytes</B> of data to initialize.
     * @param usage Specifies the expected pattern of the data store, GL_STATIC_DRAW is
     *              probably good since this is clearing it.
     * @param   idx The index of the buffer to set to empty.
     * @return True on success, false on failure.
     */
    bool setEmpty(GLsizeiptr size, GLenum usage = GL_STATIC_DRAW, GLsizei idx = 0);

    /**
     * @brief Updates a subset of the buffer objects data store.
     * @param      data A pointer to the new data that will be copied into the data store
     * @param    offset The offset into the buffer object's data store where the data replacement
     *                  begins <B>in bytes</B>.
     * @param      size The number of elements being replaced in the data store.
     * @param       idx The index of the buffer to set to empty.
     * @return True on success, false on failure.
     *
     * Buffer must be bound and data store must already be initialized. Use either setEmpty()
     * or setData() to initialize the data store. The offset/sizeof(T)+size must be no greater
     * than the size of the allocated data store.
     */
    template <typename T>
    bool setSubData(const T* data, GLintptr offset = 0, GLsizei size = 1, GLsizei idx = 0)
    {
        if ( m_buffers != nullptr && m_bufferCount > idx && m_dataSet[idx] )
        {
            glBufferSubData(m_targets[idx], offset, sizeof(T)*size, reinterpret_cast<const void*>(data)); 
            return true;
        }
        return false;
    }

    /**
     * @brief Create and initialize a buffer objects data store. Buffer must be initialized
     *        and bound before using this function.
     * @param      data A pointer to the data to be stored in the data store.
     * @param      size The number of elements in the data array.
     * @param     usage The expected usage of the buffer. Can be one of the following :
     *                  GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW,
     *                  GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ,
     *                  GL_DYNAMIC_COPY.
     * @param       idx The index of the buffer.
     * @return True on success, false on failure.
     */
    template <typename T>
    bool setData(const T* data, GLsizei size = 1, GLenum usage = GL_STATIC_DRAW, GLsizei idx = 0)
    {
        if ( m_buffers != nullptr && m_bufferCount > idx && m_targets[idx] != GL_NONE )
        {
            glBufferData(m_targets[idx], sizeof(T)*size, reinterpret_cast<const void*>(data), usage);
            m_dataSet[idx] = true;
            return true;
        }

        // not initialized or not bound
        return false;
    }

    /**
     * @brief A static utility function used to unbind a buffer.
     * @param    target Any of the valid buffers in OpenGL. See the description of
     *                  the target parameter in \ref GLBuffer::bind
     */
    static void unbindBuffers(GLenum target);

    /**
     * @brief Return the OpenGL buffer index. Be very careful with this because the
     *        buffer does not recognize this as a reference count.
     * @param   idx The index of the buffer.
     * @return The index of the OpenGL buffer.
     *
     * Should only be used when debugging.
     */
    GLuint getBufferIdx(GLsizei idx = 0);
protected:
    /// The OpenGL buffer indicies
    boost::shared_array<GLuint> m_buffers;
    /// The target/type of each buffer
    boost::shared_array<GLenum> m_targets;
    /// Keeps track of which buffers data stores have been initialized.
    boost::shared_array<bool>   m_dataSet;
    /// The number of buffers managed by the class.
    GLsizei m_bufferCount;
};

#endif // __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLBUFFER_H

