#include "Mat.h"

namespace mq {
    // ------------------------------------------------------------------------
    // mat2
    // ------------------------------------------------------------------------
    
    // Create a diagional matrix
    mat2::mat2(float d)
    : mat2(d, 0.f, 0.0f, d) {}
    mat2::mat2(const vec2& a, const vec2& b)
    : m_{a, b} {}
    mat2::mat2(float m00, float m10, float m01, float m11)
    : mat2(vec2(m00, m01), vec2(m10, m11)) {}
    mat2::mat2(const mat2& other)
    : m_{other.m_[0], other.m_[1]} {}

    vec2& mat2::operator[] (int index) { 
        return m_[index];
    }

    const vec2& mat2::operator[] (int index) const { 
        return m_[index];
    }

    mat2& mat2::operator+= (const mat2& rhs) {
        m_[0] += rhs[0];
        m_[1] += rhs[1];
        return *this;
    }

    mat2 mat2::operator+ (const mat2& rhs) const {
        auto temp(*this);
        temp += rhs;
        return temp;
    }

    mat2& mat2::operator-= (const mat2& rhs) {
        m_[0] -= rhs[0];
        m_[1] -= rhs[1];
        return *this;
    }  

    mat2 mat2::operator- (const mat2& rhs) const {
        auto temp(*this);
        temp += rhs;
        return temp;
    }

    mat2& mat2::operator*= (const mat2& rhs) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    (*this)[i][j] += m_[i][k] * rhs[k][j];
                }
            }
        }

        return *this;
    }

    mat2 mat2::operator* (const mat2& rhs) const {
        auto temp(*this);
        temp *= rhs;
        return temp;
    }

    mat2& mat2::operator*= (float s) {
        m_[0] *= s;
        m_[1] *= s;
        return *this;
    }

    mat2 mat2::operator* (float s) const {
        auto temp(*this);
        temp *= s;
        return temp;
    }

    mat2 operator* (float s, const mat2& m) {
        return m * s;
    }

    vec2 mat2::operator* (const vec2& rhs) const {
        return vec2(m_[0][0] * rhs.x + m_[0][1] * rhs.y,
            m_[1][0] * rhs.x + m_[1][1] * rhs.y);
    }

    mat2& mat2::operator/= (float s) {
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

    mat2 mat2::operator/ (float s) const {
        auto temp(*this);
        temp /= s;
        return temp;        
    }

    std::ostream& operator<< (std::ostream& os, const mat2& rhs) {        
        return os << std::endl << rhs[0] << std::endl << rhs[1] << std::endl;
    }

    std::istream& operator>> (std::istream& is, mat2& rhs) {
        return is >> rhs.m_[0] >> rhs.m_[1];
    }

    // ------------------------------------------------------------------------
    //  mat2 conversion cperators
    // ------------------------------------------------------------------------

    mat2::operator const float* () const {
        return static_cast<const float*>(&m_[0].x);
    }

    mat2::operator float* () {
        return static_cast<float*>(&m_[0].x);
    }
} // namespace mq
