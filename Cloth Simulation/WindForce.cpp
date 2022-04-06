#include "WindForce.h"



WindForce::WindForce()
{
}


WindForce::~WindForce()
{
}

void WindForce::applyForce()
{

	for (Wind* object : physicalObjects) {

		object->applyWind();
	}
}

void WindForce::addPhysicalObject(Wind * body)
{
	physicalObjects.push_back(body);
}

