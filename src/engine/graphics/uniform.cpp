/**
* FIXMEs:
*   - Do not use glUniform* calls, use Uniform Buffers instead.
*/
#include "uniform.h"

#include "vec.h"
#include "engine/base/opengl_support.h"

namespace urus
{
    // FIXME: define integer vector, quaternion and mat4
    // template specializations:
    template Uniform<int>;
    // template Uniform<ivec2>;
    // template Uniform<ivec4>;
    template Uniform<float>;
    // FIXME: plug back uniform implementations for vec2, vec3, vec4
    // FIXME: template Uniform<macaque::vec2>;
    // FIXME: template Uniform<macaque::vec3>;
    // FIXME: template Uniform<macaque::vec4>;


    // template Uniform<quat>;
    //template Uniform<mat4>;
    
    template <typename T>
    void Uniform<T>::set(GLint index, const T& data)
    {
        set(index, static_cast<const T*>(&data), 1);
    }

    template <typename T>
    void Uniform<T>::set(GLint index, std::vector<T>& data)
    {
        const auto dataLength = data.size();
        if (dataLength)
            set(index, data.data(), dataLength);
    }

// A helper macro to reduce boilerplate code of setting uniforms of different types
#define UNIFORM_IMPL(gl_func, T, DataType) \
    template <> \
    void Uniform<T>::set(GLint index, const T* data, GLsizei dataLength) \
    { \
        if (dataLength) \
            gl_func(index, (GLsizei)dataLength, &data[0]); \
    }

    UNIFORM_IMPL(glUniform1iv, int, int)

    // UNIFORM_IMPL(glUniform2iv, ivec2, int)
    // UNIFORM_IMPL(glUniform4iv, ivec4, int)

    UNIFORM_IMPL(glUniform1fv, float, float)
    // FIXME: plug back uniform implementations for vec2, vec3, vec4
    // UNIFORM_IMPL(glUniform2fv, macaque::vec2, float)
    // UNIFORM_IMPL(glUniform3fv, macaque::vec3, float)
    // UNIFORM_IMPL(glUniform4fv, macaque::vec4, float)

    // UNIFORM_IMPL(glUniform4fv, quat, float)

    // FIXME: implement all UNIFORM_IMPLs
    // template<> void 
    // Uniform<mat4>::set(unsigned int slot, mat4* matArray, unsigned int length)
    // {
    //    glUniformMatrix4fv(slot, (GLsizei)length, false, static_cast<float*>(&matArray));
    // }

} // namespace urus
