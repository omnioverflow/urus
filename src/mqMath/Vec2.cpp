#include "Vec.h"

namespace mq {
    template <typename T>
    vec2_t<T>::vec2_t() : x(T(0)), y(T(0)) {}

    template <typename T>
    vec2_t<T>::vec2_t<T>(T xval, T yval) : x(xval), y(yval) {}

    template <typename T>
    vec2_t<T>::vec2_t<T>(const T* array) : x(array[0]), y(array[1]) {}

    template <typename T>
    T& vec2_t<T>::operator[] (int index)
    {
        return data[index];
    }

    template <typename T>
    const T& vec2_t<T>::operator[] (int index) const
    {
        return data[index];
    }

    template <typename T>
    vec2_t<T>& vec2_t<T>::operator+= (const vec2_t<T>& rhs) {
        (*this)[0] += rhs[0];
        (*this)[1] += rhs[1];
        return *this;
    }
    
    template <typename T>
    vec2_t<T> vec2_t<T>::operator+ (const vec2_t<T>& rhs) const {
        auto temp(*this);
        temp += rhs;
        return temp;
    }

    template <typename T>
    vec2_t<T>& vec2_t<T>::operator-= (const vec2_t<T>& rhs) {
        (*this)[0] -= rhs[0];
        (*this)[1] -= rhs[1];
        return *this;
    }

    template <typename T>
    vec2_t<T> vec2_t<T>::operator- (const vec2_t<T>& rhs) const {
        auto temp(*this);
        temp -= rhs;
        return temp;
    }

    template <typename T>
    vec2_t<T>& vec2_t<T>::operator*= (float scalar) {
        (*this)[0] *= scalar;
        (*this)[1] *= scalar;
        return *this;
    }

    template <typename T>
    vec2_t<T> vec2_t<T>::operator* (float scalar) const {
        auto temp(*this);
        temp *= scalar;
        return temp;
    }

    // ------------------------------------------------------------------------
    // Non-member operators
    // ------------------------------------------------------------------------
    template <typename T>
    vec2_t<T> operator* (float s, const vec2_t<T>& rhs) {
        return rhs * s;
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& os, const vec2_t<T>& rhs) {
        return os << vec2[0] << std::endl << vec2[1] << std::endl;
    }

    template <typename T>
    std::istream& operator>> (const std::istream& is, vec2_t<T>& rhs) {
        return is >> vec[0] >> vec[1];
    }
} // namespace mqMath