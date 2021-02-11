#include "texture.h"

// FIXME: missing OpenGL include

namespace urus
{
    Texture::Texture()
    : mWidth(0)
    , mHeight(0)
    , mChannels(0)
    {
        glGenTextures(1, &mHandle);
    }

    Texture::Texture(const char* path)
    {
        glGenTextures(1, &mHandle);
        load(path);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &mHandle);
    }

    void Texture::load(const char* path)
    {
        // FIXME: missing impl
    }

    void Texture::set(unsigned int unformIndex, unsigned int textureIndex)
    {
        glActiveTexture(GL_TEXTURE0 + textureIndex);
        glBindTexture(GL_TEXTURE_2D, mHandle);
        glUniform1i(uniformIndex, textureIndex);
    }

    void Texture::unset(unsigned int textureIndex)
    {
        glActiveTexture(GL_TEXTURE0 + textureIndex);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);
    }
} // namespace urus
