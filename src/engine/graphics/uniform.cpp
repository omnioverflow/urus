#include "uniform.h"
#include "vec.h"

// FIXME: include OpenGL headers

namespace urus
{
    // FIXME: define integer vector, quaternion and mat4
    // template specializations:
    template Uniform<int>;
    // template Uniform<ivec2>;
    // template Uniform<ivec4>;
    template Uniform<float>;
    template Uniform<macaque::vec2>;
    template Uniform<macaque::vec3>;
    template Uniform<macaque::vec4>;
    // template Uniform<quat>;
    //template Uniform<mat4>;
    
    template <typename T>
    void Uniform<T>::set(unsigned int index, const T& data)
    {
        set(index, static_cast<const T*>(&value), 1);
    }

    template <typename T>
    void Uniform<T>::set(unsigned int index, std::vector<T>& dataArray)
    {
        const auto vecSize = vec.size();
        if (vecSize)
            set(index, vec.data(), vecSize);
    }

// A helper macro to reduce boilerplate code of setting uniforms of different types
#define UNIFORM_IMPL(gl_func, T, Data) \
    template<> \
    void Uniform<T>::set(unsigned int index, const T* dataArray, unsigned int arrayLength) \
    { \
        if (arrayLength) \
            gl_func(index, (GLsizei)arrayLength, static_cast<const Data*>(&dataArray[0])); \
    }

    UNIFORM_IMPL(glUniform1iv, int, int)

    // UNIFORM_IMPL(glUniform2iv, ivec2, int)
    // UNIFORM_IMPL(glUniform4iv, ivec4, int)

    UNIFORM_IMPL(glUniform1fv, float, float)
    UNIFORM_IMPL(glUniform2fv, macaque::vec2, float)
    UNIFORM_IMPL(glUniform3fv, macaque::vec3, float)
    UNIFORM_IMPL(glUniform4fv, macaque::vec4, float)

    // UNIFORM_IMPL(glUniform4fv, quat, float)

    // FIXME: implement all UNIFORM_IMPLs
    // template<> void 
    // Uniform<mat4>::set(unsigned int slot, mat4* matArray, unsigned int length)
    // {
    //    glUniformMatrix4fv(slot, (GLsizei)length, false, static_cast<float*>(&matArray));
    // }

} // namespace urus
