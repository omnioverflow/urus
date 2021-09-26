#pragma once

#include <iostream>

namespace mq
{
    /*
      FIXME:
        - usage of global functions might be a bad practice here
        - explicit vs implicit inlining?

      Temporary implementation notes:
        1. The definitions of a class template's member functions should appear in 
          the same header that contains the class template definition 
          (this is the most convenient portable way of using templates, 
          see discussion https://stackoverflow.com/questions/495021/)
        2. Related to (1.): https://stackoverflow.com/questions/16287178/
        3. functions that post-factum end up inlined must have definitions in each 
          translation unit (source + included headers).
        4. Prevent function inlining via #pragma auto_inline(off), __declspec(noinline)
           (https://docs.microsoft.com/en-us/cpp/build/reference/ob-inline-function-expansion?view=msvc-160)
    */

    // -------------------------------------------------------------------------
    // vec2
    // -------------------------------------------------------------------------
    template <typename T>
    struct vec2_t
    {
        union
        {
            struct {
                T x;
                T y;
            };

            T data[2];
        }; // anonymous union

         vec2_t();
         vec2_t(T xval, T yval);
         explicit vec2_t(const T* array);

        // ---------------------------------------------------------------------
        // Operators
        // ---------------------------------------------------------------------
        T& operator[] (int index);
        const T& operator[] (int index) const;
        vec2_t<T>& operator+= (const vec2_t<T>& rhs);
        vec2_t<T> operator+ (const vec2_t<T>& rhs) const;
        vec2_t<T>& operator-= (const vec2_t<T>& rhs);
        vec2_t<T> operator- (const vec2_t<T>& rhs) const;
        vec2_t<T>& operator*= (float scalar);
        vec2_t<T> operator* (float scalar) const;

        template <typename U>
        friend vec2_t<U> operator* (float scalar, const vec2_t<U>& rhs);

        template <typename U>
        friend std::ostream& operator<< (std::ostream& os, const vec2_t<U>& rhs);

        template <typename U>
        friend std::istream& operator>> (std::istream& is, vec2_t<U>& rhs);
    }; // struct base_vec2

    typedef vec2_t<float> vec2;
    typedef vec2_t<int> ivec2;

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

    template <typename T>
    vec2_t<T>::vec2_t() : x(T(0)), y(T(0)) {}

    template <typename T>
    vec2_t<T>::vec2_t(T xval, T yval) : x(xval), y(yval) {}

    template <typename T>
    vec2_t<T>::vec2_t(const T* array) : x(array[0]), y(array[1]) {}

    template <typename T>
    T& vec2_t<T>::operator[] (int index) {
        return data[index];
    }

    template <typename T>
    const T& vec2_t<T>::operator[] (int index) const {
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
        return os << rhs[0] << std::endl << rhs[1] << std::endl;
    }

    template <typename T>
    std::istream& operator>> (std::istream& is, vec2_t<T>& rhs) {
        return is >> rhs[0] >> rhs[1];
    }

} // namespace mqMath
