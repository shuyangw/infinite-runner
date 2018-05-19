#include <cmath>
#include <assert.h>
#include <iostream>

#include "entities.h"
#include "log.h"

const int MAX_X = 200;
const int MIN_X = 0;
const int MAX_Y = 200;
const int MIN_Y = 0;

using namespace std;

Entity::Entity(void) {
	this->pos_x = 0.0;
	this->pos_y = 0.0;
	this->pos_z = 0.0;
	this->hp = 0;
}

void Player::init(void) {
	this->hp = 100;
	this->pos_x = 100.0;
	this->pos_y = 0.0;
	this->pos_z = 0.0;
	this->armor = 0.0;
	this->jump_vel = 0.0;
	this->jumping = false;
}

Player::Player(void) {
	log_writeln("Player initialized");
	Player::init();
	Player::obj_type = 1;
}

bool Player::change_pos(int change) {
	if (Player::pos_x + change > MAX_X) {
		pos_x += abs(MAX_X - Player::pos_x);
	}
	else if (Player::pos_x + change < MIN_X) {
		pos_x -= Player::pos_x;
	}
	else {
		Player::pos_x += change;
	}

	//Final conditions of position
	if (Player::pos_x <= MAX_X && Player::pos_x >= MIN_X) {
		return true;
	}
	else {
		return false;
	}
}

Enemy::Enemy(void) {
	//TODO: Maybe add constructor for Enemy?
	cout << "Enemy created" << endl;
	Enemy::obj_type = 2;
}

// TODO: If decided to have Enemies change pos_x, change this
bool Enemy::change_pos(int change){
	if (Enemy::pos_y + change > MAX_Y) {
		pos_y += abs(MAX_Y - Enemy::pos_y);
	}
	else if (Enemy::pos_y + change < MIN_Y) {
		pos_y -= Enemy::pos_y;
	}
	else {
		Enemy::pos_y += change;
	}

	//Final conditions of position
	if (Enemy::pos_y <= MAX_Y && Enemy::pos_y >= MIN_Y) {
		return true;
	}
	else {
		return false;
	}
}

//Bullet constructor
Bullet::Bullet(bool harmful, float velocity, float damage, float pos_z){
	this->harmful = harmful;
	this->velocity = velocity;
	this->damage = damage;
	this->damage = pos_z;
}