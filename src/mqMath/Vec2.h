#pragma once

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

        T& operator[] (int index);
        const T& operator[] (int index) const;
        vec2_t<T>& operator+= (const vec2_t<T>& rhs);
        vec2_t<T> operator+ (const vec2_t<T>& rhs) const;
        vec2_t<T>& operator-= (const vec2_t<T>& rhs);
        vec2_t<T> operator- (const vec2_t<T>& rhs) const;
        vec2_t<T>& operator* (float scalar);
        friend vec2_t<T> operator* (float scalar, const vec2_t<T>& vector);
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
    vec2_t<T>& vec2_t<T>::operator* (float scalar) {
        (*this)[0] *= scalar;
        (*this)[1] *= scalar;
        return *this;
    }

    // Non-member operator for scalar multiplication
    template <typename T>
    vec2_t<T> operator* (float scalar, const vec2_t<T>& vector) {
        auto temp(vector);
        temp *= scalar;
        return temp;
    }
} // namespace mq
