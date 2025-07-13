#version 430 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 aTexture;

out vec3 ourColor;
out vec2 TextureCoord;

void main()
{
  gl_Position = vec4( vPos, 1.0 );
  ourColor = vColor;
  TextureCoord = aTexture;
}