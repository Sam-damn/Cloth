#include "PointLight.h"


PointLight::PointLight()
{
}

PointLight::PointLight(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 position, Attenuation attenuation) :
	LightSource(ambientColor, diffuseColor, specularColor)
{
	this->position = position;
	this->attenuation = attenuation;
}
