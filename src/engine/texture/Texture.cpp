#include "texture.h"

#include <cassert>
#include <iostream>

#include "engine/texture/TextureLoader.h"
#include "stb_image/stb_image.h"

namespace urus
{
    Texture::Texture(const char* path, GLint texFormat, GLint srcImgFormat) noexcept
    : mHandle(0)
    , mTexFormat(texFormat)
    , mSrcImgFormat(srcImgFormat)
    {
        glGenTextures(1, &mHandle);

        try
        {
            load(path);
        }
        catch (const std::exception& exp)
        {
            std::cerr << exp.what() << std::endl;
        }
    }

    Texture::Texture(const std::string& path, GLint texFormat, GLint srcImgFormat) noexcept
    : Texture(path.c_str(), texFormat, srcImgFormat)
    {
    }

    Texture::~Texture()
    {
        release();
    }

    void Texture::release()
    {
        glDeleteTextures(1, &mHandle);
    }

    void Texture::load(const char* path)
    {
        TextureLoader texLoader(path);
    
        if (!texLoader.isTexLoaded())
        {
            assert(false);
            return;
        }

        glBindTexture(GL_TEXTURE_2D, mHandle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,                      // mipmap level
            mTexFormat,             // texture format
            texLoader.texWidth(),
            texLoader.texHeight(),
            0,                      // border, must always be 0
            mSrcImgFormat,          // source image format
            GL_UNSIGNED_BYTE,       // source image data type (i.e. array of those)
            texLoader.texData()     //source image data
        );        

        glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::load(const std::string& path)
    {
        load(path.c_str());
    }

    void Texture::use() const
    {
        glBindTexture(GL_TEXTURE_2D, mHandle);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    /*
    void Texture::set(GLint uniform, GLint texture)
    {
        glActiveTexture(GL_TEXTURE0 + texture);
        glBindTexture(GL_TEXTURE_2D, mHandle);
        glUniform1i(uniform, texture);
    }

    void Texture::unset(GLint texture)
    {
        glActiveTexture(GL_TEXTURE0 + texture);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);
    }
    */
} // namespace urus
