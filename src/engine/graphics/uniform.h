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

            Uniform(const Uniform&) = delete;
            Uniform& operator=(const Uniform&) = delete;

            static void set(unsigned int index, const T& value);
            static void set(unsigned int index, const T* arr, unsigned int len);
            static void set(unsigned int index, std::vector<T>& vec);

        private:
            Uniform();
    }; // class Uniform
} // namespace urus
