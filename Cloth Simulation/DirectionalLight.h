#pragma once

#include "LightSource.h"


class DirectionalLight : public LightSource
{
public:
	DirectionalLight();

	DirectionalLight(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 direction);

	glm::vec3 direction;
};
