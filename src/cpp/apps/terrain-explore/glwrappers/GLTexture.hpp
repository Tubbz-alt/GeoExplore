/**
 * @file    GLTexture.hpp
 * @author  Josh Gleason
 * @date    5/31/2014
 */

#ifndef __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLTEXTURE_HPP
#define __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLTEXTURE_HPP

// Include OpenGL and the GL math library
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <boost/shared_array.hpp>

/**
 * @brief This class is resposible for managing an OpenGL texture object.
 */
class GLTexture
{
public:
    /**
     * @brief Default constructor.
     */
    GLTexture();

    /**
     * @brief Destructor.
     */
    ~GLTexture();

    /**
     * @brief Copy constructor. Mark texture for deletion if this class contains the last
     *        instance of texture.
     * @return Returns *this.
     */
    GLTexture &operator=(const GLTexture& rhs);

// keep for debugging (needs #include opencv2/opencv.hpp)
#if 0
    void showTexture(GLsizei idx = 0)
    {
        GLint width, height, format;
        this->bind(GL_TEXTURE_2D, idx);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);

        std::cout << "Width/Height : (" << width << ',' << height << ')' << std::endl;
        cv::Mat img;
        if ( format == GL_RGB || format == GL_BGR )
            img = cv::Mat(height, width, CV_8UC3);
        else
            img = cv::Mat(height, width, CV_8UC4);

        glGetTexImage(GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, (void*)(img.data));
        cv::flip(img,img,0);    // flip vertical
        cv::imshow("Texture", img);
        cv::waitKey(0);
        cv::destroyWindow("Texture");
    }
#endif

    /**
     * @brief Generate textures.
     * @param n The number of textures to create.
     * @return True if successful. False otherwise.
     */
    bool generate(GLsizei n = 1);

    /**
     * @brief Bind texture.
     * @param target Supported values for target:
     *               <B>1D Texture Types</B>:
     *               GL_TEXTURE_1D,
     *               GL_PROXY_TEXTURE_1D
     *               <B>2D Texture Types</B>:
     *               GL_TEXTURE_2D,
     *               GL_TEXTURE_1D_ARRAY,
     *               GL_TEXTURE_RECTANGLE,
     *               GL_TEXTURE_CUBE_MAP_POSITIVE_X,
     *               GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
     *               GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
     *               GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
     *               GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
     *               GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
     *               GL_PROXY_TEXTURE_2D,
     *               GL_PROXY_TEXTURE_1D_ARRAY,
     *               GL_PROXY_TEXTURE_RECTANGLE
     *               <B>3D Texture Types</B>:
     *               GL_PROXY_TEXTURE_CUBE_MAP,
     *               GL_TEXTURE_3D,
     *               GL_TEXTURE_2D_ARRAY,
     *               GL_TEXTURE_CUBE_MAP_ARRAY,
     *               GL_PROXY_TEXTURE_3D,
     *               GL_PROXY_TEXTURE_2D_ARRAY,
     *               GL_PROXY_TEXTURE_CUBE_MAP_ARRAY
     * @param    idx The index of the texture to bind.
     */
    void bind(GLenum target, GLsizei idx = 0);

    /**
     * @brief Set the texture data.
     * @param data    The data contiaining texture information. Should be formatted so that
     *                information is in order from left to right, bottom to top, i.e. row major
     *                with origin at lower left.
     * @param dimVals 1, 2, or 3 element array indicating size of texture for 1D, 2D, and 3D
     *                textures respectively. For 2D this contains width then height of texture.
     *                For 3D this contains the width, height, then depth of the texture.
     * @param     idx The index of the texture to set.
     * @param    type The data type contained in data. (ex. if templated type <B>T</B> is GLubyte,
     *           then type should be GL_UNSIGNED_BYTE.
     * @param  format How the data is formatted inside the data array. Usually GL_RGB or GL_RGBA.
     * @param     lod The level-of-detail number. Level 0 is the base image, level n is the nth mipmap reduction image.
     * @return If true then data set successfully. If false then failure occured.
     */
    template <typename T>
    bool setData(const T* data, const GLsizei* dimVals, GLsizei idx = 0, GLenum type = GL_UNSIGNED_BYTE, GLenum format = GL_RGBA, GLint lod = 0 );

    /**
     * @brief Load image into texture from file.
     * @param filename The path to the image file.
     * @param      idx The index of the texture to load image into.
     * @param      lod The level-of-detail number. Level 0 is the base image, level n is the
     *                 nth mipmap reduction image.
     * @return If true then image loaded and set successfully. If false then failure occured.
     */
    bool loadImageData(const char* filename, GLsizei idx = 0, GLint lod = 0);
    
    /**
     * @brief Static utilitiy function which tells OpenGL how to sample the data when viewing
     *        texture at non-native resolution.
     * @param target The type of target: see GLTexture::bind <B>target</B> parameter for valid
     *               values.
     * @param minFilter The type of filtering to use when near the the texture. Valid types are
     *                  GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST,
     *                  GL_NEAREST_MIPMAP_LINEAR, and GL_LINEAR_MIPMAP_LINEAR.
     * @param magFilter Texture magnification function to use. Valid values are GL_NEAREST and
     *                  GL_LINEAR.
     * @param     wrapS The wrap parameter for the width of the texture (s coordinates). Valid
     *                  types are GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, or GL_REPEAT. Only used
     *                  if referencing texture coordaintes outside [0,1].
     * @param     wrapT Same as wrapS but for height of the texture (t coordinate).
     */
    static void setSampling(GLenum target, GLenum minFilter = GL_NEAREST, GLenum magFilter = GL_NEAREST, GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT);
    /**
     * @brief Static utility function that generates multiresolution mipmaps for the targeted
     *               texture.
     * @param target The type of texture: see GLTexture::bind <B>target</B> parameter for valid
     *               values.
     */
    static void generateMipMap(GLenum target);

    /**
     * @brief Static utility function for unbinding textures from OpenGL of targeted type.
     * @param target The type of texture: see GLTexture::bind <B>target</B> parameter for valid
     *               values.
     */
    static void unbindTextures(GLenum target);
