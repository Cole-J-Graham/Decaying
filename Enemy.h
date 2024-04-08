#pragma once
//Modules
#include"AnimationModule.h"
#include"CollisionModule.h"
#include<iostream>
class Enemy
{
public:
	//Constructors and Deconstructors
	Enemy();
	Enemy(float hp, float damage, std::string texture, 
		std::string enemy_walk_up, std::string enemy_walk_down, std::string enemy_walk_left, 
		std::string enemy_walk_right);
	~Enemy();

	//Core Functions
	void update(sf::Vector2f playerPos);
	void render(sf::RenderTarget* target);

	//Movement Functions
	void initAnimations();
	void walkTowardsPlayer(sf::Vector2f playerPos);

	//Modifiers
	void moveEnemy(sf::Vector2f move);
	void setPosition(float x, float y);

	//Accessors
	sf::FloatRect getGlobalBounds() { return this->enemy->getGlobalBounds(); }
	int& getHp() { return this->hp; }
	int& getDamage() { return this->damage; }

	Sprite* enemy;

private:
	sf::Texture enemyTexture;
	AnimationModule* animation;
	CollisionModule* collision;

	int hp;
	int hpMax;
	int damage;

	float moveSpeed;

	float x;
	float y;

	//Assets
	sf::Texture enemy_walk_up;
	sf::Texture enemy_walk_down;
	sf::Texture enemy_walk_left;
	sf::Texture enemy_walk_right;
};

