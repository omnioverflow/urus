#pragma once

#include <memory>
#include <vector>

namespace urus
{
    class ShaderProgram;
    
    class Node
    {
        public:

            explicit Node(const std::vector<float>& vertices,
                          std::shared_ptr<ShaderProgram> shaderProgram);
        private:

            std::vector<float> mVertices;
            std::shared_ptr<ShaderProgram> mShaderProgram;
    }; // class node
} // namespace urus