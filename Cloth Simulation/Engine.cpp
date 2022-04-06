#include <cmath>
#include <sstream>

#include "Engine.h"


extern float deltaTime;
ResourceManager resourceManager;
InputManager* activeInputManager;

Engine::Engine() :
	attribCount(0)
{
}

void Engine::initCloth(float* vertexdata, int size)
{
	this->vertices = vertexdata;
	this->size = size;
}

void Engine::initClothIndexed(float* vertexData, int vertexDataSize, int* indexData, int indexDataSize)
{
	vertices = vertexData;
	size = vertexDataSize;
	indices = indexData;
	indicesSize = indexDataSize;
}

void Engine::updateCloth(float* vertexdata, int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(float), vertexdata);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::init()
{
	window = new Window;

	initWindow();
	initShaderProgram();

	inputManager = new InputManager(window->getWindow());
	activeInputManager = inputManager;
	activeInputManager->registerKeyboardInput(window);

	camera = new Camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	activeInputManager->registerKeyboardInput(camera);
	activeInputManager->registerMouseInput(camera);
	activeInputManager->registerScrollInput(camera);


	this->physics = new PhysicsEngine(this);

	createVertexObjects();

	material = new Material(diffPath, specPath, 11.0f);

	initLights();

	skybox = new SkyBox(skyboxFaces);
	skybox->initDefaultMesh();

	sphere = new RigidShape("resources/sphere.fbx");
	activeInputManager->registerKeyboardInput(sphere);
	this->physics->addShape(sphere);


	//depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//multisample antialiasing
	glEnable(GL_MULTISAMPLE);

	//face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); //default is back
	glFrontFace(GL_CCW); //default is ccw

	//seamless cubemap
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	//glEnable(glPolygonMode);
}

void Engine::mainLoop()
{
	while (!glfwWindowShouldClose(window->getWindow())) {
		fpsCounter.update();

		activeInputManager->handleKeyboardInput();

		this->physics->updatePhyics(deltaTime);

		//(~ 1.4ms)
		renderFrame();

		glfwPollEvents();
	}
}

void Engine::cleanup()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	delete material;

	window->close();
}

void Engine::initWindow()
{
	window->init(WIDTH, HEIGHT, "Engine");
	window->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void Engine::initShaderProgram()
{
	program.compileShaders(vertexShaderPath, geometryShaderPath, fragmentShaderPath);

	lampProgram.compileShaders(lampVertShaderPath, lampFragShaderPath);

	skyboxProgram.compileShaders(skyboxVertShaderPath.c_str(), skyboxFragShaderPath.c_str());
}

void Engine::initLights()
{
	Attenuation attenuation;
	attenuation.constant = 1.0f;
	attenuation.linear = 0.09f;
	attenuation.quadratic = 0.032f;

	Attenuation midAttenuation;
	midAttenuation.constant = 1.0f;
	midAttenuation.linear = 0.7f;
	midAttenuation.quadratic = 0.017f;

	Attenuation flashAttenuation;
	flashAttenuation.constant = 1.0f;
	flashAttenuation.linear = 0.045f;
	flashAttenuation.quadratic = 0.0075f;

	glm::vec3 yellow = glm::vec3(1.0f, 1.0f, 0.0f);
	glm::vec3 white = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 blue = glm::vec3(0.0f, 0.0f, 1.0f);

	sunlight = new DirectionalLight(0.05f * yellow, 0.35f * yellow + 1.0f * white, 0.5f * white, glm::vec3(0.0f, -0.34f, -0.5f));

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	glm::vec3 pointLightColors[] = {
		glm::vec3(0.1f,  0.22f, 0.9f),
		glm::vec3(0.72f, 0.4f, 0.83f),
		glm::vec3(0.4f,  0.94f, 0.52f),
		glm::vec3(0.7f,  0.2f,  0.1f)
	};

	for (int i = 0; i < 4; i++) {
		lamps[i] = new PointLight(0.1f * pointLightColors[i], 1.5f * pointLightColors[i], white,
			pointLightPositions[i], flashAttenuation);
		lamps[i]->initDefaultMesh();
	}

	flashlight = new SpotLight(0.1f * white, white, white, camera->getCameraPosition(), camera->getCameraFront(),
		cos(glm::radians(12.5f)), cos(glm::radians(17.5f)), flashAttenuation);

	activeInputManager->registerKeyboardInput(flashlight);
}

void Engine::createVertexObjects()
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ebo);

	//bind the vao
	glBindVertexArray(vao);

	//bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, this->size * sizeof(float), vertices, GL_DYNAMIC_DRAW);

	////bind the ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesSize * sizeof(int), indices, GL_STATIC_DRAW);

	//Specify attributes of vertices in the buffer
	glVertexAttribPointer(attribCount++, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(attribCount++, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(attribCount++, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	enableAttributes();

	//unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Don't unbind the ebo
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//unbind the vao
	glBindVertexArray(0);
}

void Engine::enableAttributes()
{
	for (int i = 0; i < attribCount; i++) {
		glEnableVertexAttribArray(i);
	}
}

void Engine::renderFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = camera->view();
	glm::mat4 projection = camera->project();
	flashlight->position = camera->getCameraPosition();
	flashlight->direction = camera->getCameraFront();

	program.useProgram();

	program.setUniformMat4("view", view);
	program.setUniformMat4("projection", projection);

	//material
	program.setUniformInt("material.diffuse", 0);
	program.setUniformInt("material.specular", 1);
	program.setUniformFloat("material.shininess", material->shininess);

	//directional light
	program.setUniformDirLight("dirLights[0]", *sunlight);

	//point light
	for (int i = 0; i < 4; i++) {
		std::ostringstream out;
		out << "pointLights[" << i << "]";
		program.setUniformPointLight(out.str(), *lamps[i]);
	}

	//spotlight
	program.setUniformSpotLight("spotLights[0]", *flashlight);

	program.setUniformVec3("viewPosition", &(camera->getCameraPosition())[0]);

	//activate the texture units
	glActiveTexture(GL_TEXTURE0);
	material->diffuseMap->useTexture();

	glActiveTexture(GL_TEXTURE1);
	material->specularMap->useTexture();

	glBindVertexArray(vao);

	//draw 10 cloths

	for (unsigned int i = 0; i < 1; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		program.setUniformMat4("model", model);

		//glDrawArrays(GL_TRIANGLES, 0, this->size / 8);
		glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
	}


	program.setUniformMat4("model", sphere->getTransform());
	sphere->draw(program);

	lampProgram.useProgram();

	//draw the lamp cubes
	for (int i = 0; i < 4; i++) {
		glm::mat4 lampModel = glm::mat4(1.0f);
		lampModel = glm::translate(lampModel, lamps[i]->position);
		lampModel = glm::scale(lampModel, glm::vec3(0.2f));

		lampProgram.setUniformMat4("model", &lampModel[0][0]);
		lampProgram.setUniformMat4("view", &view[0][0]);
		lampProgram.setUniformMat4("projection", &projection[0][0]);

		lampProgram.setUniformVec3("lightColor", lamps[i]->diffuseColor);

		lamps[i]->draw(lampProgram);
	}

	skyboxProgram.useProgram();

	skyboxProgram.setUniformMat4("view", view);
	skyboxProgram.setUniformMat4("projection", projection);

	skybox->draw(skyboxProgram);

	window->swapBuffers();
}

void Engine::start()
{
	init();
	mainLoop();
	cleanup();
}
