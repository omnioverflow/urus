#include "indexbuffer.h"

// FIXME: include OpenGL

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

    void IndexBuffer::set(unsigned int* array, unsigned int length)
    {
        mCount = length;
        const unsigned int size = sizeof(unsigned int);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * mCount, array, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::set(std::vector<unsigned int>& array)
    {
        const auto length = array.size();
        if (length)
            set(&array.data(), length);
    }
} // namespace urus
