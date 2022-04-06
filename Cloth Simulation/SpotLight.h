#pragma once

#include "LightSource.h"
#include "KeyboardControl.h"


class SpotLight : public LightSource, public KeyboardControl
{
public:
	SpotLight();

	SpotLight(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor,
		glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, Attenuation attenuation);

	void manageKeyboardInput(GLFWwindow* window);

	glm::vec3 position;
	glm::vec3 direction;

	float cutOff;
	float outerCutOff;

	Attenuation attenuation;

private:
	bool buttonDown;
	float tempCutOff;
	float tempOuterCutOff;

	void toggleLight();
};
