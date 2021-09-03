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

            T data[2];
        }; // anonymous union

        inline vec2_t() : x(T(0)), y(T(0)) {}
        inline vec2_t(T xval, T yval) : x(xval), y(yval) {}
        inline vec2_t(const T* array) : x(array[0]), y(array[1]) {}

        T& operator[] (int index);
        const T& operator[] (int index) const;
    }; // struct base_vec2

    typedef vec2_t<float> vec2;
    typedef vec2_t<int> ivec2;

    template <typename T>
    inline T& vec2_t<T>::operator[] (int index)
    {
        return data[index];
    }

    template <typename T>
    inline const T& vec2_t<T>::operator[] (int index) const
    {
        return data[index];
    }
} // namespace macaque
