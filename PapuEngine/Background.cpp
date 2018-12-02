#include "Background.h"
#include "ResourceManager.h";


Background::Background(std::string texture)
			:_texture(texture)
{
	_textureID 
		= ResourceManager::getTexture(_texture).id;
	_color.set(255, 255, 255, 255);
}

void Background::draw(SpriteBacth& spriteBatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desctRect(0, 0, 1000, 600);
	spriteBatch.draw(desctRect, uvRect, _textureID, 0.0f, _color);
}

void Background::setColor(ColorRGBA color) {
	_color = color;
}


Background::~Background()
{
}
