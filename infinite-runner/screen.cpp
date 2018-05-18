#include <iostream>
#include <string>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

#include "entities.h"
#include "game.h"
#include "log.h"
#include "keyboard.h"

const int SELF_RESOLUTION_W	=			1280;
const int SELF_RESOLUTION_H =			720;
const float SELF_LINE_WIDTH =			1.5;
const int SELF_NUM_CIRCLE_POINTS =		15;
const float SELF_CIRCLE_RADIUS =		10.0;

//Next few points are ordered by {x,y}
const Point SELF_LEFT_F_INIT =			{ 0.0, 240.0 };
const Point SELF_LEFT_T_INIT =			{ 440.0, 576.0 };
const Point SELF_RIGHT_F_INIT =			{ 1280.0, 240.0 };
const Point SELF_RIGHT_T_INIT =			{ 840.0, 576.0 };

//Colors defined by their float values ranging from 0.0f to 1.0f
Color SELF_RED =						{ 1.000, 0.000, 0.000 };
Color SELF_LCYAN =						{ 0.878, 1.000, 1.000 };
Color SELF_WHITE =						{ 1.000, 1.000, 1.000 };

//Game object
Game* game;
//Current packet
Packet packet;

//Global conditions

using namespace std;

//Initializes Anti-Aliasing and line width
void init_line_settings(void) {
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(SELF_LINE_WIDTH);
	glDepthMask(false);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

//Draws line from point from p_1 point p_2 with p_2 having an alpha of 0
void draw_line_fade(Point p_1, Point p_2, Color c) {
	glBegin(GL_LINES);
	glColor4f(c.r, c.g, c.b, 1.0);
	glVertex2f(p_1.x, p_1.y);
	glColor4f(c.r, c.g, c.b, 0.0);
	glVertex2f(p_2.x, p_2.y);
	glEnd();
}

void draw_line(Point p_1, Point p_2, Color c) {
	glBegin(GL_LINES);
	glColor3f(c.r, c.g, c.b);
	glVertex2f(p_1.x, p_1.y);
	glVertex2f(p_2.x, p_2.y);
	glEnd();
}

void draw_line_color_alpha(Point p_1, Point p_2, Color c, float alpha){
	glBegin(GL_LINES);
	glColor4f(c.r, c.g, c.b, alpha);
	glVertex2f(p_1.x, p_1.y);
	glVertex2f(p_2.x, p_2.y);
	glEnd();
}

//Draws circle centered at origin with color c
void draw_circle(Point origin, Color c) {
	glBegin(GL_LINE_LOOP);
	glColor3f(c.r, c.g, c.b);
	for (int i = 0; i < SELF_NUM_CIRCLE_POINTS; i++) {
		float theta = 2.0f * M_PI * float(i) / float(SELF_NUM_CIRCLE_POINTS);
		float x = SELF_CIRCLE_RADIUS * cosf(theta);
		float y = SELF_CIRCLE_RADIUS * sinf(theta);
		glVertex2f(x + origin.x, y + origin.y);
	}
	glEnd();
}

void draw_circle_radius(Point origin, Color c, float radius) {
	glBegin(GL_LINE_LOOP);
	glColor3f(c.r, c.g, c.b);
	for (int i = 0; i < SELF_NUM_CIRCLE_POINTS; i++) {
		float theta = 2.0f * M_PI * float(i) / float(SELF_NUM_CIRCLE_POINTS);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		glVertex2f(x + origin.x, y + origin.y);
	}
	glEnd();
}

//Corresponds to quadratic equation in the form x(t)=(1/2)at^2
float left_endpt_function(float x){
	const float ACCEL = 0.057395;
	return ((0.5)*(ACCEL)*pow(x, 2.0));
}

void draw_player() {
	if (game->player.jumping) {
		game->player.pos_z += game->player.jump_vel;
		draw_circle({ 640, 100 + game->player.pos_z }, SELF_LCYAN);
		draw_line_color_alpha(
			{ 640, 100 + game->player.pos_z },
			{ 640, 100 - SELF_CIRCLE_RADIUS },
			SELF_LCYAN,
			0.25
		);
		if (game->player.jump_vel > 0) {
			game->player.jump_vel -= 0.5;
		}
		else {
			if (game->player.pos_z + game->player.jump_vel <= 0) {
				game->player.pos_z = 0;
				draw_circle({ 640, 100 }, SELF_LCYAN);
				game->player.jumping = false;
				return;
			}
			game->player.jump_vel -= 0.5;
		}
	}
	else {
		draw_circle({ 640, 100 }, SELF_LCYAN);
	}
}

//Initializes the left and right borders for the board
void initialize_field(void) {
	float x = game->player.pos_x;	
	if (x == 100) {
		//Draw left line
		draw_line_fade(
			SELF_LEFT_F_INIT, 
			SELF_LEFT_T_INIT,
			SELF_WHITE
		);
		//Draw right line
		draw_line_fade(
			SELF_RIGHT_F_INIT, 
			SELF_RIGHT_T_INIT, 
			SELF_WHITE
		);
	}
	else {
		float endpoint_x, normalize, projected_x;
		float midpoint = SELF_RESOLUTION_W / 2;
		//Calculate to point for left
		endpoint_x = midpoint - (x / 100) * 200;	
		Point endpoint_l_t = { endpoint_x, SELF_LEFT_T_INIT.y };

		//Calculate from point for left
		Point endpoint_l_f;
		normalize = 200 - x;
		projected_x = left_endpt_function(normalize);
		if(projected_x <= 520){
			endpoint_l_f.x = 0;
			endpoint_l_f.y = 520 - projected_x;
		}
		else{
			endpoint_l_f.x = projected_x - 520;
			endpoint_l_f.y = 0;
		}

		//Draw left line
		draw_line_fade(
			endpoint_l_f,
			endpoint_l_t,
			SELF_WHITE
		);

		//Calculate to point for right
		endpoint_x = midpoint + ((100 - x) / 100) * 200 + 200;	
		Point endpoint_r_t = { endpoint_x, SELF_RIGHT_T_INIT.y };
		
		//Calculate from point for right
		Point endpoint_r_f;
		normalize = x;
		projected_x = left_endpt_function(normalize);
		if(projected_x <= 520){
			endpoint_r_f.x = SELF_RESOLUTION_W;
			endpoint_r_f.y = 520 - projected_x;
		}
		else{
			endpoint_r_f.x = SELF_RESOLUTION_W - projected_x + 520;
			endpoint_r_f.y = 0;
		}

		//Draw right line
		draw_line_fade(
			endpoint_r_f,
			endpoint_r_t,
			SELF_WHITE
		);
	}
}

void initialize_entities(void) {
	//Initializes player object on screen
	draw_player();

	vector<Entity>::iterator i;
	vector<Entity> objects = packet.obj_entities;
	for (i = objects.begin(); i != objects.end(); ++i) {
		Entity curr = *i;
		draw_circle_radius(
			{ curr.pos_x, curr.pos_y + curr.pos_z + SELF_CIRCLE_RADIUS}, 
			SELF_WHITE,
			1
		);
		/*if (curr.pos_z != 0) {
		
		}*/
	}
}

void render_loop() {
	//Clears the screen
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(10);

	//Initializes line settings
	init_line_settings();

	//Initializes the movement boundaries
	initialize_field();

	initialize_entities();
}

void main_loop(GLFWwindow* window) {
	//FPS Counter stuff
	double FPS_counter_lt = glfwGetTime();
	int nbFrames = 0;

	//Enables blending for vertex alpha changes
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	game = new Game();

	do {
		//Rest of the FPS Counter
		double FPS_counter_ct = glfwGetTime();
		nbFrames++;
		if (FPS_counter_ct - FPS_counter_lt >= 1.0) { // If last print was more than 1 sec ago
			cout << to_string(int(nbFrames)) + " FPS"  << endl;
			nbFrames = 0;
			FPS_counter_lt += 1.0;
		}

		//Keyboard inputs
		keyboard_input(window, game);

		//Receive Packet
		packet = game->send_packet();

		//Renders screen, must absolutely be last
		render_loop();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}