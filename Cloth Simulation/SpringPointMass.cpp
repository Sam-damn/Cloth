#include "SpringPointMass.h"



SpringPointMass::SpringPointMass() : maxVisitLimit(1) ,PointMass(),visit(0)
{

}

SpringPointList SpringPointMass::getVerticalSprings()
{
	return verticalSprings;
}

SpringPointList SpringPointMass::getHorizentalSprings()
{
	return horizontalSprings;
}

SpringPointList SpringPointMass::getShearSprings()
{
	return shearSprings;
}

void SpringPointMass::addVerticalSpring(Spring* spring, SpringPointMass* pointMass)
{
	verticalSprings.push_back(make_pair(spring, pointMass));
}

void SpringPointMass::addHorizentalSpring(Spring* spring, SpringPointMass* pointMass)
{
	horizontalSprings.push_back(make_pair(spring, pointMass));
}


void SpringPointMass::addShearSpring(Spring* spring, SpringPointMass* pointMass)
{
	shearSprings.push_back(make_pair(spring, pointMass));
}

void SpringPointMass::increment()
{
	visit++;
}

bool SpringPointMass::canExpand()
{
	return visit < maxVisitLimit;
	
}

