#pragma once

#include <glm/glm.hpp>

#include "KeyboardControl.h"
#include "MouseControl.h"
#include "ScrollControl.h"


class Camera : public KeyboardControl, public MouseControl, public ScrollControl
{
public:
	Camera();
	Camera(glm::vec3, glm::vec3, glm::vec3);

	glm::mat4 view();
	glm::mat4 project();

	void manageKeyboardInput(GLFWwindow *window);
	void manageMouseInput(double xOffset, double yOffset);
	void manageScrollInput(double xOffset, double yOffset);

	glm::vec3 getCameraPosition() { return cameraPosition; }
	glm::vec3 getCameraFront() { return cameraFront; }

private:
	void construct(glm::vec3, glm::vec3, glm::vec3);
	void updateView();
	void updateProjection();
	void recalculateCameraVectors();

	float cameraSpeed;

	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	float pitch;
	float yaw;

	float fov;
};
