#version 430 core

in vec4 vert_color;
layout(location = 0) out vec4 fragColor;

void main(void)
{
  fragColor = vec4(gl_FragCoord.x / 2000, 0.0, 0.0, 1.0);
}