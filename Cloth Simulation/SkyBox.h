#pragma once

#include <vector>
#include <string>

#include <glad/glad.h>

#include "IndexedMesh.h"
#include "ShaderProgram.h"


class SkyBox
{
public:
	SkyBox(std::vector<std::string> facePaths);
	void initDefaultMesh();

	void draw(ShaderProgram program);

private:
	GLuint textureId;

	IndexedMesh *skyBoxMesh;
};
