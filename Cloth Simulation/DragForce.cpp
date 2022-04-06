#include "DragForce.h"


DragForce::DragForce()
{
	this->damp = 0;
}

DragForce::DragForce(float damp)
{
	this->damp = damp;
}


void DragForce::applyForce()
{
	for (Drag* object : physicalObjects) {

		object->applyDrag(this->damp);
	}
}

void DragForce::addPhysicalObject(Drag * body)
{
	physicalObjects.push_back(body);
}
