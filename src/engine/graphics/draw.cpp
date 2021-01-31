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

    void draw(unsigned int vertexCount, DrawMode mode)
    {
        glDrawArrays(drawModeToGLEnum(mode), 0, vertexCount);
    }

    void drawInstanced(unsigned int vertexCount, DrawMode mode, unsigned int nbInstances)
    {
        glDrawArraysInstanced(drawModeToGLEnum(mode), vertexCount, nbInstances);
    }

    void draw(IndexBuffer& inIndexBuffer, DrawMode mode)
    {
        const auto handle = inIndexBuffer.getHandle();
        const auto nbIndices = inIndexBuffer.getCount();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
        glDrawElements(drawModeToGLEnum(mode), mbIndices, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void drawInstanced(IndexBuffer& inIndexBuffer, DrawMode mode, unsigned int instanceCount)
    {
        const auto handle = inIndexBuffer.getHandle();
        const auto nbIndices = inIndexBuffer.getCount();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
        glDrawElementsInstanced(drawModeToGLEnum(mode), nbIndices, GL_UNSIGNED_INT, 0, instanceCount);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
 } // namespace urus
