#pragma once

#include <vector>

#include "PointMass.h"
#include "ForceGenerator.h"
#include "Integrator.h"
#include "Face.h"
#include "Gravity.h"
#include "Drag.h"
#include "Wind.h"
#include "SimplexNoise.h"
#include "RigidShape.h"


class DeformableBody : public Gravity, public Drag,public Wind
{
public:
	virtual void update(float deltaTime) = 0;
	
	void applyGravity(glm::vec3 gravity);
	void applyDrag(float damp);
	void applyWind();
	void collide(RigidShape* shape);

	float timer = 0;
	AABB* box;
protected:
	std::vector<PointMass*> points;
	std::vector<Face*> faces;
	
	Integrator* solver;
};
