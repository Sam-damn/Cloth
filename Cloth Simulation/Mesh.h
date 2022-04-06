#pragma once

#include <vector>

#include <glad/glad.h>

#include "Vertex.h"
#include "Texture.h"
#include "ShaderProgram.h"


class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures);
	
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;

	virtual void draw(ShaderProgram program);
	
protected:
	GLuint vao;
	GLuint vbo;

	virtual void setupMesh();
	void activateTextures(ShaderProgram program);
};
