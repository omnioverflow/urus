#include "uniform.h"

// FIXME: include OpenGL headers

namespace urus
{
    // FIXME: define integer vector, quaternion and mat4
    // template specializations:
    template Uniform<int>;
    // template Uniform<ivec2>;
    // template Uniform<ivec4>;
    template Uniform<float>;
    template Unifrom<vec2>;
    template Uniform<vec3>;
    template Uniform<vec4>;
    // template Uniform<quat>;
    //template Uniform<mat4>;
    
    template <typename T>
    void Uniform<T>::set(unsigned int slot, const T& value)
    {
        set(slot, static_cast<T*>(&value), 1);
    }

    template <typename T>
    void Uniform<T>::set(unsigned int slot, std::vector<T>& vec)
    {
        const auto vecSize = vec.size();
        if (vecSize)
            set(slot, &vec.data(), vecSize);
    }


// A helper macro to reduce boilerplate code of setting uniforms of different types
#define UNIFORM_IMPL(gl_func, tType, dType) \
    template<> void \
    Uniform<tType>::set<unsigned int slot, tType* data, unsigned int length) \
    { \
        if (length) \
            gl_func(slot, (GLsizei)length, static_cast<dType*>(&data[0])); \
    }

    UNIFORM_IMPL(glUniform1iv, int, int)
    // UNIFORM_IMPL(glUniform2iv, ivec2, int)
    // UNIFORM_IMPL(glUniform4iv, ivec4, int)
    UNIFORM_IMPL(glUniform1fv, float, float)
    UNIFORM_IMPL(glUniform2fv, vec2, float)
    UNIFORM_IMPL(glUniform3fv, vec3, float)
    UNIFORM_IMPL(glUniform4fv, vec4, float)
    // UNIFORM_IMPL(glUniform4fv, quat, float)

    // FIXME: implement all UNIFORM_IMPLs
    // template<> void 
    // Uniform<mat4>::set(unsigned int slot, mat4* matArray, unsigned int length)
    // {
    //    glUniformMatrix4fv(slot, (GLsizei)length, false, static_cast<float*>(&matArray));
    // }

} // namespace urus
