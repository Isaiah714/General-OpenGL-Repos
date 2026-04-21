#version 430 core 

in vec3 ourColor;
in vec2 TextureCoord;

out vec4 FragColor;

// This is how to pass a texture to the fragment shader
// Important Note, these names need to match when calling 
// glGetUniformLocation(), they are global objects
uniform sampler2D metal;
uniform sampler2D tennis;
uniform vec3 toyColor;
uniform vec3 lightColor;

void main()
{
  //FragColor = texture(ourTexture, TextureCoord) * vec4( ourColor, 1.0 ); - gives the rainbow gradient effect
  //FragColor = texture(ourTexture, TextureCoord);
  //FragColor = mix(texture(metal, TextureCoord), texture(tennis, vec2(TextureCoord.x, TextureCoord.y)), 0.2);
  //if(toyColor.x != 0 && lightColor.x != 0) FragColor = toyColor * lightColor;
  //else if(toyColor.x == 0 && lightColor.x == 0) FragColor = vec3(0.0f, 1.0f, 0.0);
  FragColor = vec4(toyColor * lightColor, 1.0f);


}