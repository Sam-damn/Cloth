#include "Window.h"


static void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void Window::init(int width, int height, const char * name)
{
	//only initialize the window once
	if (window != nullptr) {
		return;
	}

	//create window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(width, height, name, nullptr, nullptr);

	if (window == nullptr) {
		throw std::runtime_error("Failed to create GLFW window");
	}

	//set opengl context
	glfwMakeContextCurrent(window);

	//load opengl functions (only required once per program)
	static bool gladLoaded = false;
	if (!gladLoaded) {
		gladLoaded = true;
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Failed to initialize GLAD.");
		}
	}

	//set framebuffer size
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Window::close()
{
	glfwTerminate();
}

void Window::manageKeyboardInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
