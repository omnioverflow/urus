#pragma once

#include "vec.h"
#include "vertex.h"

// FIXME: remove namespace using
using namespace walnut;

enum class VAO_IDs : GLuint 
{
  Triangles = 0,
  CoordinateSystem,
  Count
};

enum class VBO_IDs : GLuint 
{
  Triangles = 0,
  CoordinateSystem,
  Count
};

enum class Attrib_IDs : GLuint 
{
  vPosition = 0
};

constexpr auto NUM_VAO = static_cast<size_t>(VAO_IDs::Count);
GLuint VAOs[NUM_VAO];
GLuint Buffers[static_cast<size_t>(VBO_IDs::Count)];
constexpr GLuint NumVertices[NUM_VAO] = { 4, 6 };
GLuint ShaderPrograms[2];
std::vector<std::map<std::string, GLint>>
  ShaderUniforms
  {
    { { "p", -1}, {"scaleMatrix", -1}, {"rotationMatrix", -1} },
    { { "scaleMatrix", -1}, {"rotationMatrix", -1} }
  };

// /!\ Note, order is important
const std::vector<std::string> VertexShaderNames = 
{
  "color.vert",
  "coord_sys.vert"
};

// Note, order is important
const std::vector<std::string> FragmentShaderNames = 
{
  "color.frag",
  "coord_sys.frag"
};

//-----------------------------------------------------------------------------

void loadBufferData();
GLuint loadShader(const std::string& vertShaderName, const std::string& fragShaderName, GLuint shaderId);
void loadShaders();

//-----------------------------------------------------------------------------

// load Vertex Buffer Objects
void loadBufferData() 
{
  {
    Vertex vertexData[4] = {
      // { "geom. coordinate", "color" }
      { vec4(-0.5, -0.5, 0.0, 1.0), vec4(1.0, 0.0, 0.0, 1.0) },
      { vec4(-0.5,  0.5, 0.0, 1.0), vec4(0.0, 1.0, 0.0, 1.0) },
      { vec4(0.5,  0.5, 0.0, 1.0), vec4(0.0, 0.0, 1.0, 1.0) },
      { vec4(0.5, -0.5, 0.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0) }
    };

    glGenVertexArrays(1, &VAOs[0]);
    glBindVertexArray(VAOs[0]);

    glGenBuffers(1, &Buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertexData, GL_STATIC_DRAW);

    // pass vertex attributes
    const GLuint positionVA = 0, colorVA = 1;
    glEnableVertexAttribArray(positionVA);
    glEnableVertexAttribArray(colorVA);
    glVertexAttribPointer(positionVA, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);
    glVertexAttribPointer(colorVA, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)sizeof(vec4));
  }

  // for the coordinate system
  {
    constexpr auto numVertices = NumVertices[static_cast<size_t>(VAO_IDs::CoordinateSystem)];
    // coordinate system segments 
    Vertex vertexData[numVertices] = {
      // x-axis , red
      { vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) },
      { vec4(1.5f,  0.0f, 0.0f, 1.0f), vec4(1.0, 0.0, 0.0, 1.0) },
      // y-axis, green
      { vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) },
      { vec4(0.0f, 1.0f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) },
      // z-axis, blue
      { vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f) },
      { vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f) }
    };

    glGenVertexArrays(1, &VAOs[1]);
    glBindVertexArray(VAOs[1]);

    glGenBuffers(1, &Buffers[1]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), vertexData, GL_STATIC_DRAW);

    // pass vertex attributes
    const GLuint positionVA = 0, colorVA = 1;
    glEnableVertexAttribArray(positionVA);
    glEnableVertexAttribArray(colorVA);
    glVertexAttribPointer(positionVA, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);
    glVertexAttribPointer(colorVA, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)sizeof(vec4));
  }  
}

void loadShaders() 
{
  const auto numShaders = VertexShaderNames.size(); 
  assert(numShaders == FragmentShaderNames.size());
  for (int i = 0; i < numShaders; ++i)
    ShaderPrograms[i] = loadShader(VertexShaderNames[i], FragmentShaderNames[i], i);
}

GLuint loadShader(const std::string& vertShaderName,
                  const std::string& fragShaderName,
                  GLuint shaderId) 
{
  const GLuint shaderProgram = initShader(vertShaderName.c_str(), fragShaderName.c_str());

  auto& uniforms = ShaderUniforms[shaderId];
  for (auto& uniform : uniforms) {
    uniform.second = glGetUniformLocation(shaderProgram, uniform.first.c_str());
    if (uniform.second < 0)
      std::cout << "Shader " << shaderId <<
        " does not contain the '" << uniform.first << "' uniform." << std::endl;
  }

  return shaderProgram;
}