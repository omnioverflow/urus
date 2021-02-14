#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 scaleMatrix;
uniform mat4 rotationMatrix;

out vec4 vert_color;

void main (void)
{
    vert_color = color;
    gl_Position = rotationMatrix * scaleMatrix * vec4(position);
    gl_PointSize = gl_Position.z; 
}