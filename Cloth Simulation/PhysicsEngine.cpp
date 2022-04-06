#include "PhysicsEngine.h"
#include "Cloth.h"
#include "GravitationalForce.h"
#include "DragForce.h"
#include "WindForce.h"


PhysicsEngine::PhysicsEngine() :
	timeStep(1.0f / 60.0),
	timeAccumulator(0.0f)
{
}

PhysicsEngine::PhysicsEngine(Render* renderer) :
	timeStep(1.0f / 60.0),
	timeAccumulator(0.0f)
{
	this->renderer = renderer;

	//initialize forces 
	GravitationalForce* gravity = new GravitationalForce(glm::vec3(0, -4.8f, 0));
	DragForce* drag = new DragForce(2.0f);
	WindForce* wind = new WindForce();

	this->externalForces.push_back(gravity);
	this->externalForces.push_back(drag);
	this->externalForces.push_back(wind);

	//initialize objects
	int width = 25;
	int height = 25;

	Cloth* cloth = new Cloth(glm::vec3(-0.5f, 0.75f, -0.5f), width, height, 1.0f, 1.0f, 200.0f);

	this->physicalObjects.push_back(cloth);
	gravity->addPhysicalObject(cloth);
	drag->addPhysicalObject(cloth);
	wind->addPhysicalObject(cloth);

	size = (width - 1) * (height - 1) * 8 * 6;
	sizeVertices = width * height * 8;
	sizeIndices = (width - 1) * (height - 1) * 6;

	//this->renderer->initCloth(cloth->getVertexData(), size);
	this->renderer->initClothIndexed(cloth->getVertexDataIndexed(), sizeVertices, cloth->getIndexData(), sizeIndices);
}

void PhysicsEngine::updatePhyics(float deltaTime)
{
	this->timeAccumulator += deltaTime;

	while (timeAccumulator >= timeStep) {



		//apply the external forces (~ 0.2ms)
		for (ForceGenerator* forceGenerator : externalForces) {
			forceGenerator->applyForce();
		}



		//call update method on each body which calculates the internal forces and then integrates (~ 4.5ms)


		for (DeformableBody* object : physicalObjects) {
			object->update(timeStep);
		}


		// collision detection with shape
		for (DeformableBody* object : physicalObjects) {

			if (object->box->intersect(shape->box)) {
				object->collide(shape);

			}
		}

		timeAccumulator -= timeStep;
	}

	//(~ 2ms)
	this->updateRenderer();

}

void PhysicsEngine::addPhysicalObject(DeformableBody* physicalObject)
{
	physicalObjects.push_back(physicalObject);
}

void PhysicsEngine::addExternalForce(ForceGenerator* externalForce)
{
	externalForces.push_back(externalForce);
}

void PhysicsEngine::addShape(RigidShape* shape)
{
	this->shape = shape;

}

void PhysicsEngine::updateRenderer()
{
	Cloth* cloth = (Cloth*)physicalObjects[0];

	//this->renderer->updateCloth(cloth->getVertexData(), size);
	this->renderer->updateCloth(cloth->getVertexDataIndexed(), sizeVertices);
}
