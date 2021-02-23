#version 430 core

layout(location = 0) out vec4 fragColor;

in vec4 vertexColor; // the input var matching the output var from the vertex shader

void main(void)
{
  fragColor = vertexColor;
}