/**
* FIXMEs:
*   - Do not use glUniform* calls, use Uniform Buffers instead.
*   - read https://gamedev.stackexchange.com/questions/133615/how-do-you-store-uniform-data
*/
#include "uniform.h"

#include "vec.h"
#include "engine/base/OpenGLSupport.h"

namespace urus
{
    template Uniform<int>;
    template Uniform<float>;
    template Uniform<macaque::ivec2>;
    template Uniform<macaque::ivec4>;
    template Uniform<macaque::vec2>;
    template Uniform<macaque::vec3>;
    template Uniform<macaque::vec4>;

    // FIXME: quaternion and mat4 template specializations:
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

/**
* A helper macro to reduce boilerplate code of setting uniforms of different types
* (explicit specialization tailored for basic data types)
*/
#define UNIFORM_IMPL(gl_func, T, DataType) \
    template <> \
    void Uniform<T>::set(GLint index, const T* data, GLsizei dataLength) \
    { \
        if (dataLength) \
            gl_func(index, (GLsizei)dataLength, &data[0]); \
    }

/**
* Helper macro (similar to UNIFORM_IMPL), but tailored for vector data types 
* (i.e. vec*, ivec*)
* In current impl, a workaround with dereferencing (*data)[0] is used to call overloaded 
* operator[] instead of built-in indexer on the pointer (c-style array issue)
*/

#define UNIFORM_VEC_IMPL(gl_func, T, DataType) \
    template <> \
    void Uniform<T>::set(GLint index, const T* data, GLsizei dataLength) \
    { \
        if (dataLength) \
            gl_func(index, (GLsizei)dataLength, &((*data)[0])); \
    }
    
    UNIFORM_IMPL(glUniform1iv, int, int)
    UNIFORM_IMPL(glUniform1fv, float, float)
    UNIFORM_VEC_IMPL(glUniform2iv, macaque::ivec2, int)
    UNIFORM_VEC_IMPL(glUniform4iv, macaque::ivec4, int)
    UNIFORM_VEC_IMPL(glUniform2fv, macaque::vec2, float)
    UNIFORM_VEC_IMPL(glUniform3fv, macaque::vec3, float)
    UNIFORM_VEC_IMPL(glUniform4fv, macaque::vec4, float)

    // FIXME: fix quat & mat4 implementations
    // UNIFORM_IMPL(glUniform4fv, quat, float)

    // FIXME: implement all UNIFORM_IMPLs
    // template<> void 
    // Uniform<mat4>::set(unsigned int slot, mat4* matArray, unsigned int length)
    // {
    //    glUniformMatrix4fv(slot, (GLsizei)length, false, static_cast<float*>(&matArray));
    // }

} // namespace urus
