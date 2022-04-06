#include <iostream>
#include <limits>
#include "Engine.h"
#include <glm/glm.hpp>


int main(int argc, char** argv) {
	Engine engine;

	

	try {
		engine.start();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		getchar();
		return EXIT_FAILURE;
	}




	

	/*std::cout << std::numeric_limits<float>::min();
	getchar();*/
	
	return EXIT_SUCCESS;
}
