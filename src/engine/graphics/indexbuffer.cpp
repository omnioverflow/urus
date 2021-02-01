#include "indexbuffer.h"

#include "engine/base/compiler_support.h"

namespace urus
{
    IndexBuffer::IndexBuffer()
    {
        glGenBuffers(1, &mHandle);
        mCount = 0;
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &mHandle);
    }

    void IndexBuffer::set(unsigned int* indices, unsigned int nbIndices)
    {
        mCount = nbIndices;
        const auto size = sizeof(unsigned int);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(size) * mCount, indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::set(std::vector<unsigned int>& indices)
    {
        const auto length = indices.size();
        if (length)
            set(indices.data(), length);
    }
} // namespace urus