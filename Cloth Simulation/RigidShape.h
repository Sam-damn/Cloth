#pragma once

#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"
#include "Triangle.h"
#include "AABB.h"

class RigidShape :public KeyboardControl
{
public:
	RigidShape(std::string path);
	
	 void draw(ShaderProgram program);
	 glm::mat4 getTransform();
	 void manageKeyboardInput(GLFWwindow *window);
	 
	 std::vector<Triangle*> triangles;
	 AABB* box;

	 //just for testing against a fake sphere
	 glm::vec3 center;
	 float radius;
	 bool intersectPoint(glm::vec3 point, glm::vec3 &dir);



	 //just for drawing and testing triangle
	 IndexedMesh *lightMesh;
	 Triangle *triangle;


private:
	Model * model;
	
	glm::vec3 pos;
	float scalefactor;
	glm::vec3 translation;
	

};

