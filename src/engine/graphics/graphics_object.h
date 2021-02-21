#pragma once

#include <memory>
#include <vector>

namespace urus
{
    class ShaderProgram;
    
    class graphics_object
    {
        public:

            explicit graphics_object(const std::vector<float>& vertices,
                                     std::shared_ptr<ShaderProgram> shaderProgram);
        private:

            std::vector<float> mVertices;
            std::shared_ptr<ShaderProgram> mShaderProgram;
    }; // class graphics_object
} // namespace urus