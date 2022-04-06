#include "RigidShape.h"


extern float deltaTime;

RigidShape::RigidShape(std::string path) :scalefactor(0.3f)
{
	model = new Model(path);

	std::vector<IndexedMesh> meshes = model->getMesh();

	for (IndexedMesh mesh : meshes) {

		for (int i = 0; i < mesh.indices.size(); i += 3)
		{
			int index1 = mesh.indices[i];
			int index2 = mesh.indices[i + 1];
			int index3 = mesh.indices[i + 2];


			Triangle* triangle = new Triangle(mesh.vertices[index1].position, mesh.vertices[index2].position, mesh.vertices[index3].position);

			this->triangles.push_back(triangle);


		}

	}



	//center = glm::vec3(0.0f, -0.1f, 0.0f);
	//radius = 0.3f;

	/*float vertices[] = {
		-0.5f,  -0.25f,  -0.25f,
		 0.5f,  -0.25f,  -0.25f,
		 0.0f,	0.25f,  -0.75f,

	};*/


	/*float vertices[] = {
		-0.5f,  0.25f,  -0.25f,
		 0.5f,  0.25f,  -0.25f,
		 0.0f,	-0.25f,  -0.75f,

	};*/
	/*float vertices[] = {
		-0.5f,  -0.1f,  -0.25f,
		 0.5f,  -0.1f,  -0.25f,
		 0.0f,	0.5f,  -0.75f,

	};

	uint32_t indices[] = {

		0, 1, 2

	};*/


	//float vertices[] = {
	//	-0.25f,  0.25f,  0.25f,
	//	 0.25f,  0.25f,  0.25f,
	//	 0.25f, -0.25f,  0.25f,
	//	-0.25f, -0.25f,  0.25f,
	//	-0.25f,  0.25f, -0.25f,
	//	 0.25f,  0.25f, -0.25f,
	//	 0.25f, -0.25f, -0.25f,
	//	-0.25f, -0.25f, -0.25f,
	//};


	//uint32_t indices[] = {
	//	//front
	//	0, 2, 1,
	//	2, 0, 3,

	//	//right
	//	1, 6, 5,
	//	6, 1, 2,

	//	//bottom
	//	3, 6, 2,
	//	6, 3, 7,

	//	//left
	//	4, 3, 0,
	//	3, 4, 7,

	//	//top
	//	4, 1, 5,
	//	1, 4, 0,

	//	//back
	//	4, 5, 6,
	//	6, 7, 4,
	//};
	//std::vector<Texture> textureVec; //empty
	//std::vector<Vertex> vertexVec;
	//std::vector<unsigned int> indexVec;

	//for (int n = 0; n < sizeof(vertices) / sizeof(vertices[0]); n += 3) {
	//	vertexVec.push_back(Vertex(
	//		glm::vec3(vertices[n], vertices[n + 1], vertices[n + 2]),
	//		glm::vec3(0.0f),
	//		glm::vec2(0.0f)
	//	));
	//}

	//for (int i = 0; i < sizeof(indices) / sizeof(indices[0]); i++) {
	//	indexVec.push_back(indices[i]);
	//}

	//lightMesh = new IndexedMesh(vertexVec, indexVec, textureVec);

	//

	//for (int i = 0; i < 36; i += 3) {

	//	int index1 = indices[i];
	//	int index2 = indices[i+1];
	//	int index3 = indices[i+2];

	//	glm::vec3 point1 =  glm::vec3(vertices[3 * index1], vertices[3 * index1 + 1], vertices[3 * index1 + 2]);
	//	glm::vec3 point2 = glm::vec3(vertices[3 * index2], vertices[3 * index2 + 1], vertices[3 * index2 + 2]);
	//	glm::vec3 point3 = glm::vec3(vertices[3 * index3], vertices[3 * index3 + 1], vertices[3 * index3 + 2]);


	//	this->triangles.push_back(new Triangle(point1, point2, point3));

	//}

	std::vector<glm::vec3> points;


	glm::mat4 mat = glm::mat4(1.0f);
	mat = glm::scale(mat, glm::vec3(scalefactor));

	for (Triangle* tri : triangles) {

		tri->scale(mat);
		points.push_back(tri->point1);
		points.push_back(tri->point2);
		points.push_back(tri->point3);

	}

	box = new AABB(points);

	/*glm::vec3 point1 = glm::vec3(vertices[0], vertices[1], vertices[2]);
	glm::vec3 point2 = glm::vec3(vertices[3], vertices[4], vertices[5]);
	glm::vec3 point3 = glm::vec3(vertices[6], vertices[7], vertices[8]);*/


	/*triangle = new Triangle(point1, point2, point3);
	triangles.push_back(triangle);*/


	pos = glm::vec3(0.0f, 0.0f, 8.0f);
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	center = glm::vec3(0.0f, 0.0f, -2.0f);

}

void RigidShape::draw(ShaderProgram program)
{
	model->draw(program);

	/*if (lightMesh != nullptr) {
		lightMesh->draw(program);
	}
	else {
		std::cout << "Light mesh uninitialized" << std::endl;
	}*/

}

glm::mat4 RigidShape::getTransform()
{

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(scalefactor));
	model = glm::translate(model, center);
	return model;
}

void RigidShape::manageKeyboardInput(GLFWwindow* window)
{
	float speed = 2.0f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		pos += speed * glm::vec3(0.0f, 0.0f, 1.0f);
		pos = speed * glm::vec3(0.0f, 0.0f, 1.0f);
		translation = speed * glm::vec3(0.0f, 0.0f, 1.0f);
		center += speed * glm::vec3(0.0f, 0.0f, 1.0f);
	}


	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		pos -= speed * glm::vec3(0.0f, 0.0f, 1.0f);
		pos = -speed * glm::vec3(0.0f, 0.0f, 1.0f);
		translation = -speed * glm::vec3(0.0f, 0.0f, 1.0f);
		center -= speed * glm::vec3(0.0f, 0.0f, 1.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		pos -= speed * glm::vec3(1.0f, 0.0f, 0.0f);
		translation = -speed * glm::vec3(1.0f, 0.0f, 0.0f);
		center -= speed * glm::vec3(1.0f, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {

		pos += speed * glm::vec3(1.0f, 0.0f, 0.0f);
		translation = speed * glm::vec3(1.0f, 0.0f, 0.0f);
		center += speed * glm::vec3(1.0f, 0.0f, 0.0f);
	}


	/*for (Triangle* tri : triangles) {

		tri->update(this->getTransform());
	}*/


	/*this->translation = glm::vec3(0.0f, 0.0f, 0.0f);*/

}

bool RigidShape::intersectPoint(glm::vec3 point, glm::vec3& dir)
{
	glm::vec3 diff = point - this->center;
	dir = glm::normalize(diff);
	if (glm::length(diff) < this->radius) {

		return true;
	}
	return false;

}



