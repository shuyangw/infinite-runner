#include <iostream>

#include "game.h"
#include "entities.h"

Game::Game() {
	Game::player.velocity = 3.5;
	bullet_CD_lt = 0.0;
}

Packet Game::send_packet(void) {
	//TODO
	Packet p;
	p.bullet_entities = Game::bullet_entities;
	return p;
}

//Begin game logic section------------------------------------------------------
//Argument specifies direction of movement, negative for left, positive for 
//right
bool Game::player_move(int direction) {
	bool success;
	if (direction < 0) {
		success = player.change_pos(-player.velocity);
	}
	else {
		success = player.change_pos(player.velocity);
	}
	return success;
}

void Game::player_shoot_bullet() {
	Bullet *b = new Bullet( //Initializes a bullet that is
		false,		   //not harmful to the player
		0.5,		   //has a velocity of 0.5 pixels per frame
		1,			   //does 1 damage to the enemy
		Game::player.pos_z
	);
	b->pos_x = Game::player.pos_x;
	b->pos_y = Game::player.pos_y + 10.0;
	b->obj_type = 2;
	Game::bullet_entities.push_back(*b);
}
