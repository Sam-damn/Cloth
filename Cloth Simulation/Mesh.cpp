#include "Mesh.h"


Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->textures = textures;

	setupMesh();
}


void Mesh::setupMesh()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::activateTextures(ShaderProgram program)
{
	unsigned int diffuseNum = 1;
	unsigned int specularNum = 1;

	//activate texture units based on number of textures available
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name;
		switch (textures[i].type) {
		case TextureType::texture_diffuse:
			number = std::to_string(diffuseNum++);
			name = "diffuse";
			break;
		case TextureType::texture_specular:
			number = std::to_string(specularNum++);
			name = "specular";
			break;
		}
		if (number == "1") {
			program.setUniformInt("material." + name, i);
		}
		else {
			program.setUniformInt("material." + name + number, i);
		}
		textures[i].useTexture();
	}
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::draw(ShaderProgram program)
{
	activateTextures(program);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
	glBindVertexArray(0);	
}
