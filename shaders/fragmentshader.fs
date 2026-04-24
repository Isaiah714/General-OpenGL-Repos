#version 430 core 

in vec3 ourColor;
in vec2 TextureCoord;

out vec4 FragColor;

// These came from the output of vertex shader file (for diffuse ligting effect)
in vec3 normal;
in vec3 fragPos;

// This is how to pass a texture to the fragment shader
// Important Note, these names need to match when calling 
// glGetUniformLocation(), they are global objects
uniform sampler2D metal;
uniform sampler2D tennis;

// These are variables to obtain data for lighting effects
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 lightColor2;
uniform vec3 lightPos2;
uniform vec3 viewPos; // For specular lighting calculation

vec3 calculateLight(vec3 lightColor);

void main() {
  vec3 result = calculateLight(lightColor);
  FragColor = vec4(result, 1.0f);
}

vec3 calculateLight(vec3 lightColor) {
  //FragColor = texture(ourTexture, TextureCoord) * vec4( ourColor, 1.0 ); - gives the rainbow gradient effect
  //FragColor = texture(ourTexture, TextureCoord);
  //FragColor = mix(texture(metal, TextureCoord), texture(tennis, vec2(TextureCoord.x, TextureCoord.y)), 0.2);
  //if(toyColor.x != 0 && lightColor.x != 0) FragColor = toyColor * lightColor;
  //else if(toyColor.x == 0 && lightColor.x == 0) FragColor = vec3(0.0f, 1.0f, 0.0);

  // This is how to calculate ambient lighting
  float ambientStrength = 0.1f;
  vec3 ambient = ambientStrength * lightColor;
  vec3 result = ambient * objectColor;
  //FragColor = vec4(result, 1.0f); // To output the ambient lighting effect
  //FragColor = vec4(0.26, 0.68, 0.02, 1.0);

  // This is how to calculate diffuse lighting. Check out vertexShader to see first steps before getting here
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);

  float diff = max(dot(norm, lightDir), 0.0); // This is to calculate the diffuse impact, we use max to prevent undefined colors
  //lightColor *= 1.5f // This adjust the brightness of the color
  vec3 diffuse = diff * lightColor; // This is to obtain the diffuse component
  result = (ambient + diffuse) * objectColor; // The last step to apply diffuse lighting 
  
  // This is how to calculate specular lighting
  float specularStrength = 10.0f;
  vec3 viewDirection = normalize(viewPos - fragPos);
  vec3 reflectDirection = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32); // The 32 is the brightness value
  vec3 specular = specularStrength * spec * lightColor;
  result = (ambient + diffuse + specular) * objectColor;
  //float exposure = 1.1f;
  //result *= exposure;
  return result;
}