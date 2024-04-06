#pragma once
//Modules
#include"AnimationModule.h"
#include"CollisionModule.h"
#include<iostream>
class Enemy
{
public:
	//Constructors and Deconstructors
	Enemy(std::string texture, std::string enemy_walk_up, std::string enemy_walk_down,
		std::string enemy_walk_left, std::string enemy_walk_right);
	~Enemy();

	//Core Functions
	void update();
	void render(sf::RenderTarget* target);

	//Movement Functions
	void initAnimations();
	void walkTowardsPlayer();

	//Modifiers
	void moveEnemy(sf::Vector2f move);

private:
	Sprite* enemy;
	sf::Texture enemyTexture;
	AnimationModule* animation;
	CollisionModule* collision;

	float x;
	float y;

	//Assets
	sf::Texture enemy_walk_up;
	sf::Texture enemy_walk_down;
	sf::Texture enemy_walk_left;
	sf::Texture enemy_walk_right;
};

