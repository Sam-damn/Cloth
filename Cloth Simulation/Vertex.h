#pragma once

#include <glm/glm.hpp>


class Vertex
{
public:
	Vertex();
	Vertex(glm::vec3 position, glm::vec3 normal , glm::vec2 texCoords);

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;

};
