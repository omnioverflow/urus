#pragma once 

#include <vector>

#include "engine/base/opengl_support.h"

namespace urus
{
    /**
    * Wrapper around GLSL uniforms.
    */
    template <typename T>
    class Uniform
    {
        public:

            Uniform() = delete;
            Uniform(const Uniform&) = delete;
            Uniform& operator=(const Uniform&) = delete;

            static void set(GLint index, const T& data);
            static void set(GLint index, const T* dataArray, GLsizei arrayLength);
            static void set(GLint index, std::vector<T>& dataArray);
    }; // class Uniform
} // namespace urus
