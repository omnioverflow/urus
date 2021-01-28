#include "draw.h"

// FIXME: include OpenGL header

namespace urus
{
    static GLenum drawModeToGLEnum(DrawMode input)
    {
        switch (input)
        {
            case DrawMode::Points:
                return GL_POINTS;

            case DrawMode::LineStrip:
                return GL_LINE_STRIP;

            case DrawMode::LineLoop:
                return GL_LINE_LOOP;

            case DrawMode::Lines:
                return GL_LINES;

            case DrawMode::Triangles:
                return GL_TRIANGLES;

            case DrawMode::TriangleStrip:
                return GL_TRIANGLE_STRIP;

            case DrawMode::TriangleFan:
                return GL_TRIANGLE_FAN;

            // unreachable code hot
            assert(false);

            return 0;
        }
    } 
 } // namespace urus
