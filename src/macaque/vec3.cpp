#include "vec3.h"

#include <cmath>

namespace macaque
{
    float& vec3::operator[] (int index)
    {
        return data[index];
    }

    vec3 operator+ (const vec3& lhs, const vec3& rhs) 
    { 
        return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); 
    }

    vec3 operator- (const vec3& lhs, const vec3& rhs) 
    { 
        return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); 
    }

    vec3 operator* (const vec3& v, float f)
    {
        return vec3(v.x * f, v.y * f, v.z * f);
    }

    vec3 operator* (const vec3& lhs, const vec3& rhs) 
    {
        return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
    }

    bool operator== (const vec3& lhs, const vec3& rhs)
    {
        return lengthSq(lhs - rhs) < vec3::VEC3_EPSILON;
    }

    bool operator!= (const vec3& lhs, const vec3& rhs)
    {
        return !(lhs == rhs);
    }

    vec3 cross(const vec3& lhs, const vec3& rhs)
    {
        return vec3(lhs.y * rhs.z - lhs.z * rhs.y,
                    lhs.z * rhs.x - lhs.x * rhs.z,
                    lhs.x * rhs.y - lhs.y * rhs.x);
    }

    float length(const vec3& v)
    {
        const float lenSq = lengthSq(v);
        if (lenSq < vec3::VEC3_EPSILON)
            return 0.f;

        return sqrtf(lenSq);
    }

    void normalize(vec3& v)
    {
        const float lenSq = lengthSq(v);
        if (lenSq < vec3::VEC3_EPSILON)
            return;

        const float invLen = 1.f / sqrtf(lenSq);
        v.x *= invLen;
        v.y *= invLen;
        v.z *= invLen;
    }

    vec3 normalized(const vec3& v)
    {
        const float lenSq = lengthSq(v);
        if (lenSq < vec3::VEC3_EPSILON)
            return v;

        const float invLen = 1.f / sqrtf(lenSq);
        return vec3(v.x * invLen, v.y * invLen, v.z * invLen);
    }

    float angle(const vec3& a, const vec3& b)
    {
        const float lengthA = length(a);
        const float lengthB = length(b);
        if (lengthA < vec3::VEC3_EPSILON || lengthB < vec3::VEC3_EPSILON)
            return 0.f;

        return acosf(dot(a, b) / (lengthA + lengthB));
    }

    vec3 projection(const vec3& a, const vec3& b)
    {
        const float lengthB = length(b);
        if (lengthB < vec3::VEC3_EPSILON)
            return vec3();

        const auto scale = dot(a, b) / lengthB;
        return b * scale;
    }

    vec3 rejection(const vec3& a, const vec3& b)
    {
        vec3 projA = projection(a, b);
        return a - projA;
    }

    vec3 reflect(const vec3& a, const vec3& n)
    {
        const float lengthB = length(n);
        if (lengthB < vec3::VEC3_EPSILON)
            return vec3();

        const float scale = dot(a, n) / lengthB;
        vec3 proj2 = n * (scale * 2);

        return a - proj2;
    }

    vec3 lerp(const vec3& v0, const vec3& v1, float t)
    {
        return vec3(
                    v0.x + (v1.x - v0.x) * t,
                    v0.y + (v1.y - v0.y) * t,
                    v0.z + (v1.z - v0.z) * t
                   );
    }

    vec3 slerp(const vec3& v0, const vec3& v1, float t)
    {
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

    vec3 nlerp(const vec3& v0, const vec3& v1, float t)
    {
        return normalized(lerp(v0, v1, t));
    }

} // namespace macaque
