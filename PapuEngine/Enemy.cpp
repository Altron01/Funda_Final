#include "Enemy.h"
#include "Bullet.h"
#include <SDL\SDL.h>
#include <iostream>


Enemy::Enemy(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	int enemy_type) :
	Agent(agent_width, agent_height, position, texture)
{
	color = ColorRGBA(255, 255, 255, 255);
	switch (enemy_type)
	{
	case ENEMY_TYPE::BIG:
		color.r = 0;
		color.g = 0;
		color.b = 255;
		life = 3;
		break;
	case ENEMY_TYPE::NORMAL:
		color.r = 255;
		color.g = 0;
		color.b = 0;
		life = 2;
		break;
	case ENEMY_TYPE::SMALL:
		color.r = 0;
		color.g = 255;
		color.b = 0;
		life = 1;
		break;
	default:
		break;
	}
}

void Enemy::update(float deltaTime, bool reloj) {
	_position.x -= 3;
}


void Enemy::setPosition(glm::vec2 position) {
	_position = position;
}
void Enemy::changeTexture(std::string texturePath) {
	_texturePath = texturePath;
}
std::string Enemy::getTexture() {
	return _texturePath;
}

Enemy::~Enemy() {}