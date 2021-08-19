#include "node.h"
#include "engine/graphics/shader/shader.h"

namespace urus
{
    Node::Node(const std::vector<float>& vertices, 
                          std::shared_ptr<ShaderProgram> shaderProgram)
    : mVertices(vertices)
    , mShaderProgram(shaderProgram)
    {}
} // namespace urus