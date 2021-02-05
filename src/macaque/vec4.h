#pragma once 

namespace macaque 
{
    template <typename T>
        struct vec4_t
        {
            union 
            {
                struct
                {
                    T x;
                    T y;
                    T z;
                    T w;
                };

                T v[4];
            };

            inline vec4_t<T>() : x((T)0), y((T)0), w((T)0) {}
            inline vec4_t<T>(T xval, T yval, T zval, T wval) : x(xval), y(yval), z(zval), w(wval) {}
            inline vec4_t<T>(const T* data) : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}
        }; // struct vec4_t

    typedef vec4_t<float> vec4;
    typedef vec4_t<int> ivec4;
    typedef vec4_t<unsigned int> uivec4;
} // namespace macaque
