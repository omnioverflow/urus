#pragma once

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

            TextureLoader(const TextureLoader& other) = delete;
            TextureLoader& operator= (const TextureLoader& other) = delete;

            /**
             * dtor releases the image resources.
             */
            ~TextureLoader();

            GLuint texWidth() const noexcept;
            GLuint texHeight() const noexcept;
            GLuint texChannels() const noexcept;
    };
} // namespace urus