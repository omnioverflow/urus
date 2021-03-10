#include "engine/graphics/texture_raw_image.h"

#include <cassert>

// FIXME: correct include paths in cmake
#include "stb_image.h"

namespace urus
{
    TextureLoader::TextureLoader(const char* path)
    : mWidth(0)
    , mHeight(0)
    , mChannels(0)
    , mData(nullptr)
    {
        static int numComponentsPerPixel = 4;
        try
        {
            mData = stbi_load(
                              path,
                              &mWidth,
                              &mHeight,
                              &mChannels,
                              numComponentsPerPixel
                             );
        }
        catch (...)
        {
            assert(false);
        }
    }

    TextureLoader::TextureLoader(const std::string& path)
    : TextureLoader(path.c_str())
    {}

    TextureLoader::~TextureLoader()
    {
        if (mData)
            stbi_image_free(mData);
    }

    GLuint TextureLoader::texWidth() const 
    { 
        return mWidth;
    }

    Gluint TextureLoader::texHeight() const 
    { 
        return mHeight;
    }

    Gluint TextureLoader::texChannels() const
    { 
        return mChannels;
    }

    bool TextureLoader::texLoaded() const 
    {
        return mData != nullptr;
    }
} // namespace urus