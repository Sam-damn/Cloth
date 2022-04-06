#pragma once

#include <glm/glm.hpp>


class Gravity
{
public:
	virtual void applyGravity(glm::vec3 gravityAccelration) = 0;
};
