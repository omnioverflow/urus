#include "shader.h"

#include <cassert>
#include <iostream>
#include <fstream>

#include "engine/base/compiler_support.h"

namespace tamarix
{
    ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        // TODO: implement
    }

    ShaderProgram::~ShaderProgram()
    {
        // TODO: implement
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

    bool ShaderProgram::link(unsigned int vertexShaderHandle, unsigned int fragmentShaderHandle)
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
            std::cout << "\t" << infoLog << "\n";

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

    /*
    void ShaderProgram::load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        std::ifstream f(vertexShaderPath.c_str());
        bool vertFile = f.good();
        f.close();

        f = std::ifstream(fragmentShaderPath.c_str());
        bool fragFile = f.good();
        f.close();

        std::string v_source = vertex;

        if (vertFile) 
        {
            v_source = ReadFile(vertex);
        }
        std::string f_source = fragment;

        if (fragFile) 
        {
            f_source = ReadFile(fragment);
        }

        unsigned int vert = CompileVertexShader(v_source);
        unsigned int f = CompileFragmentShader(f_source);

        if (LinkShaders(vert, frag)) 
        {
            PopulateAttributes();
            PopulateUniforms();
        }
    }
    */

    void ShaderProgram::bind() const
    {
        glUseProgram(mProgramHandle);
    }

    void ShaderProgram::unbind() const
    {
        glUseProgram(0);
    }
} // namespace tamarix