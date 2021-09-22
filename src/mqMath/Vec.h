#pragma once

#include <cmath>
#include <iostream>
#include <vector>

#include "mqMath/MqMath.h"

namespace mq
{
    /*
      FIXME:
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

    // -------------------------------------------------------------------------
    // vec2
    // -------------------------------------------------------------------------
    template <typename T>
    struct vec2_t
    {
        union
        {
            struct {
                T x;
                T y;
            };

            T data[2];
        }; // anonymous union

         vec2_t();
         vec2_t(T xval, T yval);
         explicit vec2_t(const T* array);

        // ---------------------------------------------------------------------
        // Operators
        // ---------------------------------------------------------------------
        T& operator[] (int index);
        const T& operator[] (int index) const;
        vec2_t<T>& operator+= (const vec2_t<T>& rhs);
        vec2_t<T> operator+ (const vec2_t<T>& rhs) const;
        vec2_t<T>& operator-= (const vec2_t<T>& rhs);
        vec2_t<T> operator- (const vec2_t<T>& rhs) const;
        vec2_t<T>& operator*= (float scalar);
        vec2_t<T> operator* (float scalar) const;
        friend vec2_t<T> operator* (float scalar, const vec2_t<T>& rhs);
        friend std::ostream& operator<< (std::ostream& os, const vec2_t<T>& rhs);
        friend std::istream& operator>> (const std::istream& is, vec2_t<T>& rhs);
    }; // struct base_vec2

    typedef vec2_t<float> vec2;
    typedef vec2_t<int> ivec2;

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

        friend vec3_t<T>& operator+= (vec3_t<T>& lhs, const vec3_t<T>& rhs);
        friend vec3_t<T> operator+ (const vec3_t<T>& lhs, const vec3_t<T>& rhs);
        friend vec3_t<T>& operator-= (vec3_t<T>& lhs, const vec3_t<T>& rhs);
        friend vec3_t<T> operator- (const vec3_t<T>& lhs, const vec3_t<T>& rhs);
        friend vec3_t<T>& operator*= (vec3_t<T>& lhs, float scalar);
        friend vec3_t<T> operator* (const vec3_t<T>& lhs, float scalar);
        friend vec3_t<T> operator* (float scalar, const vec3_t<T>& rhs);
        friend vec3_t<T>& operator*= (vec3_t<T>& lhs, const vec3_t<T>& rhs);
        friend vec3_t<T> operator* (const vec3_t<T>& lhs, const vec3_t<T>& rhs);
        friend bool operator== (const vec3_t<T>& lhs, const vec3_t<T>& rhs);
        friend bool operator!= (const vec3_t<T>& lhs, const vec3_t<T>& rhs);
        friend std::ostream operator<< (std::ostream& os, const vec3_t<T>& rhs);
        friend std::istream operator>> (std::istream& is, vec3_t<T>& rhs);

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
        friend vec4_t<T> operator* (const vec4_t<T>& lhs, float scalar);
        friend vec4_t<T> operator* (float scalar, const vec4_t<T>& rhs);
        friend std::ostream& operator<< (std::ostream& os, const vec4_t<T>& rhs);
        friend std::istream& operator>> (const std::istream& is, vec4_t<T>& rhs);
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

    /**
    * Compute cross-product. 
    */
    template <typename T>
    vec4_t<T> cross(const vec4_t<T>& a, const vec4_t<T>& b);
} // namespace mq