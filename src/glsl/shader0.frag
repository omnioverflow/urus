#version 430 core

layout (location = 0) out vec4 fragColor;

in vec3 vertexColor;

void main(void)
{
  fragColor = vec4(vertexColor, 1.0f);
}