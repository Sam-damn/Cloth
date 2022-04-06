#version 440 core

layout (location = 0) in vec3 aPos;

out vec3 cubeTexCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	mat4 centeredView = mat4(mat3(view)); //remove translation from view matrix
	gl_Position = projection * centeredView * vec4(aPos, 1.0);
	gl_Position = gl_Position.xyww; //set depth buffer to maximum value
	cubeTexCoords = aPos;
}
