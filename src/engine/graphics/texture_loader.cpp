#include "engine/graphics/texture_loader.h"

#include <cassert>

// FIXME: correct include paths in cmake
#include "stb_image/stb_image.h"

namespace urus
{
    TextureLoader::TextureLoader(const char* path) noexcept
    : mTexWidth(0)
    , mTexHeight(0)
    , mTexChannels(0)
    , mData(nullptr)
    {
        static const int num_components_per_pixel = 4;
        try
        {
            auto lol = stbi_load(
                              path,
                              &mTexWidth,
                              &mTexHeight,
                              &mTexChannels,
                              num_components_per_pixel
                             );
        }
        catch (...)
        {
            assert(false);
        }
    }

    TextureLoader::TextureLoader(const std::string& path) noexcept
    : TextureLoader(path.c_str())
    {}

    TextureLoader::~TextureLoader()
    {
        if (mData)
            stbi_image_free(mData);
    }

    GLint TextureLoader::texWidth() const noexcept
    { 
        return mTexWidth;
    }

    GLint TextureLoader::texHeight() const noexcept
    { 
        return mTexHeight;
    }

    GLint TextureLoader::texChannels() const noexcept
    { 
        return mTexChannels;
    }

    bool TextureLoader::texLoaded() const noexcept
    {
        return mData != nullptr;
    }
} // namespace urus
