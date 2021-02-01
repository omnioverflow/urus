#pragma once

#include <vector>

namespace urus
{
    /**
    * Wrapper around Index Buffer abstraction.
    * Index buffer is an array of pointers into the vertex buffer, which 
    * allows to reuse existing data for multiple vertices.
    */
    class IndexBuffer
    {
        public:

            IndexBuffer();
            IndexBuffer(const IndexBuffer& other) = delete;
            IndexBuffer& operator=(const IndexBuffer& other) = delete;
            ~IndexBuffer();

            void set(unsigned int* indices, unsigned int nbIndices);
            void set(std::vector<unsigned int>& indices);

            unsigned int getHandle() const { return mHandle; }
            unsigned int getCount() const { return mCount; }

        private:

            unsigned int mHandle;
            unsigned int mCount;
    }; // class IndexBuffer
} // namespace urus
