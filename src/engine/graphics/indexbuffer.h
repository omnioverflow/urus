#pragma once

#include <vector>

namespace urus
{
    class IndexBuffer
    {
        public:

            IndexBuffer();
            IndexBuffer(const IndexBuffer& other) = delete;
            IndexBuffer& operator=(const IndexBuffer& other) = delete;
            ~IndexBuffer();

            void set(unsigned int* rr, unsigned int len);
            void set(std::vector<unsigned int>& input);

            unsigned int getHandle() const { return mHandle; }
            unsigned int getCount() const { return mCount; }

        private:

            unsigned int mHandle;
            unsigned int mCount;
    }; // class IndexBuffer
} // namespace urus
