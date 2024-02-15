#include "Skills.h"
//Constructors and Destructors
Skills::Skills()
{
	//Main attributes
	this->level = 0;
	this->skill_point = 0;

	this->exp = 0;
	this->exp_next = 100;

	this->strength = 0;
	this->agility = 0;
	this->intelligence = 0;
}

Skills::~Skills()
{

}

//Core Functions
void Skills::render(sf::RenderTarget* target)
{

}

void Skills::levelUp()
{
	if (this->exp >= this->exp_next) {
		this->level++;
		this->skill_point++;
		this->exp = 0;
		this->exp_next += 100;
	}
}

void Skills::skillUp(float skill)
{
	if (this->skill_point > 0) {
		this->skill_point--;
		skill++;
	}
}