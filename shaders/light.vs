#version 430 core

layout (location = 0) in vec3 vPos;

uniform mat4 lightModel;
uniform mat4 lightView;
uniform mat4 lightProjection;

void main()
{
  gl_Position = lightProjection * lightView * lightModel * vec4(vPos, 1.0);
}