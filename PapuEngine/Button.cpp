#include "Button.h"
#include "ResourceManager.h"
#include <glm\glm.hpp>
#include <iostream>


Button::Button(std::string texture): _texture(texture)
{
	_position = glm::vec2(400, 300);
	_textureID = ResourceManager::getTexture(texture).id;
}

bool Button::clicked(glm::vec2 position) {
	return (position.x > _position.x)
		&& (position.x < _position.x + 190)
		&& (500 - position.y > _position.y)
		&& (500 - position.y < _position.y + 50);
}

void Button::draw(SpriteBacth& spritebatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA color;
	color.set(255, 255, 255, 255);
	glm::vec4 desctRect(_position.x, _position.y, 190, 50);
	spritebatch.draw(desctRect, uvRect, _textureID, 0.0f, color);
}	

Button::~Button()
{
}
