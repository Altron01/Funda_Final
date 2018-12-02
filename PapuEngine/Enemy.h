#pragma once
#include "Agent.h"

enum ENEMY_TYPE {SMALL, NORMAL, BIG};

class Enemy : public Agent
{
public:
	int life;
	int type;
	Enemy(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture,
		int enemy_type
	);
	void update(float deltaTime, bool reloj);
	void setPosition(glm::vec2 position);
	void changeTexture(std::string texturePath);
	std::string getTexture();
	~Enemy();
};

