#include <sstream>
#include <iostream>

#include "Model.h"


extern ResourceManager resourceManager;

Model::Model(std::string path)
{
	loadModel(path);
}


void Model::draw(ShaderProgram program)
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].draw(program);
	}
}

std::vector<IndexedMesh> Model::getMesh()
{
	return meshes;
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::stringstream errorMessage;
		errorMessage << "Failed to load model. " << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		throw std::runtime_error(errorMessage.str());
	}
	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	//process the nodes meshes
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	//process the children nodes meshes
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

IndexedMesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	//process vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		glm::vec3 posVec;
		posVec.x = mesh->mVertices[i].x;
		posVec.y = mesh->mVertices[i].y;
		posVec.z = mesh->mVertices[i].z;

		glm::vec3 normVec;
		normVec.x = mesh->mNormals[i].x;
		normVec.y = mesh->mNormals[i].y;
		normVec.z = mesh->mNormals[i].z;

		glm::vec2 texVec;
		if (mesh->mTextureCoords[0]) {
			texVec.x = mesh->mTextureCoords[0][i].x;
			texVec.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			texVec.x = 0.0f;
			texVec.y = 0.0f;
		}

		vertex.position = posVec;
		vertex.normal = normVec;
		vertex.texCoords = texVec;

		vertices.push_back(vertex);
	}

	//process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	//process materials
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::texture_diffuse);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::texture_specular);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return IndexedMesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial * material, aiTextureType type, TextureType typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i, &str);
		Texture texture = resourceManager.loadTexture(directory + "/" + str.C_Str(), typeName);
		textures.push_back(texture);
	}
	return textures;
}
