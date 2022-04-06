#pragma once

#include <vector>

#include "DeformableBody.h"
#include "Render.h"


class PhysicsEngine
{
public:
	PhysicsEngine();
	PhysicsEngine(Render* renderer);
	void updatePhyics(float deltaTime);

	void addPhysicalObject(DeformableBody* physicalObject);
	void addExternalForce(ForceGenerator* externalForce);

	void addShape(RigidShape * shape);

private:	
	std::vector<DeformableBody*> physicalObjects;
	std::vector<ForceGenerator*> externalForces;

	Render * renderer;

	float timeAccumulator;
	float timeStep;

	void updateRenderer();

	//int width;
	//int height;

	int size;
	int sizeVertices;
	int sizeIndices;

	RigidShape* shape;
};
