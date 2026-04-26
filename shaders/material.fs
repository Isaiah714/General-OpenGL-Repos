#version 430 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shine;
}

out vec3 FragColor;

in vec3 aNormal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Material material;

vec3 calculateLight(vec3 lColor, vec3 lPos, vec3 normal, vec3 fragPos, vec3 vPos);

void main() {
  aNormal = normalize(aNormal);

}

vec3 calculateLight(vec3 lColor, vec3 lPos, vec3 normal, vec3 fragPos, vec3 vPos) {
  vec3 ambient = lColor * material.ambient;

  vec3 lightDirection = normalize(lPos, fragPos);
  float diffuseComponent = max(dot(normal, lightDirection), 0.0f);
  vec3 diffuse = lColor * (diffuseComponent * material.diffuse);

  vec3 viewDirection = normalize(vPos - fragPos);
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float specularComponent = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shine);
  vec3 specular = lColor * (specularComponent * material.specular);

  vec3 result = ambient + diffuse + specular;
  FragColor = vec4(result, 1.0f);


}
