#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define GLEW_STATIC

#include "screen.h"
#include "log.h"

#pragma comment (lib, "glew32s.lib")
	
using namespace std;

int main(void){
	//Exits if there exits a problem with initialization
	if (!glfwInit()) {
		cout << "Error init" << endl;
		log_writeln("Error with initialization in main.cpp");
	}

	GLFWwindow* window;
	window = glfwCreateWindow(SELF_RESOLUTION_W, SELF_RESOLUTION_H, "Infinite Runner", NULL, NULL);
	if (window == NULL) {
		log_writeln("Error initializing window in main.cpp");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		log_writeln("Failed to initialize GLEW");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// set up view
	glViewport(0, 0, SELF_RESOLUTION_W, SELF_RESOLUTION_H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Creates canvas
	glOrtho(0.0, SELF_RESOLUTION_W, 0.0, SELF_RESOLUTION_H, 0.0, 1.0);

	log_writeln("Initialization successful! Starting render loop...");

	main_loop(window);
}