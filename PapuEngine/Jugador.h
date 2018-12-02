#pragma once
#include "Agent.h"
#include "InputManager.h"
class Jugador : public Agent
{
private:
	InputManager* _inputManager;

public:
	unsigned int maxBulletCount;
	unsigned int bulletCount;
	unsigned int magazineCount;
	unsigned int score;
	Jugador(float agent_width,
			float agent_height,
			glm::vec2 position,
			std::string texture
	);
	Jugador(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture,
		InputManager* inputManager
	);
	void update(float deltaTime,bool reloj);
	void setPosition(glm::vec2 position);
	void changeTexture(std::string texturePath);
	bool canShoot();
	void useBullet();
	std::string getTexture();
	~Jugador();
};

