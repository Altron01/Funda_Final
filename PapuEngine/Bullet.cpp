#include "Bullet.h"
#include "ResourceManager.h"
#include "GLTexture.h"


Bullet::Bullet(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture) :
	Agent(agent_width, agent_height, position, texture)
{
	color = ColorRGBA(255, 255, 255, 255);
}

void Bullet::update(float deltaTime, bool reloj) {
	_position.x += 3.0;
}


void Bullet::setPosition(glm::vec2 position) {
	_position = position;
}
void Bullet::changeTexture(std::string texturePath) {
	_texturePath = texturePath;
}
std::string Bullet::getTexture() {
	return _texturePath;
}


Bullet::~Bullet()
{
}
