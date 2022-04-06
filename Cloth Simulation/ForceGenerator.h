#pragma once

#include <vector>

#include "PointMass.h"


class ForceGenerator
{
public:
	virtual void applyForce() = 0;
};
