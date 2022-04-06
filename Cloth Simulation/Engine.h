#pragma once

#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.h"
#include "Window.h"
#include "Texture.h"
#include "Camera.h"
#include "InputManager.h"
#include "LightSource.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "FpsCounter.h"
#include "Mesh.h"
#include "Model.h"
#include "ResourceManager.h"
#include "Render.h"
#include "PhysicsEngine.h"
#include "SkyBox.h"
#include "RigidShape.h"


const int WIDTH = 1366;
const int HEIGHT = 768;

const char* const vertexShaderPath = "shaders/mainShader.vert";
const char* const geometryShaderPath = "shaders/mainShader.geom";
const char* const fragmentShaderPath = "shaders/mainShader.frag";

const char lampVertShaderPath[] = "shaders/LampShader.vert";
const char lampFragShaderPath[] = "shaders/LampShader.frag";

const std::string skyboxVertShaderPath = "shaders/skyboxShader.vert";
const std::string skyboxFragShaderPath = "shaders/skyboxShader.frag";

const std::string diffPath = "resources/clothTile.jpg";
const std::string specPath = "resources/clothSpecular.png";

const glm::vec3 cubePositions[] = {
	glm::vec3( 0.0f,  0.0f,  0.0f),
	glm::vec3( 2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3( 2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3( 1.3f, -2.0f, -2.5f),
	glm::vec3( 1.5f,  2.0f, -2.5f),
	glm::vec3( 1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

const std::vector<std::string> skyboxFaces = {
	
	"resources/skybox/space_right.png",
	"resources/skybox/space_left.png",
	"resources/skybox/space_up.png",
	"resources/skybox/space_down.png",
	"resources/skybox/space_back.png",
	"resources/skybox/space_front.png"
};

struct Material {
	Texture *diffuseMap;
	Texture *specularMap;
	float shininess;

	Material(std::string diffMapPath, std::string specMapPath, float shininess) {
		this->diffuseMap = new Texture(diffMapPath);
		this->diffuseMap->type = TextureType::texture_diffuse;

		this->specularMap = new Texture(specMapPath);
		this->specularMap->type = TextureType::texture_specular;

		this->shininess = shininess;
	}

	~Material() {
		delete diffuseMap;
		delete specularMap;
	}
};

class Engine : public Render
{
public:
	Engine();

	void start();

	void initCloth(float * vertexdata,int size) override;
	void initClothIndexed(float *vertexData, int vertexDataSize, int *indexData, int indexDataSize) override;
	void updateCloth(float * vertexdata,int size) override;

private:
	float* vertices;
	int size;
	int* indices;
	int indicesSize;
	uint32_t vbo;
	uint32_t vao;
	uint32_t ebo;
	int attribCount;

	FpsCounter fpsCounter;

	ShaderProgram program;
	ShaderProgram lampProgram;
	ShaderProgram skyboxProgram;
	Window *window;
	Camera *camera;
	InputManager *inputManager;
	DirectionalLight *sunlight;
	PointLight *lamps[4];
	SpotLight *flashlight;
	Material *material;
	SkyBox *skybox;
	RigidShape *sphere;

	PhysicsEngine* physics;

	void init();
	void mainLoop();
	void cleanup();
	
	void initWindow();
	void initShaderProgram();
	void initLights();
	void createVertexObjects();
	void enableAttributes();

	void renderFrame();
};
