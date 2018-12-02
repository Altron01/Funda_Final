#pragma once
#include "SpriteBacth.h"
#include <glm\glm.hpp>;
#include "GLTexture.h";
#include <string>;

class Button
{
private:
	std::string _texture;
	int _textureID;
	glm::vec2 _position;
public:
	void draw(
			SpriteBacth& spriteBatch);
	Button(std::string texture);
	bool clicked(glm::vec2 position);
	void setPosition(glm::vec2 position);
	glm::vec2 getPosition() const {
		return _position;
	}
	~Button();
};

