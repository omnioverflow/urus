#pragma once

#include <iostream>

#include "Vec.h"

namespace mq
{
    /**
    * mat2 - 2D square matrix
    */    
    class mat2 {
    public:

        explicit mat2(float d = float(1.0f));
        mat2(const vec2& a, const vec2& b);
        mat2(float m00, float m10, float m01, float m11);
        mat2(const mat2& m);

        vec2& operator[] (int index);
        const vec2& operator[] (int index) const;

        mat2& operator+= (const mat2& rhs);
        mat2 operator+ (const mat2& rhs) const;
        mat2& operator-= (const mat2& rhs);
        mat2 operator- (const mat2& rhs) const;

        mat2& operator*= (const mat2& rhs);
        mat2 operator* (const mat2& rhs) const;
        mat2& operator*= (float s);
        mat2 operator* (float s) const;
        friend mat2 operator* (float s, const mat2& rhs);
        vec2 operator* (const vec2& rhs) const;

        mat2& operator/= (float s);
        mat2 operator/ (float s) const;
     
        friend std::ostream& operator<< (std::ostream& os, const mat2& rhs);
        friend std::istream& operator>> (std::istream& is, mat2& rhs);

        // Cconversion operators
        operator const float* () const;
        operator float* ();

        private:
            vec2 m_[2];
    }; // class mat2

    /**
    * mat3 - 3D square matrix 
    */
    class mat3 {
    public:

        explicit mat3(float d = float(1.0f));
        mat3(const vec3& a, const vec3& b, const vec3& c);
        mat3(float m00, float m10, float m20,
            float m01, float m11, float m21,
            float m02, float m12, float m22);
        mat3(const mat3& other);

        vec3& operator[] (int index);
        const vec3& operator[] (int index) const;

        mat3& operator+= (const mat3& rhs);
        mat3 operator+ (const mat3& rhs) const;
        mat3& operator-= (const mat3& rhs);
        mat3 operator- (const mat3& rhs) const;
        mat3& operator*= (const mat3& rhs);
        mat3 operator* (const mat3& rhs) const;
        mat3& operator*= (float s);
        mat3 operator* (float s) const;
        friend mat3 operator* (float s, const mat3& rhs);
        mat3& operator/= (float s);
        mat3 operator/ (float s) const;

        vec3 operator* (const vec3& v) const;        

        friend std::ostream& operator<< (std::ostream& os, const mat3& rhs);
        friend std::istream& operator>> (std::istream& is, mat3& rhs);

        // Conversion operators
        operator const float* () const;
        operator float* ();

        // --------------------------------------------------------------------
        private:
            vec3 m_[3];
    }; // class mat3

    // ------------------------------------------------------------------------
    // Non-class mat3 Methods
    // ------------------------------------------------------------------------

    mat3 matrixCompMult(const mat3& A, const mat3& B);
    mat3 transpose(const mat3& A);

    /**
     * mat4.h - 4D square matrix
     */
    class mat4 {
    public:
        
        mat4(float d = float(1.0f));
        mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d);
        mat4(float m00, float m10, float m20, float m30,
            float m01, float m11, float m21, float m31,
            float m02, float m12, float m22, float m32,
            float m03, float m13, float m23, float m33);
        mat4(const mat4& other);

        vec4& operator[] (int index);
        const vec4& operator[] (int index) const;        

        mat4& operator+= (const mat4& rhs);
        mat4 operator+ (const mat4& rhs) const;
        mat4& operator-= (const mat4& rhs);
        mat4 operator- (const mat4& rhs) const;
        mat4& operator*= (const mat4& rhs);
        mat4 operator* (const mat4& rhs) const;
        mat4& operator*= (float s);
        mat4 operator* (float s) const;
        friend mat4 operator* (float s, const mat4& rhs);
        mat4& operator/= (float s);
        mat4 operator/ (float s) const;

        vec4 operator* (const vec4& v) const;

        friend std::ostream& operator<< (std::ostream& os, const mat4& rhs);
        friend std::istream& operator>> (std::istream& is, mat4& rhs);

        // Conversion operators
        operator const float* () const;
        operator float* ();

    public:

        static mat4 translate(float x, float y, float z);
        static mat4 translate(const vec3& v);
        static mat4 translate(const vec4& v);
        static mat4 rotateX(float theta);
        static mat4 rotateY(float theta);
        static mat4 rotateZ(float theta);
        static mat4 rotateXDegrees(float theta);
        static mat4 rotateYDegrees(float theta);
        static mat4 rotateZDegrees(float theta);
        static mat4 scale(float x, float y, float z);
        static mat4 scale(const vec3& v);
        //-------------------------------------------------------------------------
        //  Projection transformation matrix geneartors
        //
        //    Note: Microsoft Windows (r) defines the keyword "far" in C/C++.  In
        //          order to avoid any name conflicts, we use the variable names
        //          "zNear" to reprsent "near", and "zFar" to reprsent "far".
        // ------------------------------------------------------------------------
        static mat4 ortho(float left, float right, float bottom, float top,
            float zNear, float zFar);
        static mat4 ortho2D(float left, float right, float bottom, float top);
        static mat4 frustum(float left, float right, float bottom, float top,
            float zNear, float zFar);
        static mat4 perspective(float fovy, float aspect, float zNear, float zFar);

        static mat4 matrixCompMult(const mat4& A, const mat4& B);
        static mat4 transpose(const mat4& A);

        private:
            vec4 m_[4];
    }; // class mat4
}  // namespace mq
