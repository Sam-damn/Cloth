#include "DirectionalLight.h"


DirectionalLight::DirectionalLight()
{
}

DirectionalLight::DirectionalLight(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 direction) :
	LightSource(ambientColor, diffuseColor, specularColor)
{
	this->direction = direction;
}
