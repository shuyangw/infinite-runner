#include <GLFW/glfw3.h>

#include "game.h"

//Keyboard listener for user controls
void keyboard_input(GLFWwindow* window, Game* game) {
	//Move left
	if (glfwGetKey(window, GLFW_KEY_A)) {
		game->player_move(-1);
	}
	//Move right
	if (glfwGetKey(window, GLFW_KEY_D)) {
		game->player_move(1);
	}
	//Jump
	if (glfwGetKey(window, GLFW_KEY_W)) {
		if (!game->player.jumping) {
			game->player.jump_vel = 10.0;
			game->player.jumping = true;
		}
	}
	//Fires bullet on a initial 0.5 second cooldown 
	//MAY CHANGE LATER
	if (glfwGetKey(window, GLFW_KEY_SPACE)) {
		float bullet_CD_ct = glfwGetTime();
		if(game->bullet_CD_lt == 0){
			game->bullet_CD_lt = glfwGetTime();
		}
		if (bullet_CD_ct - game->bullet_CD_lt >= 0.5) {
			game->player_shoot_bullet();
			game->bullet_CD_lt = glfwGetTime();
		}
	}
}