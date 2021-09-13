
/*
#pragma once

#include <cmath>
*/

/*
    Note on implementation.
    column-major matrix PROS:
        - conforms with OpenGL column-major notation
        - first 3 columns correspond to the basis vectors, while the rightmost column
          corresponds to the translation
    column-major matrix CONS:
        - cache unfriendly (increases cache misses)
        - might be less intuitive to use
    row-wise matrix PROS:
        - cache friendly
        - more intuitive
    row-wise matrix CONS:
        - does not comply with the OpenGL convetion
*/

/*
namespace mq
{
    struct row_major_mat4
    {
        union
        {
            float data[16];

            struct
            {
                vec4 row0;
                vec4 row1;
                vec4 row2;
                vec4 row3;
            };

            struct
            {
                // row0 elements
                float xx;
                float xy;
                float xz;
                float xw;
                // row1 elemnts
                float yx;
                float yy;
                float yz;
                float yw;
                // row2 elements
                float zx;
                float zy;
                float zz;
                float zw;
                // row3 elements
                float wx;
                float wy;
                float wz;
                float ww;
            };
        } // union

        // default ctor creates an identity matrix
        inline row_major_mat4() 
        : vec4{1.f, 0.f, 0.f, 0.f}
        , vec4{0.f, 1.f, 0.f, 0.f}
        , vec4{0.f, 0.f, 1.f, 0.f}
        , vec4{0.f, 0.f, 0.f, 0.f}
        {}

        inline row_major_mat4(float *dataArray)
        : xx(dataArray[0])
        , xy(dataArray[1])
        , xz(dataArray[2])
        , xw(dataArray[3])
        , yx(dataArray[4])
        , yy(dataArray[5])
        , yz(dataArray[6])
        , yw(dataArray[7])
        , zx(dataArray[8])
        , zy(dataArray[9])
        , zz(dataArray[10])
        , zw(dataArray[11])
        , wx(dataArray[12])
        , wy(dataArray[13])
        , wz(dataArray[14])
        , ww(dataArray[15])
        {}

        static constexpr MAT4_EPSILON = 0.1fe-6;

        friend bool operator== (const mat4& lhs, const mat4& rhs)
        {
            for (int i = 0; i < 16; ++i)
            {
                if (fabs(lhs.data[i] - rhs.data[i]) > )
                    return false;
            }
            return true;
        }

        friend bool operator!= (const mat4& lhs, const mat4& rhs)
        {
            return !(a == b);
        }

        friend mat4 operator+ (const mat4& lhs, const mat4& rhs)
        {
            return mat4
                   (
                        lhs.data[0] + rhs.data[0],
                        lhs.data[1] + rhs.data[1],
                        lhs.data[2] + rhs.data[2],
                        lhs.data[3] + rhs.data[3],
                        lhs.data[4] + rhs.data[4],
                        lhs.data[5] + rhs.data[5],
                        lhs.data[6] + rhs.data[6],
                        lhs.data[7] + rhs.data[7],
                        lhs.data[8] + rhs.data[8],
                        lhs.data[9] + rhs.data[9],
                        lhs.data[10] + rhs.data[10],
                        lhs.data[11] + rhs.data[11],
                        lhs.data[12] + rhs.data[12],
                        lhs.data[13] + rhs.data[13],
                        lhs.data[14] + rhs.data[14],
                        lhs.data[15] + rhs.data[15],
                   );
        }

        friend mat4 operator* (const mat4& m, float s)
        {
            return mat4
                   (
                        m.data[0] * s, m.data[1] * s, m.data[2] * s, m.data[3] * s,
                        m.data[4] * s, m.data[5] * s, m.data[6] * s, m.data[7] * s,
                        m.data[8] * s, m.data[9] * s, m.data[10] * s, m.data[11] * s,
                        m.data[12] * s, m.data[13] * s, m.data[14] * s, m.data[15] * s
                   );
        }

        friend mat4 operator* (const mat4& lhs, const mat4& rhs)
        {
            mat4 res;
            // FIXME: add implementation
            return res;
        }
    }; // struct mat4

    typedef row_major_mat4 mat4;
} // namespace mq
*/