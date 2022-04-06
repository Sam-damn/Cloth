#pragma once

#include "PointMass.h"
#include "Triangle.h"
#include <vector>

class Face
{
public:
	Face(PointMass* point1, PointMass* point2, PointMass * point3);
	
	float getArea();
	void calcNormal();
	void updatePointNormals();
	void update();

	glm::vec3 normal;
	Triangle * triangle;
	std::vector<PointMass*> points;

	static glm::vec3 calcNormal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);

private:
	PointMass *point1, *point2, *point3;

	void init(PointMass* point1, PointMass* point2, PointMass* point3);
};
