#include "shader.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

#include "engine/base/opengl_support.h"

namespace urus
{
	namespace
	{
		// consts with internal linkage
		constexpr size_t info_log_size = 512;
		constexpr GLsizei buf_size = 128;
		constexpr GLsizei double_buf_size = 256;
	} // unnamed namespace 

	ShaderProgram::ShaderProgram(const std::string& vertexShaderPath,
								 const std::string& fragmentShaderPath)
	: mProgramHandle(glCreateProgram())
	{
		// TODO: lazy loading, on-demand might be a viable option other than 
		// compiling and linking shaders inside the ctor
		loadShaders(vertexShaderPath, fragmentShaderPath);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(mProgramHandle);
	}

	GLuint ShaderProgram::compileVertexShader(const std::string& path) const
	{
		return compileShader(path, GL_VERTEX_SHADER);
	}

	GLuint ShaderProgram::compileFragmentShader(const std::string& path) const
	{
		return compileShader(path, GL_FRAGMENT_SHADER);
	}

	GLuint ShaderProgram::compileShader(const std::string& path, GLenum shaderType) const
	{
		GLint success = 0; // init as no success
		if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER)
		{
			assert(false);
			return success;
		}

		GLuint handle = glCreateShader(shaderType);
		const auto* source = path.c_str();

		glShaderSource(handle, 1, &source, NULL);
		glCompileShader(handle);

		glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
		if (!success) 
		{
			GLchar infoLog[info_log_size];
			glGetShaderInfoLog(handle, info_log_size, NULL, infoLog);

			std::cout << "Vertex compilation failed.\n";
			std::cout << "\t" << infoLog << std::endl;

			glDeleteShader(handle);

			return success;
		};

		return handle;
	}

	std::string ShaderProgram::readShaderSource(const std::string& path) const
	{
		std::ifstream inputStream;
		inputStream.open(path);

		std::stringstream contents;
		contents << inputStream.rdbuf();
		inputStream.close();

		return contents.str();
	}

	bool ShaderProgram::linkShaders(GLuint vertexShaderHandle, GLuint fragmentShaderHandle)
	{
		glAttachShader(mProgramHandle, vertexShaderHandle);
		glAttachShader(mProgramHandle, fragmentShaderHandle);

		glLinkProgram(mProgramHandle);

		GLint success = 0;

		glGetProgramiv(mProgramHandle, GL_LINK_STATUS, &success);

		if (!success) 
		{
			GLchar infoLog[info_log_size];

			glGetProgramInfoLog(mProgramHandle, info_log_size, NULL, infoLog);

			std::cout << "ERROR: Shader linking failed.\n";
			std::cout << infoLog << "\n";

			glDeleteShader(vertexShaderHandle);

			glDeleteShader(fragmentShaderHandle);

			return false;
		}

		glDeleteShader(vertexShaderHandle);
		glDeleteShader(fragmentShaderHandle);

		return true;
	}

	void ShaderProgram::populateAttributes()
	{
		GLint attribCount = -1;
		GLsizei nameLength = -1;
		GLint attribSize = -1;
		GLenum type = 0;
		GLchar name[buf_size] = { 0 }; // compiler gonna fill unwritten entries with 0s

		glUseProgram(mProgramHandle);
		glGetProgramiv(mProgramHandle, GL_ACTIVE_ATTRIBUTES, &attribCount);

		for (int i = 0; i < attribCount; ++i) 
		{
			memset(name, 0, sizeof(char) * buf_size);
			glGetActiveAttrib(mProgramHandle, (GLuint)i, buf_size, &nameLength, &attribSize, &type, name);

			// get the attribName location
			const GLint attribLocation = glGetAttribLocation(mProgramHandle, name);

			if (attribLocation >= 0) 
			{
				mAttributes[name] = attribLocation;
			}
		}

		glUseProgram(0);
	}

	void ShaderProgram::populateUniforms()
	{       
		GLint uniformCount = -1;
		GLsizei nameLength;
		GLchar name[buf_size] = { 0 };
		GLint uniformSize;
		GLenum type;
		GLchar testName[double_buf_size];

		glUseProgram(mProgramHandle);
		glGetProgramiv(mProgramHandle, GL_ACTIVE_UNIFORMS, &uniformCount);

		for (int i = 0; i < uniformCount; ++i) 
		{
			memset(name, 0, sizeof(char) * buf_size);
			glGetActiveUniform(mProgramHandle, (GLuint)i, buf_size, &nameLength, &uniformSize, &type, name);

			GLint uniform = glGetUniformLocation(mProgramHandle, name);

			if (uniform >= 0)
			{ // Is uniform valid?
				std::string uniformName = name;
				// if name contains [, uniform is an array
				std::size_t found = uniformName.find('[');

				if (found != std::string::npos) 
				{
					// If that uniform was an array, remove the [0] part of the name
					uniformName.erase(uniformName.begin() + found, uniformName.end());
					GLuint uniformIndex = 0;

					// FIXME: test on an array and rename testName var,
					// and rewrite code to make it readable (or add comments)
					while (true) 
					{
						memset(testName, 0, sizeof(char) * double_buf_size);
						sprintf(testName, "%s[%d]", uniformName.c_str(), uniformIndex++);

						GLint uniformLocation = glGetUniformLocation(mProgramHandle, testName);

						if (uniformLocation < 0)                
							break;                   

						mUniforms[testName] = uniformLocation;
					}
				}
				mUniforms[uniformName] = uniform;
			}
		}

		glUseProgram(0);
	}

	void ShaderProgram::loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		auto vertexShaderSource = std::string("");
		auto fragmentShaderSource = std::string("");

		{
			std::ifstream vertShaderInputStream(vertexShaderPath.c_str());
			bool vertShaderFileExists = vertShaderInputStream.good();
			vertShaderInputStream.close();
		
			if (vertShaderFileExists)
				vertexShaderSource = readShaderSource(vertexShaderPath);
		}

		{
			std::ifstream fragShaderInputStream(fragmentShaderPath.c_str());
			bool fragShaderFileExists = fragShaderInputStream.good();
			fragShaderInputStream.close();

			if (fragShaderFileExists)
				fragmentShaderSource = readShaderSource(fragmentShaderPath);
		}

		const auto vertShaderHandle = compileVertexShader(vertexShaderSource);
		const auto fragShaderHandle = compileFragmentShader(fragmentShaderSource);

		if (linkShaders(vertShaderHandle, fragShaderHandle))
		{
			populateAttributes();
			populateUniforms();
		}
	}

	void ShaderProgram::bind() const
	{
		glUseProgram(mProgramHandle);
	}

	void ShaderProgram::unbind() const
	{
		glUseProgram(0);
	}

	GLint ShaderProgram::getAttrib(const std::string& attribName) const
	{
		const auto found = mAttributes.find(attribName);
		if (found == mAttributes.cend())
		{
			std::cerr << "Bad attribute name\n";
			return 0;
		}

		return found->second;
	}

	GLint ShaderProgram::getUniform(const std::string& uniformName) const
	{
		const auto iter = mUniforms.find(uniformName);
		if (iter == mUniforms.cend())
		{
			std::cerr << "Bad uniform name\n";
			return 0;
		}

		return iter->second;
	}
} // namespace urus
