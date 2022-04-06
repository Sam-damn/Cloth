#include "Spring.h"


Spring::Spring(float k, float d, PointMass * particle1, PointMass * particle2,float maxRate)
{
	init(k, d, particle1, particle2,maxRate);

}


float Spring::getRestLength()
{
	return this->restLength;
}

float Spring::getCurrentLength()
{
	glm::vec3 diff = pointMasses[0]->getPosition() - pointMasses[1]->getPosition();
	return glm::length(diff);
}

void Spring::setMasterPoint(PointMass * master)
{
	if((*pointMasses[0])==(*master)){
		masterPoint = 0;
	}
	else {
		masterPoint = 1;
	}

}

//performance critical function (optimize to shit)
void Spring::applyForce()
{

	glm::vec3 posDiff = pointMasses[0]->getPosition() - pointMasses[1]->getPosition();

	glm::vec3 velDiff = pointMasses[0]->getVelocity() - pointMasses[1]->getVelocity();
	
	//float length = getCurrentLength();
	float length = glm::length(posDiff); //~ 10fps faster

	glm::vec3 dir = glm::normalize(posDiff);

	glm::vec3 force = -(springConst * (length - restLength)) * dir - (velDiff * dampingConst);
	
	

	pointMasses[0]->addForce(force);
	pointMasses[1]->addForce(-force);

}

void Spring::adjust()
{
	PointMass* master = pointMasses[masterPoint];
	PointMass* other = pointMasses[(masterPoint + 1) % 2];

	float currentLength = getCurrentLength();
	float deformRate =  ( (currentLength - restLength) / restLength)*100;

	if (deformRate > maxDeformRate) {

		glm::vec3 pos = master->getPosition() - restLength* (1 + maxDeformRate / 100) * (master->getPosition() - other->getPosition()) / currentLength;
		other->setPosition(pos);
	}

}

void Spring::adjust2()
{
	PointMass* master = pointMasses[masterPoint];
	PointMass* other = pointMasses[(masterPoint + 1) % 2];

	float currentLength = getCurrentLength();
	float deformRate = ((currentLength - restLength) / restLength) * 100;

	

	if(deformRate > maxDeformRate) {

		glm::vec3 dir = (master->getPosition() - other->getPosition()) / currentLength;


		

		if (master->immovable) {
			glm::vec3 pos = master->getPosition() - restLength * (1 + maxDeformRate / 100)*dir;
			other->setPosition(pos);

		}

		else if (other->immovable) {

			glm::vec3 pos = other->getPosition() +restLength * (1 + maxDeformRate / 100)*dir;
			master->setPosition(pos);

		}

		else
		{
			float lengthdiff = currentLength - restLength * (1 + maxDeformRate / 100);

			
			glm::vec3 pos1 = other->getPosition() + (lengthdiff / 2)*dir;
			glm::vec3 pos2 = master->getPosition() - (lengthdiff / 2)*dir;

			master->setPosition(pos2);
			other->setPosition(pos1);


		}

	}


}

bool Spring::adjust3(float &error)
{
	PointMass* point1 = pointMasses[masterPoint];
	PointMass* point2 = pointMasses[(masterPoint + 1) % 2];

	glm::vec3 dir = point2->getPosition() - point1->getPosition();

	float desired_length = restLength + restLength * (maxDeformRate / 100);

	float length = glm::length(dir);

	if (/*(restLength - restLength*(maxDeformRate/100)) <= */length <= desired_length) {
		return false;
	}

	float diff = 0.5f*(length - desired_length);

	glm::vec3 posdiff = diff * (dir / length);
	glm::vec3 newpos1 = point1->getPosition() + posdiff;
	glm::vec3 newpos2 = point2->getPosition() - posdiff;
	point1->setPosition(newpos1);
	point2->setPosition(newpos2);

	error = (length - desired_length) / desired_length;



}

void Spring::adjust_vel()
{
	PointMass* master = pointMasses[masterPoint];
	PointMass* other = pointMasses[(masterPoint + 1) % 2];

	float currentLength = getCurrentLength();
	float deformRate = ((currentLength - restLength) / restLength) * 100;


	if (deformRate >= maxDeformRate) {

		glm::vec3 dir = (other->getPosition()-master->getPosition()  ) / currentLength;
		glm::vec3 dir2 = (master->getPosition() - other->getPosition()) / currentLength;

		glm::vec3 vel1 = master->getVelocity();
		glm::vec3 vel2 = other->getVelocity();

		

		float dot1 = glm::dot(dir, master->getVelocity());
		float dot2 = glm::dot(dir2, other->getVelocity());

		glm::vec3 vel1New = vel1 - dot1 * dir;
		glm::vec3 vel2New = vel2 - dot2 * dir2;
		
		if (dot1 < 0) {
			master->setVelocity(vel1New);
		}
		if (dot2 < 0) {
			other->setVelocity(vel2New);
		}

	}


}


void Spring::init(float k, float d,  PointMass * particle1, PointMass * particle2,float maxRate)
{

	this->pointMasses = new PointMass*[2];
	this->pointMasses[0] = particle1;
	this->pointMasses[1] = particle2;

	this->springConst = k;
	this->dampingConst = d;

	this->masterPoint = 0;
	this->maxDeformRate = maxRate;
	

	this->restLength = glm::length(particle1->getPosition() - particle2->getPosition());
}
