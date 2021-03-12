#pragma once

#include <string>

#include "engine/base/opengl_support.h"

namespace urus
{
    /**
     * RAII-style wrapper around C library (stb_image) image loading capabilities.
     */
    class TextureLoader
    {   
        public:

            /**
             * The resource (i.e. a source image) is loaded into memory in ctor,
             * and its lifecycle is managed by TextureLoader instance.
             */
            explicit TextureLoader(const std::string& path) noexcept;
            explicit TextureLoader(const char* path) noexcept;

            TextureLoader(const TextureLoader& other) = delete;
            TextureLoader& operator= (const TextureLoader& other) = delete;

            /**
             * dtor releases the image resources.
             */
            ~TextureLoader();

            inline GLint texWidth() const noexcept;
            inline GLint texHeight() const noexcept;
            inline GLint texChannels() const noexcept;

            /**
             * Texture might not be loaded due to issue on reading
             * source file from the file system.
             *
             * @return wheather the texture is loaded.
             */
            inline bool texLoaded() const noexcept;

        private:

            GLint    mTexWidth;
            GLint    mTexHeight;
            GLint    mTexChannels;
            GLubyte* mData;
    };
} // namespace urus
