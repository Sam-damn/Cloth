
#include <stb/stb_image.h>

#include "SkyBox.h"


SkyBox::SkyBox(std::vector<std::string> facePaths)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	stbi_set_flip_vertically_on_load(false); //cubemap texture coordinates are top left to bottom right

	int width, height, numChannels;

	for (unsigned int i = 0; i < facePaths.size(); i++) {

		unsigned char *data = stbi_load(facePaths[i].c_str(), &width, &height, &numChannels, 0);

		GLenum format;

		if (numChannels == 1) {
			format = GL_RED;
		}
		else if (numChannels == 3) {
			format = GL_RGB;
		}
		else if (numChannels == 4) {
			format = GL_RGBA;
		}
		else {
			throw std::runtime_error("Unknown color format for texture " + facePaths[i] + "\n");
		}

		if (data != nullptr) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}

		else {
			throw std::runtime_error("Failed to load texture " + facePaths[i] + "\n");
			stbi_image_free(data);
		}

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//replaced with enabling seamless cubemap
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	this->textureId = textureId;
}

void SkyBox::initDefaultMesh()
{
	float vertices[] = {
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
	};

	uint32_t indices[] = {
		//front
		0, 1, 2,
		2, 3, 0,

		//right
		1, 5, 6,
		6, 2, 1,

		//bottom
		3, 2, 6,
		6, 7, 3,

		//left
		4, 0, 3,
		3, 7, 4,

		//top
		4, 5, 1,
		1, 0, 4,

		//back
		4, 6, 5,
		6, 4, 7,
	};

	std::vector<Texture> textureVec; //empty
	std::vector<Vertex> vertexVec;
	std::vector<unsigned int> indexVec;

	for (int n = 0; n < sizeof(vertices) / sizeof(vertices[0]); n += 3) {
		vertexVec.push_back(Vertex(
			glm::vec3(vertices[n], vertices[n + 1], vertices[n + 2]),
			glm::vec3(0.0f),
			glm::vec2(0.0f)
		));
	}

	for (int i = 0; i < sizeof(indices) / sizeof(indices[0]); i++) {
		indexVec.push_back(indices[i]);
	}

	skyBoxMesh = new IndexedMesh(vertexVec, indexVec, textureVec);
}

void SkyBox::draw(ShaderProgram program)
{
	if (skyBoxMesh != nullptr) {
		//disable writing to the depth buffer
		glDepthMask(GL_FALSE); //unnecessary when drawing the skybox last (but just in case we wanna draw something after it)
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
		skyBoxMesh->draw(program);
		glDepthMask(GL_TRUE);
	}
	else {
		std::cout << "SkyBox mesh uninitialized" << std::endl;
	}
}
