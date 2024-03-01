#pragma once
#include<SFML/Graphics.hpp>
class Sprite
{
public:
	//Constructors and Destructors
	Sprite(float x, float y, float pixel_width, float pixel_height, 
		float scale, sf::Texture& sprite_texture);
	~Sprite();

	//Core Functions
	void render(sf::RenderTarget* target);

	//Accessor Functions
	const sf::Vector2f getPosition() const;

	//Modifier Functions
	void setTextureRect(int left, int top, int width, int height);

	sf::Sprite& getSprite() { return this->sprite; };

private:

	//Core Variables
	sf::Sprite sprite;
	sf::Texture sprite_texture;

	float x;
	float y;

	float scale;
	float pixel_width;
	float pixel_height;
};

