#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>


//to prevent circular includes use forward declaration in the header file and include the header in the cpp file
class IndexedMesh;
class ShaderProgram;

struct Attenuation {
	float constant;
	float linear;
	float quadratic;
};

class LightSource
{
public:
	LightSource();
	LightSource(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor);

	void initDefaultMesh();
	void draw(ShaderProgram program);

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

private:
	IndexedMesh *lightMesh;
};
