#version 440 core

out vec4 FragColor;

uniform vec3 lightColor;

void main()
{
	vec3 lightColor2 = lightColor;
    FragColor = vec4(lightColor, 1.0f);
}
