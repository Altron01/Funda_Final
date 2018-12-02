#pragma once
#include <glm\glm.hpp>
#include <unordered_map>
#include <string>
#include "SpriteBacth.h"
#include "GLTexture.h"


class Zombie;
class Human;

class Agent
{
protected:


	std::string _texturePath;
	float _agent_width;
	float _agent_height;
	int _texture_id;
	float _agent_radius;
	
	float _speed;
	ColorRGBA color;
	void checkTilePosition(const std::vector<std::string>& levelData, 
		std::vector<glm::vec2>& collideTilePosition,float x, float y );
	void collideWithTile(glm::vec2 tilePos);

public:
	glm::vec2 _position;
	Agent(float agent_width,float agent_height,glm::vec2 position, std::string texturePath);
	glm::vec2 getPosition()const { return _position; };

	virtual void update(float deltaTime, bool reloj) = 0;
	virtual void changeTexture(std::string texturePath) = 0;
	virtual std::string getTexture() = 0;
	void draw(SpriteBacth& spritebatch);
	bool collideWithLevel(const std::vector<std::string>& levelData);
	virtual ~Agent();
	bool collideWithAgent(Agent* agent);
};

