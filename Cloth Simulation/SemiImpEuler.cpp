#include "SemiImpEuler.h"


SemiImpEuler::SemiImpEuler(std::vector<PointMass*> points)
{
	this->points = points;
}


void SemiImpEuler::solve(float fixedDeltaTime)
{
	for (PointMass* point : points) {


		
			//advance the particles position and velocity in time 
			glm::vec3 velNew = point->getVelocity() + point->getAcceleration() * fixedDeltaTime;
			glm::vec3 posNew = point->getPosition() + velNew * fixedDeltaTime;

			point->setPosition(posNew);


			point->setVelocity(velNew);

			//clear the accumulators
			point->clearAccum();
		
		
	}

}
