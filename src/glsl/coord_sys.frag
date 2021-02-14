#version 430

in vec4 vert_color;
layout(location = 0) out vec4 fragColor;

void main(void)
{
    fragColor = vert_color;
}