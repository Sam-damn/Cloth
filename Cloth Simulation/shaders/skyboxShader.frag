#version 440 core

out vec4 FragColor;

in vec3 cubeTexCoords;

uniform samplerCube skyBox;

void main()
{
    FragColor = texture(skyBox, cubeTexCoords);
}
