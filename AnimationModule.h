#pragma once
#include<iostream>
#include"Sprite.h"
class AnimationModule
{
public:
	//Constructors and Destructors
	AnimationModule(sf::Sprite* sprite);
	~AnimationModule();

	//Core Functions
	void animateSheet(float speed, bool movement, int sheet_x);
	void animateTimer(float speed);

	//Core Movement
	void animateMovement(sf::Texture& walk_up, sf::Texture& walk_down,
		sf::Texture& walk_left, sf::Texture& walk_right, sf::Texture& walk_diagnol_left_down,
		sf::Texture& walk_diagnol_right_down, sf::Texture& walk_diagnol_right_up,
		sf::Texture& walk_diagnol_left_up, sf::Texture& roll_up, sf::Texture& roll_down,
		sf::Texture& roll_left, sf::Texture& roll_right);
	void animateWalk(sf::Texture& walk_up, sf::Texture& walk_down,
		sf::Texture& walk_left, sf::Texture& walk_right, sf::Texture& walk_diagnol_left_down,
		sf::Texture& walk_diagnol_right_down, sf::Texture& walk_diagnol_right_up,
		sf::Texture& walk_diagnol_left_up);
	void animateRoll(sf::Texture& roll_up, sf::Texture& roll_down, sf::Texture& roll_left, sf::Texture& roll_right);

private:
	//Animation Variables
	sf::Sprite* sprite;

	int frame;
	bool frameInit;

	bool last_key_w;
	bool last_key_a;
	bool last_key_s;
	bool last_key_d;
	bool player_walking;
	bool player_rolling;

	int animationFrame;
	int sheet_walk_x;
	int sheet_walk_y;
	int sheet_roll_x;
	int sheet_roll_y;

	float movementSpeed;

	sf::Vector2f velocity;

	sf::Clock timer;
	sf::Time elapsed;
	sf::Clock dodge_timer;
	sf::Time dodge_elapsed;

	//Assets
	sf::Texture walk_up;
	sf::Texture walk_down;
	sf::Texture walk_left;
	sf::Texture walk_right;
	sf::Texture walk_diagnol_left_down;
	sf::Texture walk_diagnol_right_down;
	sf::Texture walk_diagnol_left_up;
	sf::Texture walk_diagnol_right_up;

	sf::Texture roll_up;
	sf::Texture roll_down;
	sf::Texture roll_left;
	sf::Texture roll_right;


};

