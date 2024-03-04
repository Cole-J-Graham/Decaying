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
	void animateSheet(float speed, bool action, int offset, int sheet, int maxFrame);
	void animateTimer(int maxFrame, float speed);

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

	bool last_key_w;
	bool last_key_a;
	bool last_key_s;
	bool last_key_d;
	bool player_walking;
	bool player_rolling;

	int animationFrame;

	float movementSpeed;

	sf::Vector2f velocity;

	sf::Clock animationTimer;
	sf::Time animationElapsed;
	sf::Clock dodge_timer;
	sf::Time dodge_elapsed;
};

