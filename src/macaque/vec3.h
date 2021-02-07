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

        inline vec3() : x(0.f), y(0.f), z(0.f) {}
        inline vec3(float xvalue, float yvalue, float zvalue) : x(xvalue), y(yvalue), z(zvalue) {}
        inline vec3(const float* array) : x(array[0]), y(array[1]), z(array[2]) {}
    }; // struct vec3
} // namespace macaque
