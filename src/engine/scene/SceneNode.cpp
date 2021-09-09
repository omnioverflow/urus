#include "SceneNode.h"
#include "engine/shader/Shader.h"

namespace urus
{
    SceneNode::SceneNode(const std::vector<float>& vertices, 
                          std::shared_ptr<ShaderProgram> shaderProgram)
    : mVertices(vertices)
    , mShaderProgram(shaderProgram)
    {}
} // namespace urus