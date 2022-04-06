#pragma once

#include <vector>

#include "PointMass.h"


class Integrator
{
public:
	virtual void solve(float deltaTime) = 0;

protected:

	std::vector<PointMass*> points;
};
