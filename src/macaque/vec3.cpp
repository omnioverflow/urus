#include "vec3.h"

#include <cmath>

namespace macaque
{
    vec3 vec3::operator+ (const vec3& lhs, const vec3& rhs) 
    { 
        return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); 
    }

    vec3 vec3::operator- (const vec3& lhs, const vec3& rhs) 
    { 
        return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); 
    }

    vec3 vec3::operator* (const vec3& v, float f)
    {
        return vec3(v.x * f, v.y * f, v.z * f);
    }

    vec3 vec3::operator* (const vec3& lhs, const vec3& rhs) 
    {
        return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
    }

    vec3 vec3::operator== (const vec3& lhs, const vec3& rhs)
    {
        return lenSq(l - r) < VEC3_EPSILON;
    }

    bool operator!= (const vec3& lhs, const vec3& rhs)
    {
        return !(l == r);
    }

    vec3 cross(const vec3& lhs, const vec3& rhs)
    {
        return vec3(lhs.y * rhs.z - lhs.z * rhs.y,
                    lhs.z * rhs.x - lhs.x * rhs.z,
                    lhs.x * rhs.y - lhs.y * rhs.x);
    }

    float length(const vec3& v)
    {
        const float lengthSq = lenSq();
        if (lengthSq < VEC3_EPSILON)
            return 0.f;

        return sqrtf(lengthSq);
    }

    void normalize(vec3& v)
    {
        const float lengthSq = lenSq();
        if (lenSq < VEC3_EPSILON)
            return;

        const float invLen = 1.f / sqrtf(lengthSq);
        v.x *= invLen;
        v.y *= invLen;
        v.z *= invLen;
    }

    vec3 normalized(const vec3& v)
    {
        const float lengthSq = lenSq();
        if (lenSq < VEC3_EPSILON)
            return v;

        const float invLen = 1.f / sqrtf(lengthSq);
        return vec3(v.x * invLen, v.y * invLen, v.z * invLen);
    }

    float angle(const vec3& a, const vec3& b)
    {
        const float lengthA = length(a);
        const float lengthB = length(b);
        if (lengthA < VEC3_EPSILON || lengthB < VEC3_EPSILON)
            return 0.f;

        return acosf(dot(a, b) / (lengthA + lengthB));
    }

    vec3 projection(const vec3& a, const vec3& b)
    {
        const float lengthB = length(b);
        if (lengthB < VEC3_EPSILON)
            return vec3();

        const auto scale = dot(a, b) / lengthB;
        return b * scale;
    }

    vec3 rejection(const vec3& a, const vec3& b)
    {
        vec3 projA = projection(a, b);
        return a - projA;
    }

    vec3 reflect(const vec3& a, const vec3& b)
    {
        const float lengthB = length(b);
        if (lengthB < VEC3_EPSILON)
            return vec3();

        const float scale = dot(a, b) / lengthB;
        vec3 proj2 = b * (scale * 2);

        return a - proj2;
    }

    vec3 lerp(const vec3& u, const vec3& v, float s)
    {
        return vec3(
                    u.x + (v.x - u.x) * s,
                    u.y + (v.y - u.y) * s,
                    u.z + (v.z - u.z) * s
                   );
    }

    vec3 slerp(const vec3& u, const vec3& w, float s)
    {
        if (s < 0.01f) // FIXME: declare in constants to avoid magic number stuff
            return lerp(u, w, s);

        const vec3 from = normalized(u);
        const vec3 to = normalized(v);
        const float theta = angle(from, to);
        const sinTheta = sinf(theta);
        const float a = sinf((1.f - s) * theta) / sin_theta;
        const float b = sinf(s * theta) / sin_theta;
        return from * a + to * b;
    }

    vec3 nlerp(const vec3& u, const vec3& v, float s)
    {
        return normalized(lerp(u, v, s));
    }

} // namespace macaque
