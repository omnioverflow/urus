#version 430 core

layout(location = 0) out vec4 fragColor;

void main(void)
{
  fragColor = vec4(0.0, gl_FragCoord.y / 2000, 0.0, 1.0);
}