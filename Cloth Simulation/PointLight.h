#pragma once

#include "LightSource.h"


class PointLight : public LightSource
{
public:
	PointLight();

	PointLight(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 position, Attenuation attenuation);

	glm::vec3 position;

	Attenuation attenuation;
};
