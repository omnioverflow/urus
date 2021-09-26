#pragma once

#include <cmath>
#include <iostream>

#include "MqMath.h"

namespace mq {

// -------------------------------------------------------------------------
// vec3
// -------------------------------------------------------------------------

    template <typename T>
    struct vec3_t
    {
        union
        {
            struct {
                T x;
                T y;
                T z;
            };

            T data[3];
        }; // anonymous union

        vec3_t();
        vec3_t(T xval, T yval, T zval);
        explicit vec3_t(const T* array);
        
        T& operator[] (int index);
        const T& operator[] (int index) const;

        static vec3_t<T> getZero();
    }; // struct vec3_t

    typedef vec3_t<float> vec3;
    typedef vec3_t<int> ivec3;

    /**
    * Cross product between the input vectors.
    */
    template <typename T>
    vec3_t<T> cross(const vec3_t<T>& a, const vec3_t<T>& b);

    /**
    * Dot product.
    */
    template <typename T>
    float dot(const vec3_t<T>& a, const vec3_t<T>& b);

    /**
    * Squared lenght of the vector.
    */
    template <typename T>
    float lengthSq(const vec3_t<T>& v);

    /**
    * Length of the vector.
    */
    template <typename T>
    float length(const vec3_t<T>& v);

    /**
    * Normalize the input vector so that it lenght is 1.
    */
    template <typename T>
    void normalize(vec3_t<T>& v);

    /**
    * Return a normalized vector obtained from the input vector.
    */
    template <typename T>
    vec3_t<T> normalize(const vec3_t<T>& v);

    /**
    * Compute and return the angle between the vectors.
    */
    template <typename T>
    float angle(const vec3_t<T>& a, const vec3_t<T>& b);

    /**
     * Vector projection of a on b.
     */
    template <typename T>
    vec3_t<T> projection(const vec3_t<T>& a, const vec3_t<T>& b);

    /**
     * Vector rejection.
     * The vector rejection of a on b is a vector a2 which is either null or orthogonal to b.
     * (see https://en.wikipedia.org/wiki/Vector_projection#Vector_rejection_3)
     */
    template <typename T>
    vec3_t<T> rejection(const vec3_t<T>& a, const vec3_t<T>& b);

    /**
     * Bounce reflection of a with respect to n (as if n was a normal to the 
     * bounce sourface)
     */
    template <typename T>
    vec3_t<T> reflect(const vec3_t<T>& a, const vec3_t<T>& n);

    /**
     * Linear interpolation between the input vectors.
     */    
    template <typename T>
    vec3_t<T> lerp(const vec3_t<T>& v0, const vec3_t<T>& v1, float t);

    /**
     * Spherical linear interpolation between the input vectors.
     */
    template <typename T>
    vec3_t<T> slerp(const vec3_t<T>& v0, const vec3_t<T>& v1, float t);

    /**
     * Normalized linear interpolation between the input vectors.
     */
    template <typename T>
    vec3_t<T> nlerp(const vec3_t<T>& v0, const vec3_t<T>& v1, float t);

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

    template <typename T>
    vec3_t<T>::vec3_t() : x(0), y(0), z(0) {}

    template <typename T>
    vec3_t<T>::vec3_t(T xval, T yval, T zval) : x(xval), y(yval), z(zval) {}

    template <typename T>
    vec3_t<T>::vec3_t(const T* array)
    : x(array[0]), y(array[1]), z(array[2]) {}

    // ------------------------------------------------------------------------
    // Member operators
    // ------------------------------------------------------------------------

    template <typename T>
    T& vec3_t<T>::operator[] (int index) {
        return data[index];
    }

    template <typename T>
    const T& vec3_t<T>::operator[] (int index) const {
        return data[index];
    }

    // ------------------------------------------------------------------------
    // Non-member operators
    // ------------------------------------------------------------------------

    template <typename T>
    vec3_t<T>& operator+= (vec3_t<T>& lhs, const vec3_t<T>& rhs) {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        lhs.z += rhs.z;
        return lhs;
    }

    template <typename T>
    vec3_t<T> operator+ (const vec3_t<T>& lhs, const vec3_t<T>& rhs) {
        auto temp(lhs);
        temp += rhs;
        return temp;        
    }

    template <typename T>
    vec3_t<T>& operator-= (vec3_t<T>& lhs, const vec3_t<T>& rhs) {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        lhs.z -= rhs.z;
        return lhs;
    }

    template <typename T>
    vec3_t<T> operator- (const vec3_t<T>& lhs, const vec3_t<T>& rhs) {
        auto temp(lhs);
        temp -= rhs;
        return temp;
    }

    template <typename T>
    vec3_t<T>& operator*= (vec3_t<T>& lhs, float scalar) {
        lhs.x *= scalar;
        lhs.y *= scalar;
        lhs.z *= scalar;

        return lhs;
    }

    template <typename T>
    vec3_t<T> operator* (const vec3_t<T>& lhs, float scalar) {
        auto temp(lhs);
        temp *= scalar;
        return temp;
    }

    template <typename T>
    vec3_t<T> operator* (float scalar, const vec3_t<T>& rhs) {
        auto temp(rhs);
        temp *= scalar;
        return temp;
    }

    template <typename T>
    vec3_t<T>& operator*= (vec3_t<T>& lhs, const vec3_t<T>& rhs) {
        lhs.x *= rhs.x;
        lhs.y *= rhs.y;
        lhs.z *= rhs.z;
        return lhs;
    }

