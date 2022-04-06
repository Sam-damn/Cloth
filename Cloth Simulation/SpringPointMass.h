#pragma once

#include "PointMass.h"
#include "Spring.h"

#include <utility>
#include <vector>

using namespace std;
class SpringPointMass;

typedef std::vector< std::pair<Spring*,SpringPointMass*> > SpringPointList ;

class SpringPointMass : public PointMass
{
public:
	SpringPointMass();

	SpringPointList getVerticalSprings();
	SpringPointList getHorizentalSprings();
	SpringPointList getShearSprings();

	void addVerticalSpring(Spring* spring, SpringPointMass* pointMass);
	void addHorizentalSpring(Spring* spring, SpringPointMass* pointMass);
	void addShearSpring(Spring* spring, SpringPointMass* pointMass);

	void increment();
	bool canExpand();


private:
	SpringPointList verticalSprings;
	SpringPointList horizontalSprings;
	SpringPointList shearSprings;
	int maxVisitLimit;
	int visit;
	

};

