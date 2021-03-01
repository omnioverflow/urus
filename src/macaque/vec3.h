#pragma once

#include <cmath>

#include "macaque/mq_math.h"

/*
  FIXME:
    - define function isZero(T val) which internaly will compare to zero wrt EPSILON
    - usage of global functions might be a bad practice here
    - explicit vs implicit inlining?

  Temporary implementation notes:
    1. The definitions of a class template's member functions should appear in 
      the same header that contains the class template definition 
      (this is the most convenient portable way of using templates, 
      see discussion https://stackoverflow.com/questions/495021/)
    2. Related to (1.): https://stackoverflow.com/questions/16287178/
    3. functions that post-factum end up inlined must have definitions in each 
      translation unit (source + included headers).
    4. Prevent function inlining via #pragma auto_inline(off), __declspec(noinline)
       (https://docs.microsoft.com/en-us/cpp/build/reference/ob-inline-function-expansion?view=msvc-160)
*/

namespace macaque
{
    template <typename T>
    struct vec3_t
    {
        union
        {
            struct
            {
                T x;
                T y;
                T z;
            };

            T data[3];
        }; // anonymous union
        
        T& operator[] (int index) 
        { 
            return data[index]; 
        }

        friend vec3_t<T> operator+ (const vec3_t<T>& lhs, const vec3_t<T>& rhs)
        {
            return vec3_t<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
        }

        friend vec3_t<T> operator- (const vec3_t<T>& lhs, const vec3_t<T>& rhs)
        {
            return vec3_t<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
        }

        friend vec3_t<T> operator* (const vec3_t<T>& lhs, float scalar)
        {
            return vec3_t<T>(lhs.x * scalar, lhs.y * scalar, lhs.z * scalar);
        }

        friend vec3_t<T> operator* (const vec3_t<T>& lhs, const vec3_t<T>& rhs)
        {
            return vec3_t<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
        }

        friend bool operator== (const vec3_t<T>& lhs, const vec3_t<T>& rhs)
        {
            return isZero(lengthSq(lhs - rhs));
        }

        friend bool operator!= (const vec3_t<T>& lhs, const vec3_t<T>& rhs)
        {
            return !(lhs == rhs);
        }

        inline vec3_t() : x(0), y(0), z(0) {}
        inline vec3_t(T xval, T yval, T zval) : x(xval), y(yval), z(zval) {}
        inline vec3_t(const T* array) : x(array[0]), y(array[1]), z(array[2]) {}
    }; // struct vec3_t

    typedef vec3_t<float> vec3;
    typedef vec3_t<int> ivec3;

    /**
    * Cross product between the input vectors.
    */
    template <typename T>
    vec3_t<T> cross(const vec3_t<T>& a, const vec3_t<T>& b)
    {
        return vec3(a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x);
    }

    /**
    * Dot product.
    */
    template <typename T>
    inline float dot(const vec3_t<T>& a, const vec3_t<T>& b) 
    { 
        return a.x * b.x + a.y * b.y + a.z * b.z; 
    }

    /**
    * Squared lenght of the vector.
    */
    template <typename T>
    inline float lengthSq(const vec3_t<T>& v) 
    { 
        return dot(v, v); 
    }

    /**
    * Length of the vector.
    */
    template <typename T>
    float length(const vec3_t<T>& v)
    {
        const float lenSq = lengthSq(v);
        if (isZero(lenSq))
            return 0.f;

        return sqrtf(lenSq);
    }

    /**
    * Normalize the input vector so that it lenght is 1.
    */
    template <typename T>
    void normalize(vec3_t<T>& v)
    {
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
    vec3_t<T> normalized(const vec3_t<T>& v)
    {
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
    float angle(const vec3_t<T>& a, const vec3_t<T>& b)
    {
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
    vec3_t<T> projection(const vec3_t<T>& a, const vec3_t<T>& b)
    {
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
    vec3_t<T> rejection(const vec3_t<T>& a, const vec3_t<T>& b)
    {
        vec3 projA = projection(a, b);
        return a - projA;
    }

    /**
     * Bounce reflection of a with respect to n (as if n was a normal to the 
     * bounce sourface)
     */
    template <typename T>
    vec3_t<T> reflect(const vec3_t<T>& a, const vec3_t<T>& n)
    {
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
    vec3_t<T> lerp(const vec3_t<T>& v0, const vec3_t<T>& v1, float t)
    {
        return vec3(v0.x + (v1.x - v0.x) * t,
                    v0.y + (v1.y - v0.y) * t,
                    v0.z + (v1.z - v0.z) * t);
    }

    /**
     * Spherical linear interpolation between the input vectors.
     */
    template <typename T>
    vec3_t<T> slerp(const vec3_t<T>& v0, const vec3_t<T>& v1, float t)
    {
        if(t < 0.01f) // FIXME: declare in constants to avoid magic number stuff
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
    vec3_t<T> nlerp(const vec3_t<T>& v0, const vec3_t<T>& v1, float t)
    {
        return normalized(lerp(v0, v1, t));
    }

} // namespace macaque
