#include "Jugador.h"
#include "Bullet.h"
#include <SDL\SDL.h>
#include <iostream>


Jugador::Jugador(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture):
		Agent(agent_width,agent_height,position,texture)
{
	maxBulletCount = bulletCount = 15;
	magazineCount = 2;
	score = 0;
}

Jugador::Jugador(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	InputManager* inputManager
	) :
	Agent(agent_width, agent_height, position, texture)
{
	color = ColorRGBA(255, 255, 255, 255);
	maxBulletCount = bulletCount = 15;
	magazineCount = 2;
	score = 0;
	_inputManager = inputManager;
}

void Jugador::update(float deltaTime,bool reloj) {
	if (score == 100) {
		score = 0;
		magazineCount += 1;
	}
	if (_inputManager->isKeyDown(SDLK_w)) {
		_position.y += 3.0f;
	}
	if (_inputManager->isKeyDown(SDLK_s)) {
		_position.y -= 3.0f;
	}
	if (_inputManager->isKeyDown(SDLK_d)) {
		_position.x += 4.0f;
	}
	if (_inputManager->isKeyDown(SDLK_a)) {
		_position.x -= 4.0f;
	}
	if (_inputManager->wasKeyPressed(SDLK_r)) {
		if (magazineCount > 0 && bulletCount < maxBulletCount) {
			magazineCount -= 1;
			bulletCount = 15;
		}
	}
}


void Jugador::setPosition(glm::vec2 position) {
	_position = position;
}
void Jugador::changeTexture(std::string texturePath) {
	_texturePath = texturePath;
}
std::string Jugador::getTexture() {
	return _texturePath;
}

Jugador::~Jugador()
{
}

bool Jugador::canShoot() {
	return (bulletCount > 0);
}

void Jugador::useBullet() {
	if(bulletCount > 0) bulletCount -= 1;
}