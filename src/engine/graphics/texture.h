#pragma once

#include "engine/base/opengl_support.h"

namespace urus
{
    class Texture
    {
        public:

            Texture();
            Texture(const Texture& other) = delete;
            Texture& operator= (const Texture& other) = delete;
            explicit Texture(const char* path);
            ~Texture();

            void load(const char* path);
            void set(GLint uniformIndex, GLint textureIndex);
            void unset(GLint textureIndex);

            inline unsigned int getHandle() const { return mHandle; }

        private:

            GLuint mWidth;
            GLuint mHeight;
            GLuint mChannels;
            GLuint mHandle;
    }; // class Texture
} // namespace urus
