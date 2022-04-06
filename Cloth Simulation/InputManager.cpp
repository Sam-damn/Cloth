#include <iostream>

#include "InputManager.h"


static void mouse_callback(GLFWwindow* window, double xPosition, double yPosition);
static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

MouseControl * InputManager::activeMouseInputObject;
ScrollControl * InputManager::activeScrollInputObject;

double InputManager::mouseLastXPos;
double InputManager::mouseLastYPos;
float InputManager::mouseSensitivity = 0.05f;


InputManager::InputManager(GLFWwindow * window)
{
	this->window = window;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

void InputManager::registerKeyboardInput(KeyboardControl * inputObject)
{
	keyboardInputObjects.push_back(inputObject);
}

//sets the active mouse controlled object (for now only one object can be mouse controlled but this can change later
void InputManager::registerMouseInput(MouseControl * inputObject)
{
	activeMouseInputObject = inputObject;
}

void InputManager::registerScrollInput(ScrollControl * inputObject)
{
	activeScrollInputObject = inputObject;
}

void InputManager::handleKeyboardInput()
{
	for (KeyboardControl *in : keyboardInputObjects) {
		in->manageKeyboardInput(window);
	}
}

//sends the change in x and y positions
void InputManager::handleMouseInput(double xPosition, double yPosition)
{
	static bool firstMouseUse = true;
	if (firstMouseUse) {
		mouseLastXPos = xPosition;
		mouseLastYPos = yPosition;
		firstMouseUse = false;
	}

	double xOffset = xPosition - mouseLastXPos;
	double yOffset = mouseLastYPos - yPosition;
	mouseLastXPos = xPosition;
	mouseLastYPos = yPosition;

	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	//Send the offsets to the mouse controlled object (camera)
	activeMouseInputObject->manageMouseInput(xOffset, yOffset);
}

void InputManager::handleScrollInput(double xOffset, double yOffset) 
{
	activeScrollInputObject->manageScrollInput(xOffset, yOffset);
}


void mouse_callback(GLFWwindow * window, double xPosition, double yPosition)
{
	InputManager::handleMouseInput(xPosition, yPosition);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) 
{
	InputManager::handleScrollInput(xOffset, yOffset);
}
