#include "VertexAttribute.h"

#include "mqMath/Vec.h"

#include "engine/base/OpenGLSupport.h"

namespace urus
{
    template VertexAttribute<int>;
    template VertexAttribute<float>;
    template VertexAttribute<macaque::vec2>;
    template VertexAttribute<macaque::vec3>;
    template VertexAttribute<macaque::vec4>;
    template VertexAttribute<macaque::ivec4>;

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
    void VertexAttribute<int>::setVertexAttribPointer(GLuint index)
    {
#ifdef __APPLE__
        // glVertexAttribIPointer is unavailabe on Mac?
        glVertexAttribIPointerEXT(index, 1, GL_INT, 0, nullptr);
#else
        glVertexAttribIPointer(index, 1, GL_INT, 0, nullptr);
#endif
    }

    template <>
    void VertexAttribute<float>::setVertexAttribPointer(GLuint index)
    {
        glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, 0, 0);
    }

    template <>
    void VertexAttribute<macaque::vec2>::setVertexAttribPointer(GLuint index)
    {
        glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    template <>
    void VertexAttribute<macaque::vec3>::setVertexAttribPointer(GLuint index)
    {
        glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    template <>
    void VertexAttribute<macaque::vec4>::setVertexAttribPointer(GLuint index)
    {
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, 0, 0);
    }

    template <>
    void VertexAttribute<macaque::ivec4>::setVertexAttribPointer(GLuint index)
    {
        glVertexAttribIPointer(index, 4, GL_INT, 0, (void*)0);
    }

    template <typename T>
    void VertexAttribute<T>::set(const T* attribs, size_t attribCount)
    {
        mCount = attribCount;
        const auto size = sizeof(T);
        glBindBuffer(GL_ARRAY_BUFFER, mHandle);
        glBufferData(GL_ARRAY_BUFFER, size * mCount, attribs, GL_STREAM_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    template <typename T>
    void VertexAttribute<T>::bindTo(GLuint index)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mHandle);
        glEnableVertexAttribArray(index);
        setVertexAttribPointer(index);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    template <typename T>
    void VertexAttribute<T>::unbindFrom(GLuint index)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mHandle);
        glDisableVertexAttribArray(index);        
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
    size_t VertexAttribute<T>::getCount() const
    {
        return mCount;
    }

    template <typename T>
    GLuint VertexAttribute<T>::getHandle() const
    {
        return mHandle;
    }

} // namespace urus
