#version 430 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shine;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Material material;

vec3 calculateLight(vec3 lColor, vec3 lPos, vec3 normal, vec3 fragPos, vec3 vPos);

void main() {
  vec3 result = calculateLight(lightColor, lightPos, Normal, FragPos, viewPos);
  FragColor = vec4(result, 1.0f);
}

vec3 calculateLight(vec3 lColor, vec3 lPos, vec3 normal, vec3 fragPos, vec3 vPos) {
  vec3 ambient = lColor * material.ambient;

  normal = normalize(normal);
  vec3 lightDirection = normalize(lPos - fragPos);
  float diffuseImpact = max(dot(normal, lightDirection), 0.0f);
  vec3 diffuse = lColor * (diffuseImpact * material.diffuse);

  vec3 viewDirection = normalize(vPos - fragPos);
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float specularComponent = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shine);
  vec3 specular = lColor * (specularComponent * material.specular);

  vec3 result = ambient + diffuse + specular;

  return result;
}
