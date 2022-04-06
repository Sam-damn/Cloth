#pragma once

class ScrollControl
{
public:
	virtual void manageScrollInput(double xOffset, double yOffset) = 0;
};
