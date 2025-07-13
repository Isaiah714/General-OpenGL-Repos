#version 430 core 

in vec3 ourColor;
in vec2 TextureCoord;

out vec4 FragColor;

// This is how to pass a texture to the fragment shader
uniform sampler2D ourTexture;

void main()
{
  FragColor = texture(ourTexture, TextureCoord) * vec4( ourColor, 1.0 );
}