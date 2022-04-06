#include "AABB.h"



AABB::AABB(std::vector<glm::vec3> points)
{

	float max = std::numeric_limits<float>::max();
	float min = std::numeric_limits<float>::min();

	this->maxPoint = glm::vec3(min, min, min);
	this->minPoint = glm::vec3(max, max, max);


	update(points);

}

void AABB::update(std::vector<glm::vec3> points)
{

	for (glm::vec3 point : points) {

		this->maxPoint.x = std::max(point.x, maxPoint.x);
		this->maxPoint.y = std::max(point.y, maxPoint.y);
		this->maxPoint.z = std::max(point.z, maxPoint.z);

		this->minPoint.x = std::min(point.x, minPoint.x);
		this->minPoint.y = std::min(point.y, minPoint.y);
		this->minPoint.z = std::min(point.z, minPoint.z);
	}


}

bool AABB::intersect(AABB * other)
{

	if ( (this->maxPoint.x  < other->minPoint.x) || (this->minPoint.x > other->maxPoint.x) ) {
		return false;
	}

	if ( (this->maxPoint.y < other->minPoint.y) || (this->minPoint.y > other->maxPoint.y) ) {
		return false;
	}

	if ( (this->maxPoint.z < other->minPoint.z) || (this->minPoint.z > other->maxPoint.z) ) {
		return false;
	}

	return true;
}


