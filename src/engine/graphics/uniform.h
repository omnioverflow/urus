#pragma once 

#include <vector>

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

            static void set(unsigned int index, const T& data);
            static void set(unsigned int index, const T* dataArray, unsigned int arrayLength);
            static void set(unsigned int index, std::vector<T>& dataArray);
    }; // class Uniform
} // namespace urus
