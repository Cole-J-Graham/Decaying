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
	void checkForMovement(sf::Texture& up, sf::Texture& down, sf::Texture& left, sf::Texture& right);
	void render(sf::RenderTarget* target);
	void animateTimer();

	sf::Sprite& getSprite() { return this->sprite; };

private:
	//Core Variables
	sf::Sprite sprite;
	sf::Texture sprite_texture;

	int sheet_x;
	int sheet_y;
	float x;
	float y;
	float scale;
	float pixel_width;
	float pixel_height;

	//Animation Variables
	int frame;
	bool frameInit;

	bool playerMoving;
	int animationFrame;
	float movementSpeed;
	sf::Vector2f velocity;

	sf::Clock timer;
	sf::Time elapsed;
};

