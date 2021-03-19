#pragma once

#include <map>
#include <memory>
#include <string>

#include "engine/base/opengl_support.h"

namespace urus
{
	/**
	 * Wrapper around OpenGL shader api
	 */
	class ShaderProgram
	{
		public:
			ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
			ShaderProgram(const ShaderProgram& other) = delete;
			ShaderProgram& operator= (const ShaderProgram& other) = delete;
			ShaderProgram(ShaderProgram&& other) = delete;
			ShaderProgram& operator= (ShaderProgram&& other) = delete;
			virtual ~ShaderProgram();  

			/**
			* Use the shader program in the current rendering state
			*/
			void bind() const;
			/**
			* Remove the shader program from the current rendering state
			*/
			void unbind() const;

			inline GLuint programHandle() const { return mProgramHandle;  }
			inline void useProgram() const { glUseProgram(mProgramHandle); }

		private:
			/**
			* Compile vertes shader at path
			*/
			GLuint compileVertexShader(const std::string& path) const;
			/**
			* Compile fragment shader at path
			*/
			GLuint compileFragmentShader(const std::string& path) const;
			/**
			* Link vertex and fragment shaders, identified by handle to GPU resource
			*/
			bool linkShaders(GLuint vertexShaderHandle, GLuint fragmentShaderHandle);
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
			* Get shader attribute by name
			*/
			GLint getAttrib(const std::string& name) const;
			/**
			* Get shader uniform by name
			*/
			GLint getUniform(const std::string& name) const;

			/**
			* Compile the shader
			*/
			GLuint compileShader(const std::string& path, GLenum shaderType) const;
			/**
			* Read the shader source from file path 
			*/
			std::string readShaderSource(const std::string& path) const;
		
			GLuint 						 mProgramHandle;
			std::map<std::string, GLint> mAttributes;
			std::map<std::string, GLint> mUniforms;
	}; // class Shader
} // namespace urus
