#pragma once

#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/OpenGL.h>
#  include <OpenGL/glu.h>
#  include <OpenGL/glext.h>
#  include <OpenGL/gl3.h> // <-- for usage of core profile on OS X
// OS X ships with its own implementation of standard GLUT (3.x)
// GLUT development ended many years ago and it is actually considered a non-standard extension
// Therefore we need to include FreeGLUT headers instead of the GLUT framework that ships
// with OS X platform
#  include <GLUT/glut.h> // <-- can't rely on this as explained above
//#  include "GL/freeglut.h"
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif  // __APPLE__
