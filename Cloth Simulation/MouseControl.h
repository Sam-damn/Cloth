#pragma once

class MouseControl
{
public:
	virtual void manageMouseInput(double xOffset, double yOffset) = 0;
};
