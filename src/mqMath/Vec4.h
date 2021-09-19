#pragma once 

#include <iostream>

namespace mq 
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
            vec4_t<T>& operator+= (const vec4_t<T>& rhs);
            vec4_t<T> operator+ (const vec4_t<T>& rhs) const;
            vec4_t<T>& operator- ();
            vec4_t<T> operator-() const;
            vec4_t<T>& operator-= (const vec4_t<T>& rhs);
            vec4_t<T> operator- (const vec4_t<T>& rhs) const;
            vec4_t<T>& operator*= (float scalar);
            friend vec4_t<T> operator* (const vec4_t<T>& lhs, float scalar);
            friend vec4_t<T> operator* (float scalar, const vec4_t<T>& rhs);
            friend std::ostream& operator<< (std::ostream& os, 
                const vec4_t<T>& rhs);
            friend std::istream& operator>> (const std::istream& is, 
                vec4_t<T>& rhs);
        }; // struct vec4_t

    typedef vec4_t<float> vec4;
    typedef vec4_t<int> ivec4;
    typedef vec4_t<unsigned int> uivec4;

    /**
    * Normalize non-const input vector.
    */
    template <typename T>
    void normalize(vec4_t<T>& v);

    /**
    * Return normalized vector obtained from input vector.
    */
    template <typename T>
    vec4_t<T> normalized(const vec4_t<T>& v);

} // namespace mq
