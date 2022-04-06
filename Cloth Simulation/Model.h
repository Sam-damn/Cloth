#pragma once

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "IndexedMesh.h"
#include "ShaderProgram.h"
#include "ResourceManager.h"


class Model
{
public:
	Model(std::string path);

	void draw(ShaderProgram program);
	std::vector<IndexedMesh> getMesh();

private:
	std::vector<IndexedMesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	IndexedMesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, TextureType typeName);
};
