#pragma once

#include <unordered_map>
#include <string>

#include "Texture.h"


/*TODO : 
	-make so textures with no more refernces are deleted
	-manage models
	-possibly manage meshes (if possible)
*/
class ResourceManager
{
public:
	ResourceManager();

	//use this function to load textures rather than directly invoking the texture constructor
	Texture loadTexture(std::string texturePath);
	Texture loadTexture(std::string texturePath, TextureType textureType);

private:
	std::unordered_map<std::string, Texture> textureCache;

};