protected:
    /**
     * @brief Reset class to uninitialized state.
     */
    void clean();

    /// The container for texture parameters.
    struct TexParameters
    {
        GLuint textureId;
        GLenum target;
        glm::vec3 dimensions; // width, height, depth
        GLenum type;
        GLenum format;
        GLint internalFormat;
        GLint lod;  // level-of-detail (0 = highest detail)
        size_t dataTypeSize;
    };

    /// The number of textures managed by this class
    std::shared_ptr<GLsizei> m_texCount;
    /// The parameters for each texture managed by this class
    boost::shared_array<TexParameters> m_texParameters; 
};

template <typename T>
bool GLTexture::setData(const T* data, const GLsizei* dimVals, GLsizei idx, GLenum type, GLenum format, GLint lod)
{
    if ( m_texParameters != nullptr && idx < *m_texCount && m_texParameters[idx].target != GL_NONE )
    {
        switch(m_texParameters[idx].target)
        {
            case GL_TEXTURE_1D:
            case GL_PROXY_TEXTURE_1D:
                glTexImage1D(m_texParameters[idx].target,
                    lod,
                    format,
                    dimVals[0], // width
                    0,
                    format,
                    type,
                    reinterpret_cast<const void*>(data));
                break;
            case GL_TEXTURE_2D:
            case GL_TEXTURE_1D_ARRAY:
            case GL_TEXTURE_RECTANGLE:
            case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
            case GL_PROXY_TEXTURE_2D:
            case GL_PROXY_TEXTURE_1D_ARRAY:
            case GL_PROXY_TEXTURE_RECTANGLE:
            case GL_PROXY_TEXTURE_CUBE_MAP:
                glTexImage2D(m_texParameters[idx].target,
                    lod,
                    format,
                    dimVals[0], // width
                    dimVals[1], // height
                    0,
                    format,
                    type,
                    reinterpret_cast<const void*>(data));
                break;
            case GL_TEXTURE_3D:
            case GL_TEXTURE_2D_ARRAY:
            case GL_TEXTURE_CUBE_MAP_ARRAY:
            case GL_PROXY_TEXTURE_3D:
            case GL_PROXY_TEXTURE_2D_ARRAY:
            case GL_PROXY_TEXTURE_CUBE_MAP_ARRAY:
                glTexImage3D(m_texParameters[idx].target,
                    lod,
                    format,
                    dimVals[0], // width
                    dimVals[1], // height
                    dimVals[2], // depth
                    0,
                    format,
                    type,
                    reinterpret_cast<const void*>(data));
                break;
            default:
                return false;
        }
    }
    return true;
}

#endif // __SRC_APPS_TERRAINEXPLORE_GLWRAPPERS_GLTEXTURE_HPP

