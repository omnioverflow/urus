#version 430 core

layout(location = 0) in vec3 pos;

out vec4 vertexColor;

void main (void)
{
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
    vertexColor = gl_Position;
}