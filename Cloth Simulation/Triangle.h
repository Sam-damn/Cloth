#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <limits>


class Triangle
{
public:
	Triangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
	
	glm::vec3 normal;
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 point3;

	float d;

	glm::vec3 getEdge1();
	glm::vec3 getEdge2();
	glm::vec3 getEdge3();

	
	bool intersect4(glm::vec3 r1, glm::vec3 r2, glm::vec3 &Q);
	
	void update(glm::mat4 transform/*glm::vec3 translate*/);
	void scale(float value);
	void scale(glm::mat4 mat);
	bool pointInTriangle(glm::vec3 p);
	float getArea();

private:
	
	
};

