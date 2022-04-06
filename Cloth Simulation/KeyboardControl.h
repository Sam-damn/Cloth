#pragma once

#include <glfw/glfw3.h>

class KeyboardControl
{
public:
	virtual void manageKeyboardInput(GLFWwindow *window) = 0;
};
