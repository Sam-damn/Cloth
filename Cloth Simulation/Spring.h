#pragma once

#include "PointMass.h"

  

class Spring
{
public:
	Spring();
	Spring(float, float, PointMass *, PointMass *,float);
	
	float getRestLength();
	float getCurrentLength();
	
	void setMasterPoint(PointMass* master);

	void applyForce();
	void adjust();
	void adjust2();
	bool adjust3(float &error);
	void adjust_vel();
	
private:

	float springConst;
	float dampingConst;
	float restLength;
	PointMass** pointMasses;

	int masterPoint;
	float maxDeformRate;

	void init(float, float,  PointMass*, PointMass*,float);
};
