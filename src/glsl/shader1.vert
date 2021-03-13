#version 430 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 inTexCoord;

out vec3 vertexColor;
out vec2 texCoord;

void main (void)
{
    gl_Position = vec4(pos, 1.0f);
    vertexColor = color;
    texCoord = inTexCoord;
}