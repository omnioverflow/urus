#pragma once

namespace macaque
{
    template <typename T>
    struct base_vec2
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

        inline base_vec2() : x(T(0)), y(T(0)) {}
        inline base_vec2(T xval, T yval) : x(xval), y(yval) {}
        inline base_vec2(const T* vec_ptr) : x(vec_ptr[0]), y(vec_ptr[1]) {}
    }; // struct base_vec2

    typedef base_vec2<float> vec2;
    typedef base_vec2<int> ivec2;
} // namespace macaque
