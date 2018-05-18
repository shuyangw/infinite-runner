#pragma once

#include "entities.h"

using namespace std;

class Game {
	public:
		Game();
		
		//Player object
		Player player;
		
		//Enemy entities
		vector<Entity> enemy_entities;

		//Object entities
		vector<Entity> obj_entities;

		//-------------Methods--------------
		//Sends info packet to screen for rendering
		Packet send_packet(void);
		
		//Game logic
		bool player_move(int move_by);
		void player_shoot_bullet(void);

		//Initialization
		void initialize(void);


		//Other variables
		float jump_CD_lt;
		float bullet_CD_lt;
};