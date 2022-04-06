#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <limits>
#include <algorithm>

class AABB
{
public:
	AABB(std::vector<glm::vec3> points);
	glm::vec3 minPoint;
	glm::vec3 maxPoint;
	

	void update(std::vector<glm::vec3> points);
	bool intersect(AABB * other);


	
};

