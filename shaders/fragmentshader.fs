#version 430 core 

in vec3 ourColor;
in vec2 TextureCoord;

out vec4 FragColor;

// This is how to pass a texture to the fragment shader
// Important Note, these names need to match when calling 
// glGetUniformLocation(), they are global objects
uniform sampler2D crate;
uniform sampler2D awesomeface;

void main()
{
  // FragColor = texture(ourTexture, TextureCoord) * vec4( ourColor, 1.0 ); - gives the rainbow gradient effect
  //FragColor = texture(ourTexture, TextureCoord);
  FragColor = mix(texture(crate, TextureCoord), texture(awesomeface, vec2(TextureCoord.x, TextureCoord.y)), 0.2);

}