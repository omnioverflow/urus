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

		private:
			/**
			* Compile vertes shader at path
			*/
			unsigned int compileVertexShader(const std::string& path) const;
			/**
			* Compile fragment shader at path
			*/
			unsigned int compileFragmentShader(const std::string& path) const;
			/**
			* Link vertex and fragment shaders, identified by handle to GPU resource
			*/
			bool linkShaders(unsigned int vertexShaderHandle, unsigned int fragmentShaderHandle);
			/**
			* Populate shader attributes mapping from the attributes stored inside the shader program
			*/
			void populateAttributes();
			/**
			* Populate shader uniforms mapping from the uniforms in shader program
			*/
			void populateUniforms();
			/**
			* Load vertex and fragment shaders (i.e. compile and link)
			*/
			void loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

			/**
			* Use the shader program in the current rendering state
			*/
			void bind() const;
			/**
			* Remove the shader program from the current rendering state
			*/
			void unbind() const;

			/**
			* Get shader attribute by name
			*/
			unsigned int getAttrib(const std::string& name) const;
			/**
			* Get shader uniform by name
			*/
			unsigned int getUniform(const std::string& name) const;

			/**
			* Compile the shader
			*/
			unsigned int compileShader(const std::string& path, unsigned int shaderType) const;
			/**
			* Read the shader source from file path 
			*/
			std::string readShaderSource(const std::string& path) const;

		private:
			unsigned int mProgramHandle;
			std::map<std::string, unsigned int> mAttributes;
			std::map<std::string, unsigned int> mUniforms;
	}; // class Shader
} // namespace tamarix
