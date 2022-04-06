#pragma once

#include <stdexcept>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "KeyboardControl.h"


class Window : public KeyboardControl
{
public:
	void init(int width, int height, const char* name);
	void swapBuffers();
	void setClearColor(float r, float g, float b, float a);
	void close();

	void manageKeyboardInput(GLFWwindow *window);

	GLFWwindow* getWindow() { return window; }

private:
	GLFWwindow *window;

};
