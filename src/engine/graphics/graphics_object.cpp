#include "graphics_object.h"
#include "shader.h"

namespace urus
{
    graphics_object::graphics_object(const std::vector<float>& vertices,
                                     std::shared_ptr<ShaderProgram> shaderProgram)
    : mVertices(vertices)
    , mShaderProgram(shaderProgram)
    {}
} // namespace urus