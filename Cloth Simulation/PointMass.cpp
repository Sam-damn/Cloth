#include <iostream>

#include "PointMass.h"


PointMass::PointMass()
{
	init(1.0f, glm::vec3(0, 1.0f, 0), glm::vec3(0, 0, 0), false);
}

PointMass::PointMass(float mass, glm::vec3 pos, bool immovable)
{
	init(mass, pos, glm::vec3(0, 0, 0), immovable);
}


void PointMass::init(float mass, glm::vec3 position, glm::vec3 velocity, bool immovable)
{
	this->mass = mass;
	this->immovable = immovable;
	this->position = position;
	this->prevPostion = position;
	this->velocity = velocity;
	this->forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);
	this->collides = false;
}

float PointMass::getMass()
{
	return mass;
}

glm::vec3 PointMass::getPosition()
{
	return position;
}

glm::vec3 PointMass::getVelocity()
{
	return velocity;
}

glm::vec3 PointMass::getAcceleration()
{
	return forceAccum / mass;
}

glm::vec3 PointMass::getNormal()
{
	return pointNormal;
}

void PointMass::setPosition(glm::vec3 pos)
{
	if (!immovable) {
		prevPostion = this->position;
		position = pos;
	}
}

void PointMass::setVelocity(glm::vec3 vel)
{
	if (!immovable) {
		velocity = vel;
	}
}

void PointMass::setMass(float mass)
{
	this->mass = mass;
}

void PointMass::setImmovable()
{
	immovable = true;
}

void PointMass::setIdentifier(int id)
{
	this->identfier = id;
}

//add a face normal to the normal accumulator
void PointMass::addNormal(glm::vec3 normal)
{
	normalAccum += normal;
	normalCount++;
}

//calculate average normal then clear the accumulator
void PointMass::calculatePointNormal()
{
	pointNormal = normalAccum / (float)normalCount;
	normalAccum = glm::vec3(0);
	normalCount = 0;
}

void PointMass::addForce(const glm::vec3 &force)
{
	forceAccum += force;
}

void PointMass::clearAccum()
{
	forceAccum = glm::vec3(0, 0, 0);
}

void PointMass::printPos()
{
	std::cout << position.x << " " << position.y << "\n";
}

bool PointMass::operator==(const PointMass & other)
{

	return this->identfier == other.identfier;

}
