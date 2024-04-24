#include "Slime.h"
//Constructors and Deconstructors
Slime::Slime()
{
	
}

Slime::~Slime()
{

}

//Core Functions
void Slime::update(sf::Vector2f playerPos)
{
	this->slime.walkTowardsPlayer(playerPos);
}

void Slime::render(sf::RenderTarget* target)
{
	this->slime.render(target);
}

//Modifiers
void Slime::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	this->slime.setPosition(x, y);
}