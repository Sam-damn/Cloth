#define _USE_MATH_DEFINES
#include "DeformableBody.h"
#include <glfw/glfw3.h>
#include <cmath>

void DeformableBody::applyGravity(glm::vec3 gravityAcceleration)
{
	for (PointMass* point : points) {
		point->addForce(point->getMass() * gravityAcceleration);
	}
}

void DeformableBody::applyDrag(float damp)
{
	for (PointMass* point : points) {
		point->addForce(-point->getVelocity() * damp);
	}
}

void DeformableBody::applyWind()
{
	SimplexNoise* noise = new SimplexNoise();
	float time = glfwGetTime();
	timer += 0.004f;

	float length = 5.0f;
	for (PointMass* point : points) {

		glm::vec3 pos = point->getPosition();

		float value = noise->noise(pos.x, pos.z, time);
		float value2 = noise->noise(pos.x + 1000, pos.z + 1000, time);

		float val = (value + 1) / 2;
		float val2 = (value2 + 1) / 2;


		float xValue = cos(val * M_PI * 2);
		float yValue = sin(val * M_PI * 2);

		float lengthvalue = length * val2;
		float val3 = sin(val * M_PI * 2);
		glm::vec3 force1 = val3 * lengthvalue * glm::vec3(val, 0.0f, val2);

		//glm::vec3 force = val3 * glm::vec3(6.0f, 0.0f, 2.0f);
		point->addForce(force1);


	}

}

void DeformableBody::collide(RigidShape* shape)
{
	glm::vec3 Q;
	for (PointMass* point : points) {

		glm::vec3 p0 = point->prevPostion;
		glm::vec3 p1 = point->getPosition();
		glm::vec3 vel = point->getVelocity();


		glm::vec3 dir = glm::vec3(0.0f, 0.0f, 0.0f);

		/*for (Triangle* triangle : shape->triangles) {


			if (triangle->intersect4(p0, p1, Q)) {

				//std::cout << "heyy";
				point->position = Q;
				glm::vec3 Vn = glm::dot(triangle->normal, vel) * triangle->normal;
				glm::vec3 Vt = vel - Vn;
				point->setVelocity(Vt - Vn);

			}


		}*/

		//for intersecting with fake sphere

		if (shape->intersectPoint(p1, dir)) {
			std::cout << "intersection";
			point->position = shape->center + shape->radius * dir;
			glm::vec3 Vn = glm::dot(dir, vel) * dir;
			glm::vec3 Vt = vel - Vn;
			Vt = glm::normalize(Vt);
			point->setVelocity(Vt - Vn);


		}


	}


}
