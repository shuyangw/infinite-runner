#pragma once

#include <iostream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#pragma comment (lib, "glew32s.lib")

#include "game.h"

#define SELF_RESOLUTION_W 1280
#define SELF_RESOLUTION_H 720

using namespace glm;
using namespace std;

void init_line_settings(void);
void draw_line_fade(Point p_1, Point p_2, Color c);
void draw_line(Point p_1, Point p_2, Color c);
void initialize_field(void);
void initialize_entities(void);
void render_loop();
void keyboard_input(GLFWwindow* window);
void main_loop(GLFWwindow* window);