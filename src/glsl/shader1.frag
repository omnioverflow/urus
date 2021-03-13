#version 430 core

out vec4 fragColor;

in vec3 vertexColor; 
in vec2 texCoord;

uniform sampler2D u_texture;

void main(void)
{
  fragColor = texture(u_texture, texCoord);
}