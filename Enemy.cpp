#include "Enemy.h"
//Constructors and Deconstructors
Enemy::Enemy(std::string texture, std::string enemy_walk_up, std::string enemy_walk_down,
	std::string enemy_walk_left, std::string enemy_walk_right)
{
	this->enemyTexture.loadFromFile(texture);
	this->enemy_walk_up.loadFromFile(enemy_walk_up);
	this->enemy_walk_down.loadFromFile(enemy_walk_down);
	this->enemy_walk_left.loadFromFile(enemy_walk_left);
	this->enemy_walk_right.loadFromFile(enemy_walk_right);

	this->x = 100;
	this->y = 100;

	//Initialization
	this->enemy = new Sprite(x, y, 16.f, 16.f, 2.0f, this->enemyTexture);
	this->enemy->setTextureRect(0, 0, 16, 16);
	this->animation = new AnimationModule(&this->enemy->getSprite());
	this->collision = new CollisionModule();
	this->initAnimations();
}

Enemy::~Enemy()
{
	delete this->collision;
	delete this->animation;
	delete this->enemy;
}

//Core Functions
void Enemy::update()
{

}

void Enemy::render(sf::RenderTarget* target)
{
	this->enemy->render(target);
}

//Movement Functions
void Enemy::walkTowardsPlayer()
{
	//Player at 900, 500

}

void Enemy::initAnimations()
{
	this->animation->addAnimation("WALKUP", enemy_walk_up, 4, 16, 0.2, 0);
	this->animation->addAnimation("WALKDOWN", enemy_walk_down, 4, 16, 0.2, 0);
	this->animation->addAnimation("WALKLEFT", enemy_walk_left, 4, 16, 0.2, 0);
	this->animation->addAnimation("WALKRIGHT", enemy_walk_right, 4, 16, 0.2, 0);
}

//Modifiers
void Enemy::moveEnemy(sf::Vector2f move)
{
	this->enemy->setPosition(x += move.x, y += move.y);
}