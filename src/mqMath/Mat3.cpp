#include "Mat.h"

namespace mq {

        mat3::mat3(float d)
        : m_{vec3(d, 0.f, 0.f), vec3(0.f, d, 0.f), vec3(0.f, 0.f, d)} {}

        mat3::mat3(const vec3& row0, const vec3& row1, const vec3& row2)
        : m_{row0, row1, row2} {}

        mat3::mat3(float m00, float m10, float m20,
            float m01, float m11, float m21,
            float m02, float m12, float m22)
            : m_{vec3(m00, m01, m02), vec3(m10, m11, m12), vec3(m20, m21, m22)}
            {}

        mat3::mat3(const mat3& other)
        : mat3(other[0], other[1], other[2]) {}

        vec3& mat3::operator[] (int index) {
            return m_[index];
        }

        const vec3& mat3::operator[] (int index) const { 
            return m_[index];
        }

        mat3& mat3::operator+= (const mat3& rhs) {
            m_[0] += rhs[0];
            m_[1] += rhs[1];
            m_[2] += rhs[2];
            
            return *this;
        }

        mat3 mat3::operator+ (const mat3& rhs) const {
            auto temp(*this);
            temp += rhs;
            return temp;
        }

        mat3& mat3::operator-= (const mat3& rhs) {            
            m_[0] -= rhs[0];
            m_[1] -= rhs[1];
            m_[2] -= rhs[2];
            
            return *this;
        }

        mat3 mat3::operator- (const mat3& rhs) const {
            auto temp(*this);
            temp -= rhs;
            return temp;
        }

        mat3& mat3::operator*= (const mat3& rhs) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        (*this)[i][j] += (*this)[i][k] * rhs[k][j];
                    }
                }
            }
            return *this;
        }

        mat3 mat3::operator* (const mat3& rhs) const {
            auto temp(*this);
            temp *= rhs;
            return temp;
        }

        mat3& mat3::operator*= (float s) {           
            m_[0] *= s;
            m_[1] *= s;
            m_[2] *= s;
            
            return *this;
        }

        mat3 mat3::operator* (float s) const {
            auto temp(*this);
            temp *= s;
            return temp;
        }        

        mat3 operator* (float s, const mat3& rhs) {
            return rhs * s;
        }        

        mat3& mat3::operator/= (float s) {
            #ifdef DEBUG
            if (std::fabs(s) < DivideByZeroTolerance) {
                std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
                    << "Division by zero" << std::endl;
                return *this;
            }
            #endif // DEBUG

            float r = float(1.0f) / s;
            return (*this) *= r;
        }    
        
        mat3 mat3::operator/ (float s) const {
            auto temp(*this);
            temp /= s;
            return temp;
        }

        // --------------------------------------------------------------------
        //  (modifying) Arithmetic Operators
        // --------------------------------------------------------------------                        

        vec3 mat3::operator* (const vec3& v) const {
            return vec3(m_[0][0] * v.x + m_[0][1] * v.y + m_[0][2] * v.z,
                m_[1][0] * v.x + m_[1][1] * v.y + m_[1][2] * v.z,
                m_[2][0] * v.x + m_[2][1] * v.y + m_[2][2] * v.z);
        }

        std::ostream& operator<< (std::ostream& os, const mat3& rhs) {
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

        mat3::operator const float* () const {
            return static_cast<const float*>(&m_[0].x);
        }

        mat3::operator float* () {
            return static_cast<float*>(&m_[0].x);
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
