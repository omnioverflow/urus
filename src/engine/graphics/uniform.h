#pragma once 

#include <vector>

namespace urus
{
    template <typename T>
    class Uniform
    {
        public:

            Uniform(const Uniform&) = delete;
            Uniform& operator=(const Uniform&) = delete;

            static void set(unsigned int slot, const T& value);
            static void set(unsigned int slot, T* arr, unsigned int len);
            static void set(unsigned int slot, std::vector<T>& vec);

        private:
            Uniform();
    }; // class Uniform
} // namespace urus