    template <typename T>
    vec3_t<T> operator* (const vec3_t<T>& lhs, const vec3_t<T>& rhs) {
        auto temp(lhs);
        temp *= rhs;
        return temp;
    }

    template <typename T>
    bool operator== (const vec3_t<T>& lhs, const vec3_t<T>& rhs) {
        return isZero(lengthSq(lhs - rhs));
    }

    template <typename T>
    bool operator!= (const vec3_t<T>& lhs, const vec3_t<T>& rhs) {
        return !(lhs == rhs);
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& os, const vec3_t<T>& rhs) {
        return os << rhs[0] << ", " << rhs[1] << ", " << rhs[2];
    }

    template <typename T>
    std::istream& operator>> (std::istream& is, vec3_t<T>& rhs) {
        return is >> rhs[0] >> rhs[1] >> rhs[2];
    }

    template <typename T>
    vec3_t<T> vec3_t<T>::getZero() { return vec3_t(0, 0, 0); }

    // ------------------------------------------------------------------------
    // Helper functions
    // ------------------------------------------------------------------------
    /**
    * Cross product between the input vectors.
    */
    template <typename T>
    vec3_t<T> cross(const vec3_t<T>& a, const vec3_t<T>& b) {
        return vec3(a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
    }

    /**
    * Dot product.
    */
    template <typename T>
    float dot(const vec3_t<T>& a, const vec3_t<T>& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    /**
    * Squared lenght of the vector.
    */
    template <typename T>
    float lengthSq(const vec3_t<T>& v) {
        return dot(v, v);
    }

    /**
    * Length of the vector.
    */
    template <typename T>
    float length(const vec3_t<T>& v) {
        const float lenSq = lengthSq(v);
        if (isZero(lenSq))
            return 0.f;

        return sqrtf(lenSq);
    }

    /**
    * Normalize the input vector so that it lenght is 1.
    */
    template <typename T>
    void normalize(vec3_t<T>& v) {
        const float lenSq = lengthSq(v);
        if (isZero(lenSq))
            return;

        const float invLen = 1.f / sqrtf(lenSq);
        v.x *= invLen;
        v.y *= invLen;
        v.z *= invLen;
    }

    /**
    * Return a normalized vector obtained from the input vector.
    */
    template <typename T>
    vec3_t<T> normalize(const vec3_t<T>& v) {
        const float lenSq = lengthSq(v);
        if (isZero(lenSq))
            return v;

        const float invLen = 1.f / sqrtf(lenSq);
        return vec3(v.x * invLen, v.y * invLen, v.z * invLen);
    }

    /**
    * Compute and return the angle between the vectors.
    */
    template <typename T>
    float angle(const vec3_t<T>& a, const vec3_t<T>& b) {
        const float lengthA = length(a);
        const float lengthB = length(b);
        if (isZero(lengthA) || isZero(lengthB))
            return 0.f;

        return acosf(dot(a, b) / (lengthA + lengthB));
    }
    /**
     * Vector projection of a on b.
     */
    template <typename T>
    vec3_t<T> projection(const vec3_t<T>& a, const vec3_t<T>& b) {
        const float lengthB = length(b);
        if (isZero(lengthB))
            return vec3();

        const auto scale = dot(a, b) / lengthB;
        return b * scale;
    }

    /**
     * Vector rejection.
     * The vector rejection of a on b is a vector a2 which is either null or orthogonal to b.
     * (see https://en.wikipedia.org/wiki/Vector_projection#Vector_rejection_3)
     */
    template <typename T>
    vec3_t<T> rejection(const vec3_t<T>& a, const vec3_t<T>& b) {
        vec3 projA = projection(a, b);
        return a - projA;
    }

    /**
     * Bounce reflection of a with respect to n (as if n was a normal to the
     * bounce sourface)
     */
    template <typename T>
    vec3_t<T> reflect(const vec3_t<T>& a, const vec3_t<T>& n) {
        const float lengthB = length(n);
        if (isZero(lengthB))
            return vec3();

        const float scale = dot(a, n) / lengthB;
        vec3 proj2 = n * (scale * 2);

        return a - proj2;
    }

    /**
     * Linear interpolation between the input vectors.
     */
    template <typename T>
    vec3_t<T> lerp(const vec3_t<T>& v0, const vec3_t<T>& v1, float t) {
        return vec3(v0.x + (v1.x - v0.x) * t,
            v0.y + (v1.y - v0.y) * t,
            v0.z + (v1.z - v0.z) * t);
    }

    /**
     * Spherical linear interpolation between the input vectors.
     */
    template <typename T>
    vec3_t<T> slerp(const vec3_t<T>& v0, const vec3_t<T>& v1, float t) {
        if (t < 0.01f) // FIXME: declare in constants to avoid magic number stuff
            return lerp(v0, v1, t);

        const vec3 from = normalized(v0);
        const vec3 to = normalized(v1);
        const float theta = angle(from, to);
        const float sinTheta = sinf(theta);
        const float a = sinf((1.f - t) * theta) / sinTheta;
        const float b = sinf(t * theta) / sinTheta;
        return from * a + to * b;
    }

    /**
     * Normalized linear interpolation between the input vectors.
     */
    template <typename T>
    vec3_t<T> nlerp(const vec3_t<T>& v0, const vec3_t<T>& v1, float t) {
        return normalized(lerp(v0, v1, t));
    }

} // namespace mq
