#pragma once

namespace urus
{
    enum class DrawMode : int
    {
        Points,
        LineStrip,
        LineLoop,
        Lines,
        Triangles,
        TriangleStrip,
        TriangleFan
    }; // enum DrawMode

    void draw(IndexBuffer& inIndexBuffer, DrawMode mode);
    void draw(unsigned int vertexCount, DrawMode mode);
    void drawInstanced(IndexBuffer& inIndexBuffer, DrawMode mode, unsigned int instanceCount);
    void drawInstanced(unsigned int vertexCount, DrawMode mode, unsigned int numInstances);
} // namespace urus
