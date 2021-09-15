#pragma once

#include <iostream>

#include "engine/base/OpenGLSupport.h"
#include "Vec.h"

namespace mq
{
    /**
    * mat2 - 2D square matrix
    */    
    class mat2 {
    public:

        explicit mat2(GLFloat d = GLfloat(1.0f));
        mat2(const vec2& a, const vec2& b);
        mat2(GLfloat m00, GLfloat m10, GLfloat m01, GLfloat m11);
        mat2(const mat2& m);

        vec2& operator[] (int i);
        const vec2& operator[] (int i) const;

        mat2& operator+= (const mat2& rhs);
        mat2 operator+ (const mat2& rhs) const;
        mat2& operator-= (const mat2& rhs);
        mat2 operator- (const mat2& rhs) const;

        mat2& operator*= (const mat2& rhs);
        mat2 operator* (const mat2& rhs) const;
        mat2& operator*= (GLFloat s);
        mat2 operator* (GLFloat s) const;
        friend mat2 operator* (GLFloat s, const mat2& rhs);
        vec2 operator* (const vec2& rhs) const;

        mat2& operator/= (GLFloat s);
        mat2 operator/ (GLFloat s) const;
     
        friend std::ostream& operator<< (std::ostream& os, const mat2& rhs);
        friend std::istream& operator>> (std::istream& is, mat2& rhs);

        // Cconversion operators
        operator const GLFloat* () const;
        operator GLfloat* ();

        private:
            vec2  m_[2];
    }; // class mat2

    /**
    * mat3 - 3D square matrix 
    */
    class mat3 {
    public:

        explicit mat3(GLFloat d = GLfloat(1.0f));
        mat3(const vec3& a, const vec3& b, const vec3& c);
        mat3(GLfloat m00, GLfloat m10, GLfloat m20,
            GLfloat m01, GLfloat m11, GLfloat m21,
            GLfloat m02, GLfloat m12, GLfloat m22);
        mat3(const mat3& other);

        vec3& operator[] (int i);
        const vec3& operator[] (int i) const;

        mat3& operator+= (const mat3& rhs);
        mat3 operator+ (const mat3& rhs) const;
        mat3& operator-= (const mat3& rhs);
        mat3 operator- (const mat3& rhs) const;
        mat3& operator*= (const mat3& rhs);
        mat3 operator* (const mat3& rhs) const;
        mat3& operator*= (GLFloat s);
        mat3 operator* (GLFloat s) const;
        friend mat3 operator* (GLFloat s, const mat3& rhs);
        mat3& operator/= (GLFloat s);
        mat3 operator/ (GLFloat s) const;

        vec3 operator* (const vec3& v) const;        

        friend std::ostream& operator<< (std::ostream& os, const mat3& rhs);
        friend std::istream& operator>> (std::istream& is, mat3& rhs);

        // Conversion operators
        operator const GLFloat* () const;
        operator GLfloat* ();

        // --------------------------------------------------------------------
        private:
            vec3  m_[3];
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
        
        mat4(GLFloat d = GLfloat(1.0f));
        mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d);
        mat4(GLfloat m00, GLfloat m10, GLfloat m20, GLfloat m30,
            GLfloat m01, GLfloat m11, GLfloat m21, GLfloat m31,
            GLfloat m02, GLfloat m12, GLfloat m22, GLfloat m32,
            GLfloat m03, GLfloat m13, GLfloat m23, GLfloat m33);
        mat4(const mat4& other);

        vec4& operator[] (int i);
        const vec4& operator[] (int i) const;        

        mat4& operator+= (const mat4& rhs);
        mat4 operator+ (const mat4& rhs) const;
        mat4& operator-= (const mat4& rhs);
        mat4 operator- (const mat4& rhs) const;
        mat4& operator*= (const mat4& rhs);
        mat4 operator* (const mat4& rhs) const;
        mat4& operator*= (GLFloat s);
        mat4 operator* (GLFloat s) const;
        friend mat4 operator* (GLFloat s, const mat4& rhs);
        mat4& operator/= (GLFloat s);
        mat4 operator/ (GLFloat s) const;

        vec4 operator* (const vec4& v) const;

        friend std::ostream& operator<< (std::ostream& os, const mat4& rhs);
        friend std::istream& operator>> (std::istream& is, mat4& rhs);

        // Conversion operators
        operator const GLfloat* () const;
        operator GLfloat* ();

        private:
            vec4 m_[4];
    }; // class mat4

    // ------------------------------------------------------------------------
    //  Non-class mat4 Methods
    // ------------------------------------------------------------------------

    mat4 matrixCompMult(const mat4& A, const mat4& B);
    mat4 transpose(const mat4& A);
    // Rotation matrix generators
    mat4 RotateX(GLfloat theta);
    mat4 RotateY(GLfloat theta);
    mat4 RotateZ(GLfloat theta);
    //  Translation matrix generators
    mat4 Translate(GLfloat x, GLFloat y, GLFloat z);
    mat4 Translate(const vec3& v);
    mat4 Translate(const vec4& v);
    //  Scale matrix generators
    mat4 Scale(GLFloat x, GLFloat y, GLFloat z);
    mat4 Scale(const vec3& v);

    //-------------------------------------------------------------------------
    //  Projection transformation matrix geneartors
    //
    //    Note: Microsoft Windows (r) defines the keyword "far" in C/C++.  In
    //          order to avoid any name conflicts, we use the variable names
    //          "zNear" to reprsent "near", and "zFar" to reprsent "far".
    // ------------------------------------------------------------------------
    mat4 Ortho(GLFloat left, GLFloat right, GLFloat bottom, GLFloat top,
        GLFloat zNear, GLfloat zFar);
    mat4 Ortho2D(GLFloat left, GLFloat right, GLFloat bottom, GLFloat top);
    mat4 Frustum(GLFloat left, GLFloat right, GLFloat bottom, GLFloat top,
        GLFloat zNear, GLFloat zFar);
    mat4 Perspective(GLFloat fovy, GLFloat aspect, GLFloat zNear, GLFloat zFar);
    //  Viewing transformation matrix generation
    mat4 LookAt(const vec4& eye, const vec4& at, const vec4& up);

}  // namespace mq