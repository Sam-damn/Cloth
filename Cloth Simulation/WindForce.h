#pragma once

#include "Wind.h"
#include "ForceGenerator.h"

class WindForce : public ForceGenerator

{
public:
	WindForce();
	~WindForce();


	void applyForce();
	void addPhysicalObject(Wind* body);

private:


	std::vector<Wind*> physicalObjects;
};

