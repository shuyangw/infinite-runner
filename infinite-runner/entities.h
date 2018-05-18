#pragma once

#include <vector>

/*
Notes:
	The unit of velocity is: pixels/frame
	TBC
*/
class Entity {
	public:
		int hp;
		float pos_x;
		float pos_y;
		float pos_z;

		//Constructor and destructor
		Entity();
		~Entity() = default;
};

class Player : public Entity{
	public:
		float velocity;
		float jump_vel;
		float armor;
		bool jumping;

		Player();
		~Player() = default;

		//Defined in "entities.cpp"
		bool change_pos(int change);
		void init();
};

class Enemy : public Entity {
	public:
		Enemy();
		~Enemy() = default;

		int type;
		//Defined in "entities.cpp"
		bool change_pos(int change);
};

class Bullet : public Entity { 
	public:
		Bullet(bool harmful, float velocity, float damage, float pos_z);
		~Bullet() = default;

		//int index;

		bool harmful;
		float velocity;
		float damage;
};

typedef struct Packet Packet;
struct Packet {
	std::vector<Entity> enemy_entities;
	std::vector<Entity> obj_entities;
};

//Struct for a 2-Tuple
typedef struct Point Point;
struct Point {
	float x;
	float y;
};

//Struct for a Color given in its RGB values as floats
typedef struct Color Color;
struct Color {
	float r;
	float g;
	float b;
};
