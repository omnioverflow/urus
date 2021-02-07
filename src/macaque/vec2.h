#pragma once

namespace macaque
{
    template <typename T>
    struct vec2_t
    {
        union
        {
            struct 
            {
                T x;
                T y;
            };

            T v[2];
        }; // union

        inline vec2_t() : x(T(0)), y(T(0)) {}
        inline vec2_t(T xval, T yval) : x(xval), y(yval) {}
        inline vec2_t(const T* array) : x(array[0]), y(array[1]) {}
    }; // struct base_vec2

    typedef vec2_t<float> vec2;
    typedef vec2_t<int> ivec2;
} // namespace macaque
