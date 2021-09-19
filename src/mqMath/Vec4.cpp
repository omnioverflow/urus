#include "Vec4.h"

namespace mq {
    // -------------------------------------------------------------------------
    // Member operators
    // -------------------------------------------------------------------------
    template <typename T>
    inline T& vec4_t<T>::operator[] (int index) {
        return data[index];
    }

    template <typename T>
    inline const T& vec4_t<T>::operator[] (int index) const {
        return data[index];
    }

    template <typename T>
    vec4_t<T>& vec4_t<T>::operator+= (const vec4_t<T>& rhs) {
        (*this)[0] += rhs[0];
        (*this)[1] += rhs[1];
        (*this)[2] += rhs[2];
        (*this)[3] += rhs[3];
        return *this;
    }

    template <typename T>
    vec4_t<T> vec4_t<T>::operator+ (const vec4_t<T>& rhs) const {
        auto temp(*this);
        temp += rhs;
        return temp;
    }

    template <typename T>
    vec4_t<T>& vec4_t<T>::operator- () {
        (*this)[0] = -(*this)[0];
        (*this)[1] = -(*this)[1];
        (*this)[2] = -(*this)[2];
        (*this)[3] = -(*this)[3];
        return *this;
    }

    template <typename T>
    vec4_t<T>& vec4_t<T>::operator-= (const vec4_t<T>& rhs) {
        (*this) += -(*this);
        return *this;
    }

    template <typename T>
    vec4_t<T> vec4_t<T>::operator- (const vec4_t<T>& rhs) const {
        auto temp(*this);
        temp -= rhs;
        return temp;
    }

    template <typename T>
    vec4_t<T>& vec4_t<T>::operator*= (float scalar) {
        (*this)[0] *= scalar;
        (*this)[1] *= scalar;
        (*this)[2] *= scalar;
        (*this)[3] *= scalar;
        return *this;
    }

    // -------------------------------------------------------------------------
    // Non-member operators
    // -------------------------------------------------------------------------
    template <typename T>
    vec4_t<T> operator* (const vec4_t<T>& lhs, float scalar) {
        auto temp(lhs);
        temp *= scalar;
        return temp;
    }

    template <typename T>
    vec4_t<T> operator* (float scalar, const vec4_t<T>& rhs) {
        return rhs * scalar;
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& os, const vec4_t<T>& rhs) {
        return os << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w;
    }

    template <typename T>
    std::istream& operator>> (const std::istream& is, vec4_t<T>& rhs) {
        return is >> rhs[0] >> rhs[1] >> rhs[2] >> rhs[3];
    }

    template <typename T>
    void normalize(vec4_t<T>& v) {
        const auto lenSq = lengthSq(v);
        if (!isZero(lenSq)) {
            const auto inverseLength = 1.f / sqrtf(lenSq);
            v.x *= inverseLength;
            v.y *= inverseLength;
            v.z *= inverseLength;
            v.w *= inverseLength;
        }
    }

    template <typename T>
    vec4_t<T> normalized(const vec4_t<T>& v) {
        auto temp(v);
        return normalize(temp);
    }

} // namespace mq