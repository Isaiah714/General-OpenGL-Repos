#version 430 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 aNormal; // To obtain all normal vectors for the diffuse lighting effect
//layout (location = 1) in vec3 vColor;
//layout (location = 2) in vec2 aTexture;

out vec3 ourColor;
out vec2 TextureCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  // Need to multiply the matrix from right to left since opengl is right handed
  // This is the final piece to render an object in a 3D aspect
  gl_Position = projection * view * model * vec4(vPos, 1.0);
  fragPos = vec3(model * vec4(vPos, 1.0f)); // This obtains the fragments position in world space, an important step in diffuse lighting
  normal = mat3(transpose(inverse(model))) * aNormal; // This is to get the normal matrix
  normal = aNormal; // initializing all normal vectors from the cube
  //ourColor = vColor;
  //TextureCoord = aTexture;
}