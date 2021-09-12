#pragma once

#include <iostream>

namespace mq
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

        // --------------------------------------------------------------------
        // Operators
        // --------------------------------------------------------------------
        T& operator[] (int index);
        const T& operator[] (int index) const;
        vec2_t<T>& operator+= (const vec2_t<T>& rhs);
        vec2_t<T> operator+ (const vec2_t<T>& rhs) const;
        vec2_t<T>& operator-= (const vec2_t<T>& rhs);
        vec2_t<T> operator- (const vec2_t<T>& rhs) const;
        vec2_t<T>& operator*= (float scalar);
        vec2_t<T> operator* (float scalar) const;
        friend vec2_t<T> operator* (float scalar, const vec2_t<T>& rhs);
        friend std::ostream& operator<< (std::ostream& os, 
            const vec2_t<T>& rhs);
        friend std::istream& operator>> (const std::istream& is,
            vec2_t<T>& rhs);
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

    template <typename T>
    vec2_t<T>& vec2_t<T>::operator+= (const vec2_t<T>& rhs) {
        (*this)[0] += rhs[0];
        (*this)[1] += rhs[1];
        return *this;
    }
    
    template <typename T>
    vec2_t<T> vec2_t<T>::operator+ (const vec2_t<T>& rhs) const {
        auto temp(*this);
        temp += rhs;
        return temp;
    }

    template <typename T>
    vec2_t<T>& vec2_t<T>::operator-= (const vec2_t<T>& rhs) {
        (*this)[0] -= rhs[0];
        (*this)[1] -= rhs[1];
        return *this;
    }

    template <typename T>
    vec2_t<T> vec2_t<T>::operator- (const vec2_t<T>& rhs) const {
        auto temp(*this);
        temp -= rhs;
        return temp;
    }

    template <typename T>
    vec2_t<T>& vec2_t<T>::operator*= (float scalar) {
        (*this)[0] *= scalar;
        (*this)[1] *= scalar;
        return *this;
    }

    template <typename T>
    vec2_t<T> vec2_t<T>::operator* (float scalar) const {
        auto temp(*this);
        temp *= scalar;
        return temp;
    }

    // ------------------------------------------------------------------------
    // Non-member operators
    // ------------------------------------------------------------------------
    template <typename T>
    vec2_t<T> operator* (float scalar, const vec2_t<T>& rhs) {
        auto temp(vector);
        temp *= scalar;
        return temp;
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& os, const vec2_t<T>& rhs) {
        return os << vec2[0] << std::endl << vec2[1] << std::endl;
    }

    template <typename T>
    std::istream& operator>> (const std::istream& is, vec2_t<T>& rhs) {
        return is >> vec[0] >> vec[1];
    }
} // namespace mq
