// auto-linking with glew64
#ifdef GLEW_STATIC
  #ifdef NDEBUG
    #pragma comment (lib, "glew64_static.lib") 
  #else
    #pragma comment (lib, "glew64_staticd.lib") 
  #endif
#else
  #ifdef NDEBUG
    #pragma comment (lib, "glew64.lib") 
  #else
    #pragma comment (lib, "glew64d.lib") 
  #endif
#endif

#pragma once 

//------------------------------------------------------------------------------
// 
// --- system headers ---
//
//------------------------------------------------------------------------------

#include <cmath>
#include <iostream>

// in case if not provided from <math.h> or <cmath>; must be there though.
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

//------------------------------------------------------------------------------
//
// --- Include OpenGL header files and helpers ---
//
//   The location of these files vary by operating system.  We've included
//     copies of open-soruce project headers in the "GL" directory local
//     this this "include" directory.
//
//------------------------------------------------------------------------------

#include "foundation/opengl_compiler_support.h"

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

//----------------------------------------------------------------------------
//
//  --- Utils and consts ---
//
//------------------------------------------------------------------------------

namespace util {

// Helper function to load a text file
char* readShaderSource(const char* shaderFile);

// Helper to load vertex and fragment shaders
GLuint initShader(const char* vertexShaderFile, const char* fragmentShaderFile);

//  Defined constant for when numbers are too small to be used in the
//  denominator of a division operation.  This is only used if the
//  DEBUG macro is defined.
const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);

//  Degrees-to-radians constant 
const GLfloat  DegreesToRadians = M_PI / 180.0;

}  // namespace util


//------------------------------------------------------------------------------
//
// basic includes
//
//------------------------------------------------------------------------------
#include "../vec.h"
#include "../mat.h"