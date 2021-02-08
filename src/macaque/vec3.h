#pragma once

namespace macaque
{
    struct vec3
    {
        union
        {
            struct
            {
                float x;
                float y;
                float z;
            };

            float data[3];
        };

        vec3 operator+ (const vec3& lrs, const vec3& rhs);
        vec3 operator- (const vec3& lrs, const vec3& rhs);
        vec3 operator* (const vec3& v, float f);
        vec3 operator* (const vec3& lrs, const vec3& rhs);
        bool operator== (const vec3& lhs, const vec3& rhs);
        bool operator!= (const vec3& lhs, const vec3& rhs);

        inline vec3() : x(0.f), y(0.f), z(0.f) {}
        inline vec3(float xvalue, float yvalue, float zvalue) : x(xvalue), y(yvalue), z(zvalue) {}
        inline vec3(const float* array) : x(array[0]), y(array[1]), z(array[2]) {}

        constexpr float VEC3_EPSILON = 1.0e-7;
    }; // struct vec3

    // FIXME: usage of global functions might be a bad practice here (including inlining)
    vec3 cross(const vec3& lhs, const vec3& rhs);
    inline float dot(const vec3& lhs, const vec3& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
    inline float lengthSq(const vec3& v) { return dot(v, v); }
    float length(const vec3& v);

    void normalize(vec3& v);
    vec3 normalized(const vec3& v);

    float angle(const vec3& a, const vec3& b);

    /**
     * Vector projection of a on b.
     */
    vec3 project(const vec3& a, const vec3& b);

    /**
     * Vector rejection.
     * The vector rejection of a on b is a vector a2 which is either null or orthogonal to b.
     * (see https://en.wikipedia.org/wiki/Vector_projection#Vector_rejection_3)
     */
    vec3 rejection(const vec3& a, const vec3& b);

    /**
     * Bounce reflection of a with respect to b (as if b was a normal to the 
     * bounce sourface)
     */
    vec3 reflect(const vec3& a, const vec3& b);

    /**
     * Linear interpolation
     */    
    vec3 lerp(const vec3& u, const vec3& w, float s); 
    /**
     * Spherical linear interpolation
     */
    vec3 slerp(const vec3& u, const vec3& w, float s);
    /**
     * Normalized linear interpolation
     */
    vec3 nlerp(const vec3& u, const vec3& w, float s);

} // namespace macaque
