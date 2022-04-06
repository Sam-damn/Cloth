#pragma once

#include <glm/glm.hpp>

#include "ForceGenerator.h"
#include "Gravity.h"


class GravitationalForce : public ForceGenerator
{
public:
	GravitationalForce();
	GravitationalForce(glm::vec3 gravity);
	
	void applyForce();
	void addPhysicalObject(Gravity* body);

private:

	glm::vec3 gravityAcceleration;
	std::vector<Gravity*> physicalObjects;
};
