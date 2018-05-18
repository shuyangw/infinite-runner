#include <GLFW/glfw3.h>

#include "game.h"

void keyboard_input(GLFWwindow* window, Game* game) {
	if (glfwGetKey(window, GLFW_KEY_A)) {
		game->player_move(-1);
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		game->player_move(1);
	}
	if (glfwGetKey(window, GLFW_KEY_W)) {
		float jump_CD_ct = glfwGetTime();
		if (!game->player.jumping && jump_CD_ct - game->jump_CD_lt >= 1.0) {
			game->player.jump_vel = 10.0;
			game->player.jumping = true;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE)) {
		float bullet_CD_ct = glfwGetTime();
		if (bullet_CD_ct - game->bullet_CD_lt >= 0.2) {
			game->player_shoot_bullet();
		}
	}
}