#pragma once

#include <iostream>

namespace mq {
    // forward declare vec3_t
    template <typename T> struct vec3_t;

    // -------------------------------------------------------------------------
    // vec4
    // -------------------------------------------------------------------------
    template <typename T>
    struct vec4_t
    {
        union 
        {
            struct {
                T x;
                T y;
                T z;
                T w;
            };

            T data[4];
        }; // anonymous union

        vec4_t<T>();
        vec4_t<T>(T xval, T yval, T zval, T wval);
        vec4_t<T>(const T* array);
        vec4_t<T>(const vec3_t<T>& v, T wval);

        T& operator[] (int index);
        const T& operator[] (int index) const;
        vec4_t<T>& operator+= (const vec4_t<T>& rhs);
        vec4_t<T> operator+ (const vec4_t<T>& rhs) const;
        vec4_t<T>& operator- ();
        vec4_t<T> operator- () const;
        vec4_t<T>& operator-= (const vec4_t<T>& rhs);
        vec4_t<T> operator- (const vec4_t<T>& rhs) const;
        vec4_t<T>& operator*= (float scalar);

        template <typename U>
        friend vec4_t<U> operator* (const vec4_t<U>& lhs, float scalar);

        template <typename U>
        friend vec4_t<U> operator* (float scalar, const vec4_t<U>& rhs);

        template <typename U>
        friend std::ostream& operator<< (std::ostream& os, const vec4_t<U>& rhs);

        template <typename U>
        friend std::istream& operator>> (const std::istream& is, vec4_t<U>& rhs);
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
    vec4_t<T> normalize(const vec4_t<T>& v);

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

    /**
    * Compute cross-product. 
    */
    template <typename T>
    vec4_t<T> cross(const vec4_t<T>& a, const vec4_t<T>& b);
    template <typename T>
    vec4_t<T>::vec4_t() : x((T)0), y((T)0), w((T)0) {}

    template <typename T>
    vec4_t<T>::vec4_t(T xval, T yval, T zval, T wval)
    : x(xval), y(yval), z(zval), w(wval) {}

    template <typename T>
    vec4_t<T>::vec4_t(const T* array)
    : x(array[0]), y(array[1]), z(array[2]), w(array[3]) {}

    template <typename T>
    vec4_t<T>::vec4_t(const vec3_t<T>& v, T wval)
    : x(v[0]), y(v[1]), z(v[2]), w(wval) {}

    // -------------------------------------------------------------------------
    // Member operators
    // -------------------------------------------------------------------------
    template <typename T>
    T& vec4_t<T>::operator[] (int index) {
        return data[index];
    }

    template <typename T>
    const T& vec4_t<T>::operator[] (int index) const {
        return data[index];
    }

    template <typename T>
    vec4_t<T>& vec4_t<T>::operator+= (const vec4_t<T>& rhs) {
        (*this)[0] += rhs[0];
        (*this)[1] += rhs[1];
        (*this)[2] += rhs[2];
        (*this)[3] += rhs[3];
        return *this;
    }

    template <typename T>
    vec4_t<T> vec4_t<T>::operator+ (const vec4_t<T>& rhs) const {
        auto temp(*this);
        temp += rhs;
        return temp;
    }

    template <typename T>
    vec4_t<T>& vec4_t<T>::operator- () {
        (*this)[0] = -(*this)[0];
        (*this)[1] = -(*this)[1];
        (*this)[2] = -(*this)[2];
        (*this)[3] = -(*this)[3];
        return *this;
    }

    template <typename T>
    vec4_t<T> vec4_t<T>::operator- () const {
        return -(*this);
    }

    template <typename T>
    vec4_t<T>& vec4_t<T>::operator-= (const vec4_t<T>& rhs) {
        (*this) += -(*this);
        return *this;
    }

    template <typename T>
    vec4_t<T> vec4_t<T>::operator- (const vec4_t<T>& rhs) const {
        auto temp(*this);
        temp -= rhs;
        return temp;
    }

    template <typename T>
    vec4_t<T>& vec4_t<T>::operator*= (float scalar) {
        (*this)[0] *= scalar;
        (*this)[1] *= scalar;
        (*this)[2] *= scalar;
        (*this)[3] *= scalar;
        return *this;
    }

    // -------------------------------------------------------------------------
    // Non-member operators
    // -------------------------------------------------------------------------
    template <typename T>
    vec4_t<T> operator* (const vec4_t<T>& lhs, float scalar) {
        auto temp(lhs);
        temp *= scalar;
        return temp;
    }

    template <typename T>
    vec4_t<T> operator* (float scalar, const vec4_t<T>& rhs) {
        return rhs * scalar;
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& os, const vec4_t<T>& rhs) {
        return os << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w;
    }

    template <typename T>
    std::istream& operator>> (std::istream& is, vec4_t<T>& rhs) {
        return is >> rhs[0] >> rhs[1] >> rhs[2] >> rhs[3];
    }

    template <typename T>
    void normalize(vec4_t<T>& v) {
        const auto lenSq = lengthSq(v);
        if (!isZero(lenSq)) {
            const auto inverseLength = 1.f / sqrtf(lenSq);
            v.x *= inverseLength;
            v.y *= inverseLength;
            v.z *= inverseLength;
            v.w *= inverseLength;
        }
    }

    template <typename T>
    vec4_t<T> normalize(const vec4_t<T>& v) {
        auto temp(v);
        return normalize(temp);
    }

    template <typename T>
    vec4_t<T> cross(const vec4_t<T>& a, const vec4_t<T>& b) {

    }

} // namespace mq
