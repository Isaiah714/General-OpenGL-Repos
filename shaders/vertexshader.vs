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
  //normal = aNormal; // initializing all normal vectors from the cube

  // This piece of code prevents the lighting from breaking when doing non-uniform scaling
  // Taking the inverse of the matrix helps counteract the stretching caused by non-uniform scaling
  // Takeing the transpose of the matrix helps reshape the transformation so the vectors can correctly
  // be perpindicular to the objects surfaces. transpose and inverse must be a combined operation for success
  // The downside of doing this operation is it's very expensive on the GPU side. So try to avoid doing this here
  normal = mat3(transpose(inverse(model))) * aNormal;


  //ourColor = vColor;
  //TextureCoord = aTexture;
}