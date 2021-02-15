#include "shader.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

#include "engine/base/compiler_support.h"

namespace urus
{
	ShaderProgram::ShaderProgram(const std::string& vertexShaderPath,
								 const std::string& fragmentShaderPath)
	: mProgramHandle(glCreateProgram())
	{
		// TODO: lazy loading option might be a viable option other than 
		// compiling and linking shaders inside the ctor
		loadShaders(vertexShaderPath, fragmentShaderPath);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(mProgramHandle);
	}

	unsigned int ShaderProgram::compileVertexShader(const std::string& path) const
	{
		return compileShader(path, GL_VERTEX_SHADER);
	}

	unsigned int ShaderProgram::compileFragmentShader(const std::string& path) const
	{
		return compileShader(path, GL_FRAGMENT_SHADER);
	}

	unsigned int ShaderProgram::compileShader(const std::string& path, unsigned int shaderType) const
	{
		int success = 0; // init as no success
		if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER)
		{
			assert(false);
			return success;
		}

		unsigned int handle = glCreateShader(shaderType);
		const char* source = path.c_str();

		glShaderSource(handle, 1, &source, NULL);
		glCompileShader(handle);


		glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
		if (!success) 
		{
			char infoLog[512];
			glGetShaderInfoLog(handle, 512, NULL, infoLog);

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

	bool ShaderProgram::linkShaders(unsigned int vertexShaderHandle, unsigned int fragmentShaderHandle)
	{
		glAttachShader(mProgramHandle, vertexShaderHandle);
		glAttachShader(mProgramHandle, fragmentShaderHandle);

		glLinkProgram(mProgramHandle);

		int success = 0;

		glGetProgramiv(mProgramHandle, GL_LINK_STATUS, &success);

		if (!success) 
		{
			char infoLog[512];

			glGetProgramInfoLog(mProgramHandle, 512, NULL, infoLog);

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
		int count = -1;
		int length;
		char name[128];
		int size;

		GLenum type;

		glUseProgram(mProgramHandle);
		glGetProgramiv(mProgramHandle, GL_ACTIVE_ATTRIBUTES, &count);

		for (int i = 0; i < count; ++i) 
		{
			memset(name, 0, sizeof(char) * 128);
			glGetActiveAttrib(mProgramHandle, (GLuint)i, 128, &length, &size, &type, name);

			int attrib = glGetAttribLocation(mProgramHandle, name);

			if (attrib >= 0) 
			{
				mAttributes[name] = attrib;
			}
		}

		glUseProgram(0);
	}

	void ShaderProgram::populateUniforms()
	{        
		int count = -1;
		int length;
		char name[128];
		int size;
		GLenum type;
		char testName[256];

		glUseProgram(mProgramHandle);
		glGetProgramiv(mProgramHandle, GL_ACTIVE_UNIFORMS, &count);

		for (int i = 0; i < count; ++i) 
		{
			memset(name, 0, sizeof(char) * 128);
			glGetActiveUniform(mProgramHandle, (GLuint)i, 128, &length, &size, &type, name);

			int uniform = glGetUniformLocation(mProgramHandle, name);

			if (uniform >= 0)
			{ // Is uniform valid?
				std::string uniformName = name;
				// if name contains [, uniform is array
				std::size_t found = uniformName.find('[');

				if (found != std::string::npos) 
				{
					uniformName.erase(uniformName.begin() + found, uniformName.end());
					unsigned int uniformIndex = 0;

					while (true) 
					{
						memset(testName,0,sizeof(char)*256);

						sprintf(testName, "%s[%d]",
								uniformName.c_str(),
								uniformIndex++);

						int uniformLocation = glGetUniformLocation(mProgramHandle, testName);

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

	unsigned int ShaderProgram::getAttrib(const std::string& attribName) const
	{
		const auto found = mAttributes.find(attribName);
		if (found == mAttributes.cend())
		{
			std::cerr << "Bad attribute name\n";
			return 0;
		}

		return found->second;
	}

	unsigned int ShaderProgram::getUniform(const std::string& uniformName) const
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