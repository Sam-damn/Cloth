#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}


Texture ResourceManager::loadTexture(std::string texturePath)
{
	return loadTexture(texturePath, TextureType::texture_diffuse);
}

Texture ResourceManager::loadTexture(std::string texturePath, TextureType textureType)
{
	//if the texture has been loaded already then return the existing copy
	if (textureCache.count(texturePath)) {
		return textureCache.at(texturePath);
	}

	//if it hasn't been loaded then load it and add it to the cache
	Texture tex(texturePath, textureType);
	textureCache.insert(std::pair<std::string, Texture>(texturePath, tex));
	return tex;
}
