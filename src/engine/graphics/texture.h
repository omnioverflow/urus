#pragma once

#include <string>

#include "engine/base/opengl_support.h"

namespace urus
{
    class Texture
    {
        public:

            explicit Texture(const char* path) noexcept;
            explicit Texture(const std::string& path) noexcept;
            ~Texture();

            Texture() = delete; // No source image path, no texture
            Texture(const Texture& other) = delete;
            Texture& operator= (const Texture& other) = delete;

            void use() const;
            void unbind() const;

            void set(GLint uniform, GLint texture);
            void unset(GLint texture);

            inline GLuint getHandle() const noexcept { return mHandle; }

        private:

            void load(const char* path);
            void load(const std::string& path);
            void release();
            
            GLuint   mHandle;
    }; // class Texture
} // namespace urus
