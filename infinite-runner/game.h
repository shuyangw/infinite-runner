#pragma once

#include "entities.h"

using namespace std;

class Game {
	public:
		Game();
		~Game() = default;
		
		//Player object
		Player player;
		
		//Enemy entities
		vector<Entity> enemy_entities;

		//Object entities
		vector<Bullet> bullet_entities;

		//-------------Methods--------------
		//Sends info packet to screen for rendering
		Packet send_packet(void);
		
		//Game loop
		void next_loop(void);

		//Game logic
		bool player_move(int move_by);
		void player_shoot_bullet(void);


		//Other variables
		float bullet_CD_lt;
};