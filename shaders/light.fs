version 430 core

in vec3 color;

out vec3 FragColor;

uniform vec3 lightColor;

void main()
{
	FragColor = vec4(lightColor, 1.0f);
}