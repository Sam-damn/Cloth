#include "Vertex.h"


Vertex::Vertex()
{
}

Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords)
{
	this->position = position;
	this->normal = normal;
	this->texCoords = texCoords;
}
