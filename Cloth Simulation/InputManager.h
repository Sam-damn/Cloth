#pragma once

#include <vector>

#include <glfw/glfw3.h>

#include "KeyboardControl.h"
#include "MouseControl.h"
#include "ScrollControl.h"


class InputManager
{
public:
	InputManager(GLFWwindow *window);

	void registerKeyboardInput(KeyboardControl * inputObject);
	static void registerMouseInput(MouseControl * inputObject);
	static void registerScrollInput(ScrollControl * inputObject);


	void handleKeyboardInput();
	static void handleMouseInput(double xPosition, double yPosition);
	static void handleScrollInput(double xOffset, double yOffset);

private:
	GLFWwindow *window;

	std::vector<KeyboardControl *> keyboardInputObjects;
	static MouseControl * activeMouseInputObject;
	static ScrollControl * activeScrollInputObject;

	static double mouseLastXPos;
	static double mouseLastYPos;

	static float mouseSensitivity;
};
