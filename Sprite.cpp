#include "Sprite.h"
//Constructors and Destructors
Sprite::Sprite(float x, float y, float pixel_width, float pixel_height, 
	float scale, sf::Texture& sprite_texture)
{
	this->sprite.setTexture(sprite_texture);
	this->sprite.setPosition(x, y);
	this->sprite.setScale(scale, scale);
	this->sprite.setTextureRect(sf::IntRect(pixel_width, pixel_height, pixel_width, pixel_height));
}

Sprite::~Sprite()
{

}

//Core Functions
void Sprite::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

//Accessor Functions
const sf::Vector2f Sprite::getPosition() const
{
	return this->sprite.getPosition();
}

//Modifier Functions
void Sprite::setTextureRect(int left, int top, int width, int height)
{
	this->sprite.setTextureRect(sf::IntRect(left, top, width, height));
}