#include "Vec.h"

namespace mq {

        mat3(const GLfloat d = GLfloat(1.0f)) {
            m_[0].x = d;
            m_[1].y = d;
            m_[2].z = d;
        }

        mat3(const vec3& a, const vec3& b, const vec3& c) {
            m_[0] = a;
            m_[1] = b;
            m_[2] = c;
        }

        mat3(GLfloat m00, GLfloat m10, GLfloat m20,
            GLfloat m01, GLfloat m11, GLfloat m21,
            GLfloat m02, GLfloat m12, GLfloat m22) {
            m_[0] = vec3(m00, m01, m02);
            m_[1] = vec3(m10, m11, m12);
            m_[2] = vec3(m20, m21, m22);
        }

        mat3(const mat3& m) {
            if (*this != m) {
                m_[0] = m.m_[0];
                m_[1] = m.m_[1];
                m_[2] = m.m_[2];
            }
        }

        // --------------------------------------------------------------------
        //  Indexing Operator
        // --------------------------------------------------------------------

        vec3& operator[] (int i) { return m_[i]; }
        const vec3& operator[] (int i) const { return m_[i]; }

        // --------------------------------------------------------------------
        //  (non-modifying) Arithmatic Operators
        // --------------------------------------------------------------------

        mat3& operator+= (const mat3& m) {
            m_[0] += m[0];
            m_[1] += m[1];
            m_[2] += m[2];
            return *this;
        }

        mat3 operator+ (const mat3& rhs) const {
            return mat3(m_[0] + m[0], m_[1] + m[1], m_[2] + m[2]);
        }

        mat3& operator-= (const mat3& m) {
            m_[0] -= m[0];
            m_[1] -= m[1];
            m_[2] -= m[2];
            return *this;
        }

        mat3 operator- (const mat3& m) const {
            return mat3(m_[0] - m[0], m_[1] - m[1], m_[2] - m[2]);
        }

        mat3& operator*= (const mat3& m) {
            mat3  a(0.0f);

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        a[i][j] += m_[i][k] * m[k][j];
                    }
                }
            }

            return *this = a;
        }

        mat3& operator*= (const GLfloat s) {
            m_[0] *= s;
            m_[1] *= s;
            m_[2] *= s;
            return *this;
        }

        mat3 operator* (const GLfloat s) const {
            return mat3(s * m_[0], s * m_[1], s * m_[2]);
        }        

        friend mat3 operator* (const GLfloat s, const mat3& m) {
            return m * s;
        }

        mat3 operator* (const mat3& m) const {
            mat3  a(0.0f);

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        a[i][j] += m_[i][k] * m[k][j];
                    }
                }
            }

            return a;
        }

        mat3& operator/= (const GLfloat s) {
            #ifdef DEBUG
            if (std::fabs(s) < DivideByZeroTolerance) {
                std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
                    << "Division by zero" << std::endl;
                return *this;
            }
            #endif // DEBUG

            GLfloat r = GLfloat(1.0f) / s;
            return *this *= r;
        }    
        
        mat3 operator/ (const GLfloat s) const {
            #ifdef DEBUG
            if (std::fabs(s) < DivideByZeroTolerance) {
                std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
                    << "Division by zero" << std::endl;
                return mat3();
            }
            #endif // DEBUG

            GLfloat r = GLfloat(1.0f) / s;
            return *this * r;
        }

        // --------------------------------------------------------------------
        //  (modifying) Arithmetic Operators
        // --------------------------------------------------------------------                        

        vec3 operator* (const vec3& v) const {
            return vec3(m_[0][0] * v.x + m_[0][1] * v.y + m_[0][2] * v.z,
                m_[1][0] * v.x + m_[1][1] * v.y + m_[1][2] * v.z,
                m_[2][0] * v.x + m_[2][1] * v.y + m_[2][2] * v.z);
        }

        friend std::ostream& operator<< (std::ostream& os, const mat3& rhs) {
            return os << std::endl
                << rhs[0] << std::endl
                << rhs[1] << std::endl
                << rhs[2] << std::endl;
        }

        std::istream& operator>> (std::istream& is, mat3& rhs) {
            return is >> rhs.m_[0] >> rhs.m_[1] >> rhs.m_[2];
        }

        // ---------------------------------------------------------------------
        // Conversion Operators
        // ---------------------------------------------------------------------

        operator const GLfloat* () const {
            return static_cast<const GLfloat*>(&m_[0].x);
        }

        operator GLfloat* () {
            return static_cast<GLfloat*>(&m_[0].x);
        }

        mat3 matrixCompMult(const mat3& A, const mat3& B) {
            return mat3(A[0][0] * B[0][0], A[0][1] * B[0][1], A[0][2] * B[0][2],
                A[1][0] * B[1][0], A[1][1] * B[1][1], A[1][2] * B[1][2],
                A[2][0] * B[2][0], A[2][1] * B[2][1], A[2][2] * B[2][2]);
        }

        mat3 transpose(const mat3& A) {
            return mat3(A[0][0], A[1][0], A[2][0], A[0][1], A[1][1], A[2][1],
                A[0][2], A[1][2], A[2][2]);
        }
} // namespace mq