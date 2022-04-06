#pragma once

#include <glm/glm.hpp>


class PointMass
{
public:
	PointMass();
	PointMass(float mass, glm::vec3 pos, bool immovable);
	
	void addForce(const glm::vec3 &force);
	void clearAccum();
	
	float getMass();
	glm::vec3 getPosition();
	glm::vec3 getVelocity();
	glm::vec3 getAcceleration();
	glm::vec3 getNormal();

	void setPosition(glm::vec3 pos);
	void setVelocity(glm::vec3 vel);
	void setMass(float mass);
	void setImmovable();
	void setIdentifier(int id);
	void addNormal(glm::vec3 normal);
	void calculatePointNormal();
	bool immovable;

	void printPos();

	bool operator==(const PointMass& other);

	glm::vec3 prevPostion;
	glm::vec3 position;

	bool collides;

protected:
	int identfier;
	float mass;
	


	
	glm::vec3 velocity;
	glm::vec3 forceAccum;
	glm::vec3 pointNormal;

	glm::vec3 normalAccum;
	unsigned int normalCount;


	void init(float mass, glm::vec3 position, glm::vec3 velocity, bool immovable);

};
