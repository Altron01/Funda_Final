#pragma once
#include <glm/glm.hpp>
#include "Agent.h"
#include "SpriteBacth.h"
class Bullet : public Agent
{
public:
	~Bullet();
	Bullet(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture
	);
	void update(float deltaTime, bool reloj);
	void setPosition(glm::vec2 position);
	void changeTexture(std::string texturePath);
	std::string getTexture();

};

