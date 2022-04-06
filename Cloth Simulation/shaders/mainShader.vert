#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 vertWorldPos;
out vec3 vertWorldNormal;
out vec2 vertTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0); //vertex position in clip space
	vertWorldPos = vec3(model * vec4(aPos, 1.0)); //vertex position in world space
	vertWorldNormal = mat3(transpose(inverse(model))) * aNormal; //vertex normal in world space
	vertTexCoords = aTexCoords; //vertex texture coordinate
}
