#pragma once

#include <map>
#include <memory>
#include <string>

namespace tamarix
{
    /**
     * Wrapper around OpenGL boiler-plate code to compile, link and access shaders
     */
    class ShaderProgram
    {
        friend class ShaderFactory;

        public:
            ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
            ShaderProgram(const ShaderProgram&) = delete;
            ShaderProgram& operator=(const ShaderProgram&) = delete;
            virtual ~ShaderProgram();            

            unsigned int compileVertexShader(const std::string& path) const;
            unsigned int compileFragmentShader(const std::string& path) const;
            bool link(unsigned int vertexShaderHandle, unsigned int fragmentShaderHandle);
            void populateAttributes();
            void populateUniforms();
            void load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

            void bind() const;
            void unbind() const;
            unsigned int getAttrib(const std::string& name) const;
            unsigned int getUniform(const std::string& name) const;
            unsigned int getHandle() const;
               

        private:
            unsigned int compileShader(const std::string& path, unsigned int shaderType) const;
            unsigned int mProgramHandle;
            std::map<std::string, unsigned int> mAttributes;
            std::map<std::string, unsigned int> mUniforms;
    }; // class Shader
} // namespace tamarix
