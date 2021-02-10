#pragma once

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
            void set(unsigned int uniform, unsigned int texIndex);
            void unset(unsigned int textureIndex);

            inline unsigned int getHandle() const { return mHandle; }

        private:

            unsigned int mWidth;
            unsigned int mHeight;
            unsigned int mChannels;
            unsigned int mHandle;
    }; // class Texture
} // namespace urus
