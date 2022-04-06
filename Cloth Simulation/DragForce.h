#pragma once

#include "Drag.h"
#include "ForceGenerator.h"


class DragForce : public ForceGenerator
{
public:
	DragForce();
	DragForce(float damp);

	void applyForce();
	void addPhysicalObject(Drag* body);

private:

	float damp;
	std::vector<Drag*> physicalObjects;
};
