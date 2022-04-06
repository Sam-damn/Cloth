#pragma once

#include <string>

#include <glad/glad.h>


enum class TextureType { texture_diffuse, texture_specular };

class Texture
{
public:
	Texture(std::string texturePath);
	Texture(std::string texturePath, TextureType type);
	Texture(std::string texturePath, int minFilter, int magFilter);
	Texture(std::string texturePath, TextureType type, int minFilter, int magFilter);

	void useTexture();

	static void setDefaultMinFilter(int filter);
	static void setDefaultMagFilter(int filter);

	uint32_t texture;
	TextureType type;
	std::string path;

private:
	void construct(std::string texturePath, TextureType type, int minFilter, int magFilter);

	static int defaultMinFilter;
	static int defaultMagFilter;
};
