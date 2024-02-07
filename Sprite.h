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

	//Animation Functions
	void animateTimer(float speed);
	void animateSheet(float speed, bool movement, int sheet_x);
	void animateMovement();
	void animateWalk(sf::Texture& walk_up, sf::Texture& walk_down, sf::Texture& walk_left, sf::Texture& walk_right);
	void animateRoll(sf::Texture& roll_up, sf::Texture& roll_down, sf::Texture& roll_left, sf::Texture& roll_right);

	//Assets
	void loadAssets();

	sf::Sprite& getSprite() { return this->sprite; };

private:
	//Core Variables
	sf::Sprite sprite;
	sf::Texture sprite_texture;

	sf::Clock dodge_timer;
	sf::Time dodge_elapsed;

	int sheet_walk_x;
	int sheet_walk_y;
	int sheet_roll_x;
	int sheet_roll_y;
	float x;
	float y;
	float scale;
	float pixel_width;
	float pixel_height;

	//Animation Variables
	int frame;
	bool frameInit;

	bool last_key_w;
	bool last_key_a;
	bool last_key_s;
	bool last_key_d;

	bool player_walking;
	bool player_rolling;
	int animationFrame;
	float movementSpeed;
	sf::Vector2f velocity;

	sf::Clock timer;
	sf::Time elapsed;

	//Assets
	sf::Texture zin_walk_up;
	sf::Texture zin_walk_down;
	sf::Texture zin_walk_left;
	sf::Texture zin_walk_right;

	sf::Texture zin_roll_up;
	sf::Texture zin_roll_down;
	sf::Texture zin_roll_left;
	sf::Texture zin_roll_right;
};

