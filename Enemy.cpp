#include "Enemy.h"
//Constructors and Deconstructors
Enemy::Enemy()
{

}

Enemy::Enemy(float hp, float damage, std::string texture, std::string enemy_walk_up, 
	std::string enemy_walk_down, std::string enemy_walk_left, std::string enemy_walk_right)
{
	this->enemyTexture.loadFromFile(texture);
	this->enemy_walk_up.loadFromFile(enemy_walk_up);
	this->enemy_walk_down.loadFromFile(enemy_walk_down);
	this->enemy_walk_left.loadFromFile(enemy_walk_left);
	this->enemy_walk_right.loadFromFile(enemy_walk_right);

	this->hp = hp;
	this->hpMax = hp;
	this->damage = damage;
	this->moveSpeed = 0.5;

	//Initialization
	//this->enemy.setTextureRect(0, 0, 16, 16);
	this->enemy.setScale(3.0f, 3.0f);
	this->animation = new AnimationModule(&this->enemy);
	this->initAnimations();
}

Enemy::~Enemy()
{
	delete this->animation;
}

//Core Functions
void Enemy::update(sf::Vector2f playerPos)
{
	this->walkTowardsPlayer(playerPos);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->enemy);
}

//Spawn Functions

//Movement Functions
void Enemy::walkTowardsPlayer(sf::Vector2f playerPos)
{
	if (playerPos.x > this->enemy.getPosition().x) {
		this->enemy.setPosition(x += this->moveSpeed, y);
		this->animation->play("WALKUP");
	}
	if (playerPos.x < this->enemy.getPosition().x) {
		this->enemy.setPosition(x -= this->moveSpeed, y);
		this->animation->play("WALKUP");
	}
	if (playerPos.y > this->enemy.getPosition().y) {
		this->enemy.setPosition(x, y += this->moveSpeed);
		this->animation->play("WALKUP");
	}
	if (playerPos.y < this->enemy.getPosition().y) {
		this->enemy.setPosition(x, y -= this->moveSpeed);
		this->animation->play("WALKUP");
	}
}

void Enemy::initAnimations()
{
	this->animation->addAnimation("WALKUP", enemy_walk_up, 4, 16, 0.5, 0, 2.0f);
	this->animation->addAnimation("WALKDOWN", enemy_walk_down, 4, 16, 0.2, 0, 2.f);
	this->animation->addAnimation("WALKLEFT", enemy_walk_left, 4, 16, 0.2, 0, 2.f);
	this->animation->addAnimation("WALKRIGHT", enemy_walk_right, 4, 16, 0.2, 0, 2.f);
}

//Modifiers
void Enemy::moveEnemy(sf::Vector2f move)
{
	this->enemy.setPosition(x += move.x, y += move.y);
}

void Enemy::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	this->enemy.setPosition(x, y);
}

void Enemy::setMapPosition(sf::Vector2f position)
{
	this->enemy.setPosition(x += position.x, y += position.y);
}