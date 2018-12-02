#pragma once
#include "SpriteBacth.h"
#include "GLTexture.h"
#include <glm\glm.hpp>
#include <string>

class Background
{
private :
	std::string _texture;
	ColorRGBA _color;
	int _textureID;
public:
	Background(std::string texture);
	void draw(SpriteBacth& spriteBatch);
	void setColor(ColorRGBA color);
	ColorRGBA getColor() const {
		return _color;
	}
	~Background();
};

