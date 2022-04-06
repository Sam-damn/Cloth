#pragma once

#include "Mesh.h"


class IndexedMesh : public Mesh
{
public:
	IndexedMesh();
	IndexedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	std::vector<unsigned int> indices;

	void draw(ShaderProgram program) override;

protected:
	GLuint ebo;

	void setupMesh() override;
};
