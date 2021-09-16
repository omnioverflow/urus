#include "Mat.h"

#include <cassert>

#include "MqMath.h"

namespace mq {
        mat4::mat4(float d)
        : m_{vec4(d, 0.f, 0.f, 0.f), vec4(0.f, d, 0.f, 0.f),
            vec4(0.f, 0.f, d, 0.f), vec4(0.f, 0.f, 0.f, d)} {}

        mat4::mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d)
        : m_{a, b, c, d} {}

        mat4::mat4(float m00, float m10, float m20, float m30,
            float m01, float m11, float m21, float m31,
            float m02, float m12, float m22, float m32,
            float m03, float m13, float m23, float m33)
            : m_{vec4(m00, m01, m02, m03), vec4(m10, m11, m12, m13)
            , vec4(m20, m21, m22, m23), vec4(m30, m31, m32, m33)} {}

        mat4::mat4(const mat4& other)
        : m_{other[0], other[1], other[2], other[3]} {}

        vec4& mat4::operator[] (int i) { return m_[i]; }
        const vec4& mat4::operator[] (int i) const { return m_[i]; }

        mat4& mat4::operator+= (const mat4& rhs) {
            m_[0] += rhs[0];
            m_[1] += rhs[1];
            m_[2] += rhs[2];
            m_[3] += rhs[3];
            return *this;
        }

        mat4 mat4::operator+ (const mat4& rhs) const {
            auto temp(*this);
            temp += rhs;
            return temp;
        }

        mat4& mat4::operator-= (const mat4& rhs) {
            m_[0] -= rhs[0];
            m_[1] -= rhs[1];
            m_[2] -= rhs[2];
            m_[3] -= rhs[3];
            return *this;
        }

        mat4 mat4::operator- (const mat4& rhs) const {
            auto temp(rhs);
            temp -= rhs;
            return temp;
        }

        mat4& mat4::operator*= (const mat4& rhs) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        m_[i][j] += m_[i][k] * rhs[k][j];
                    }
                }
            }

            return *this;
        }

        mat4 mat4::operator* (const mat4& rhs) const {
            auto temp(*this);
            temp *= rhs;
            return temp;
        }

        mat4& mat4::operator*= (float s) {
            m_[0] *= s;
            m_[1] *= s;
            m_[2] *= s;
            m_[3] *= s;
            return *this;
        }

        mat4 mat4::operator* (float s) const {
            auto temp(*this);
            temp *= s;
            return temp;
        }

        mat4 operator* (float s, const mat4& m) {
            return m * s;
        }

        mat4 mat4::operator/ (float s) const {
            #ifdef DEBUG
            if (std::fabs(s) < DivideByZeroTolerance) {
                std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
                    << "Division by zero" << std::endl;
                return mat4();
            }
            #endif // DEBUG

            float r = float(1.0f) / s;
            return *this * r;
        }

        mat4& mat4::operator/= (float s) {
            #ifdef DEBUG
            if (std::fabs(s) < DivideByZeroTolerance) {
                std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
                    << "Division by zero" << std::endl;
                return *this;
            }
            #endif // DEBUG

            float r = float(1.0f) / s;
            return *this *= r;
        }

        //  Matrix / Vector operators
        vec4 mat4::operator* (const vec4& v) const {  // m * v
            return vec4(m_[0][0] * v.x + m_[0][1] * v.y + m_[0][2] * v.z + m_[0][3] * v.w,
                m_[1][0] * v.x + m_[1][1] * v.y + m_[1][2] * v.z + m_[1][3] * v.w,
                m_[2][0] * v.x + m_[2][1] * v.y + m_[2][2] * v.z + m_[2][3] * v.w,
                m_[3][0] * v.x + m_[3][1] * v.y + m_[3][2] * v.z + m_[3][3] * v.w
            );
        }

        std::ostream& operator<< (std::ostream& os, const mat4& rhs) {
            return os << std::endl << rhs[0] << std::endl << rhs[1] << std::endl << rhs[2] <<
                   std::endl << rhs[3] << std::endl;
        }

        std::istream& operator>> (std::istream& is, mat4& rhs) {
            return is >> rhs.m_[0] >> rhs.m_[1] >> rhs.m_[2] >> rhs.m_[3];
        }

        //  Conversion Operators
        mat4::operator const float* () const {
            return static_cast<const float*>(&m_[0].x);
        }

        mat4::operator float* () {
            return static_cast<float*>(&m_[0].x);
        }

    // ------------------------------------------------------------------------
    //  Non-class mat4 Methods
    // ------------------------------------------------------------------------
    mat4 matrixCompMult(const mat4& A, const mat4& B) {
        return mat4(
            A[0][0] * B[0][0], A[0][1] * B[0][1], A[0][2] * B[0][2], A[0][3] * B[0][3],
            A[1][0] * B[1][0], A[1][1] * B[1][1], A[1][2] * B[1][2], A[1][3] * B[1][3],
            A[2][0] * B[2][0], A[2][1] * B[2][1], A[2][2] * B[2][2], A[2][3] * B[2][3],
            A[3][0] * B[3][0], A[3][1] * B[3][1], A[3][2] * B[3][2], A[3][3] * B[3][3]
        );
    }

    mat4 transpose(const mat4& A) {
        return mat4(A[0][0], A[1][0], A[2][0], A[3][0],
            A[0][1], A[1][1], A[2][1], A[3][1],
            A[0][2], A[1][2], A[2][2], A[3][2],
            A[0][3], A[1][3], A[2][3], A[3][3]);
    }    

    //  Rotation matrix generators
    mat4 RotateX(float theta) {
        float angle = DegreesToRadians * theta;

        mat4 c;
        c[2][2] = c[1][1] = cos(angle);
        c[2][1] = sin(angle);
        c[1][2] = -c[2][1];
        return c;
    }

    mat4 RotateY(float theta) {
        float angle = DegreesToRadians * theta;

        mat4 c;
        c[2][2] = c[0][0] = cos(angle);
        c[0][2] = sin(angle);
        c[2][0] = -c[0][2];
        return c;
    }

    mat4 RotateZ(float theta) {
        float angle = DegreesToRadians * theta;

        mat4 c;
        c[0][0] = c[1][1] = cos(angle);
        c[1][0] = sin(angle);
        c[0][1] = -c[1][0];
        return c;
    }

    //  Translation matrix generators    
    mat4 Translate(float x, float y, float z) {
        mat4 c;
        c[0][3] = x;
        c[1][3] = y;
        c[2][3] = z;
        return c;
    }

    mat4 Translate(const vec3& v) {
        return Translate(v.x, v.y, v.z);
    }

    mat4 Translate(const vec4& v) {
        return Translate(v.x, v.y, v.z);
    }

    //  Scale matrix generators
    mat4 Scale(float x, float y, float z) {
        mat4 c;
        c[0][0] = x;
        c[1][1] = y;
        c[2][2] = z;
        return c;
    }

    mat4 Scale(const vec3& v) {
        return Scale(v.x, v.y, v.z);
    }

    //  Projection transformation matrix geneartors
    mat4 Ortho(float left, float right, float bottom, float top,
            float zNear, float zFar) {
        mat4 temp;
        temp[0][0] = 2.f / (right - left);
        temp[1][1] = 2.f / (top - bottom);
        temp[2][2] = 2.f / (zNear - zFar);
        temp[3][3] = 1.f;
        temp[0][3] = -(right + left) / (right - left);
        temp[1][3] = -(top + bottom) / (top - bottom);
        temp[2][3] = -(zFar + zNear) / (zFar - zNear);
        return temp;
    }

    mat4 Ortho2D(float left, float right, float bottom, float top) {
        return Ortho(left, right, bottom, top, -1.f, 1.f);
    }

    mat4 Frustum(float left, float right, float bottom, float top,
            float zNear, float zFar) {
        mat4 temp;
        temp[0][0] = 2.f * zNear / (right - left);
        temp[0][2] = (right + left) / (right - left);
        temp[1][1] = 2.f * zNear / (top - bottom);
        temp[1][2] = (top + bottom) / (top - bottom);
        temp[2][2] = -(zFar + zNear) / (zFar - zNear);
        temp[2][3] = -2.f * zFar * zNear / (zFar - zNear);
        temp[3][2] = -1.f;
        return temp;
    }

    mat4 Perspective(float fovy, float aspect, float zNear, float zFar) {
        float top = tan(fovy * DegreesToRadians / 2.f) * zNear;
        float right = top * aspect;
        
        assert(!isZero(right));
        assert(!isZero(top));

        mat4 temp;
        temp[0][0] = zNear / right;
        temp[1][1] = zNear / top;
        temp[2][2] = -(zFar + zNear) / (zFar - zNear);
        temp[2][3] = -2.f * zFar * zNear / (zFar - zNear);
        temp[3][2] = -1.f;
        return c;
    }

    //  Viewing transformation matrix generation
    mat4 LookAt(const vec4& eye, const vec4& at, const vec4& up) {
        vec4 n = normalize(eye - at);
        vec4 u = normalize(cross(up, n));
        vec4 v = normalize(cross(n, u));
        vec4 t = vec4(0.f, 0.f, 0.f, 1.f);
        mat4 c = mat4(u, v, n, t);
        return c * Translate(-eye);
    }
    
} // namespace mq
