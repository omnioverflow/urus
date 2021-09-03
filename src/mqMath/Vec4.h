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

                T data[4];
            };

            inline vec4_t<T>() : x((T)0), y((T)0), w((T)0) {}
            inline vec4_t<T>(T xval, T yval, T zval, T wval) : x(xval), y(yval), z(zval), w(wval) {}
            inline vec4_t<T>(const T* array) : x(array[0]), y(array[1]), z(array[2]), w(array[3]) {}

            T& operator[] (int index);
            const T& operator[] (int index) const;
        }; // struct vec4_t

    typedef vec4_t<float> vec4;
    typedef vec4_t<int> ivec4;
    typedef vec4_t<unsigned int> uivec4;

    template <typename T>
    inline T& vec4_t<T>::operator[] (int index)
    {
        return data[index];
    }

    template <typename T>
    inline const T& vec4_t<T>::operator[] (int index) const
    {
        return data[index];
    }
} // namespace macaque
