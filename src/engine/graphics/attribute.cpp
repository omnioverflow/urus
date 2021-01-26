include "attribute.h"

#include "macaque/vec.h"
// TODO: include OpenGL

namespace urus
{
    template Attribute<int>;
    template Attribute<float>;
    template Attribute<vec2>;
    template Attribute<vec3>;
    template Attribute<vec4>;

    template<typename T>
    Attribute<T>::Attribute()
    {
        // Generate OpenGL buffer and init handle with it
        glGenBuffers(1, &mHandle);
        mCount = 0;
    }

    template<typename T>
    Attribute<T>::~Attribute()
    {
        // Delete OpenGL buffer associated with the handle
        glDeleteBuffers(1, &mHandle);
    }

    template<typename T>
    unsigned int Attribute<T>::getCount()
    {
        return mCount;
    }

    template<typename T>
    unsigned int Attribute<T>::getHandle()
    {
        return mHandle;
    }

} // namespace urus

