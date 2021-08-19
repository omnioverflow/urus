/*
    TODO:
        * re-activate (uncomment) set/unset methods
*/
#pragma once

#include <string>

#include "engine/base/opengl_support.h"

namespace urus
{
    class Texture
    {
        public:

            explicit Texture(const char* path,
                             GLint texFormat = GL_RGB,
                             GLint srcImgFormat = GL_RGBA) noexcept;
            explicit Texture(const std::string& path, 
                             GLint texFormat = GL_RGB,
                             GLint srcImgFormat = GL_RGBA) noexcept;
            ~Texture();
            
            Texture(const Texture& other) = delete;
            Texture& operator= (const Texture& other) = delete;

            void use() const;
            void unbind() const;

            /*
            void set(GLint uniform, GLint texture);
            void unset(GLint texture);
            */

            inline GLuint getHandle() const noexcept { return mHandle; }

        private:

            void load(const char* path);
            void load(const std::string& path);
            void release();
            
            GLuint mHandle;
            GLint  mTexFormat;
            GLint  mSrcImgFormat;
    }; // class Texture
} // namespace urus
