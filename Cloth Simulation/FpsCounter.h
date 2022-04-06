#pragma once

#include <glfw/glfw3.h>


class FpsCounter
{
public:
	FpsCounter();
	~FpsCounter();

	float fps;

	void update();

	void disablePrinting();
	void enablePrinting();

private:
	bool printFps;
	unsigned int fpsSamples;

	float *recentFrameTimes;
	float prevTime;

	unsigned int currentFrame;
	float timeAccumulator;
};
