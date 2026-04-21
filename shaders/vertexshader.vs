#version 430 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 aTexture;

out vec3 ourColor;
out vec2 TextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  // Need to multiply the matrix from right to left since opengl is right handed
  // This is the final piece to render an object in a 3D aspect
  gl_Position = projection * view * model * vec4(vPos, 1.0);
  ourColor = vColor;
  //TextureCoord = aTexture;
}