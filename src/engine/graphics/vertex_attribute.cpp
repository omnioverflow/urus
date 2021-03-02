#include "vertex_attribute.h"

#include "macaque/vec.h"
#include "vec.h"

#include "engine/base/opengl_support.h"

namespace urus
{
    template VertexAttribute<int>;
    template VertexAttribute<float>;
    template VertexAttribute<macaque::vec2>;
    template VertexAttribute<macaque::vec3>;
    template VertexAttribute<macaque::vec4>;

    template <typename T>
    VertexAttribute<T>::VertexAttribute()
    {
        // Generate OpenGL buffer and init handle with it
        glGenBuffers(1, &mHandle);
        mCount = 0;
    }

    template <typename T>
    VertexAttribute<T>::~VertexAttribute()
    {
        // Delete OpenGL buffer associated with the handle
        glDeleteBuffers(1, &mHandle);
    }

    template <>
    void VertexAttribute<int>::setVertexAttribPointer(unsigned int index)
    {
#ifdef __APPLE__
        // glVertexAttribIPointer is unavailabe on Mac?
        glVertexAttribIPointerEXT(index, 1, GL_INT, 0, nullptr);
#else
        glVertexAttribIPointer(index, 1, GL_INT, 0, nullptr);
#endif
    }

    template <typename T>
    void VertexAttribute<T>::set(const T* attribs, unsigned int nbAttribs)
    {
        mCount = nbAttribs;
        const auto size = sizeof(T);
        glBindBuffer(GL_ARRAY_BUFFER, mHandle);
        glBufferData(GL_ARRAY_BUFFER, size * mCount, attribs, GL_STREAM_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    template <typename T>
    void VertexAttribute<T>::set(const std::vector<T>& attribs)
    {
        const auto nbAttribs = attribs.size();
        if (nbAttribs)
            set(attribs.data(), nbAttribs);
    }

    template <typename T>
    unsigned int VertexAttribute<T>::getCount() const
    {
        return mCount;
    }

    template <typename T>
    unsigned int VertexAttribute<T>::getHandle() const
    {
        return mHandle;
    }

} // namespace urus
