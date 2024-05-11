#include "Enemy.h"
//Constructors and Deconstructors
Enemy::Enemy()
{

}

Enemy::Enemy(float hp, float damage, int colOffset, std::string texture, std::string enemy_walk_up, 
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
	this->colOffset = colOffset;

	//Initialization
	this->enemy.setScale(3.0f, 3.0f);
	this->animation = new AnimationModule(&this->enemy);
	this->initRects();
	this->initAnimations();
}

Enemy::~Enemy()
{
	delete this->animation;

	//Deconstruct Rectangles
	auto ir = this->rectangles.begin();
	for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
		delete ir->second;
	}
}

//Core Functions
void Enemy::update(sf::Vector2f playerPos)
{
	this->walkTowardsPlayer(playerPos);
	this->updateRects();
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->enemy);
	this->renderRects(target);
}

//Movement Functions
void Enemy::walkTowardsPlayer(sf::Vector2f playerPos)
{
	// Calculate direction towards the player
	sf::Vector2f direction = playerPos - this->enemy.getPosition();

	// Normalize the direction vector
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (distance > 0.1f) { // Avoid division by zero
		direction /= distance;
	}

	// Adjust the move speed based on the distance
	float moveSpeedAdjusted = this->moveSpeed;
	if (distance < 50.0f) { // Decrease move speed when close to the player
		moveSpeedAdjusted = this->moveSpeed * 0.5f;
	}

	// Calculate the step size to move the enemy
	sf::Vector2f step = direction * moveSpeedAdjusted;

	// Update the enemy's position
	this->enemy.move(x += step.x, y += step.y);

	// Play animation
	this->animation->play("WALKUP");
}

void Enemy::initAnimations()
{
	this->animation->addAnimation("WALKUP", enemy_walk_up, 4, 32, 0.5, 32, 2.0f);
	this->animation->addAnimation("WALKDOWN", enemy_walk_down, 4, 32, 0.2, 32, 2.f);
	this->animation->addAnimation("WALKLEFT", enemy_walk_left, 4, 32, 0.2, 32, 2.f);
	this->animation->addAnimation("WALKRIGHT", enemy_walk_right, 4, 32, 0.2, 32, 2.f);
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

//Rectangle Functions
void Enemy::updateRects()
{
	this->rectangles["HITBOX"]->setPosition(x + this->colOffset, y + this->colOffset);
	this->rectangles["HP_RECT"]->setPosition(x + 25, y + 10);
	this->rectangles["HP_RECT"]->setString(std::to_string(this->hp));
}

void Enemy::initRects()
{
	this->rectangles["HITBOX"] = new Rectangle(x, y, 50, 50, sf::Color::Black, sf::Color::Transparent, 0.f, true);
	this->rectangles["HP_RECT"] = new Rectangle(x, y, 30, 10, sf::Color::Black, sf::Color::White, 1.f, "", 9, false);
}

void Enemy::renderRects(sf::RenderTarget* target)
{
	for (auto& it : this->rectangles) {
		it.second->render(target);
	}
}

sf::FloatRect Enemy::getEnemyHitbox() { return this->rectangles["HITBOX"]->getGlobalBounds(); }