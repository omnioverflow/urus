#version 430 core

uniform vec2 p;

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

// model-view-projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 scaleMatrix;
uniform mat4 rotationMatrix;

out vec4 vert_color;

void main (void)
{
    //gl_Position = projection * view * model * vec4(position, 1.0);    
    vert_color = color;
    gl_Position = rotationMatrix * scaleMatrix * vec4(position) + vec4(p.x, p.y, 0.0, 0.0);
    gl_PointSize = gl_Position.z; 

    // colorV = color;
    // gl_Position = vec4(p, 0.0, 0.0) + position;
    // gl_Position = gl_Position * 0.1;
}