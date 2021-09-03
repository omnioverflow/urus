#include "Node.h"
#include "engine/shader/Shader.h"

namespace urus
{
    Node::Node(const std::vector<float>& vertices, 
                          std::shared_ptr<ShaderProgram> shaderProgram)
    : mVertices(vertices)
    , mShaderProgram(shaderProgram)
    {}
} // namespace urus