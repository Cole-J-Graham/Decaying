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

void Skills::update()
{
	this->checkForLevelUp();
}

void Skills::checkForLevelUp()
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

//Display Functions
std::string& Skills::displayStats()
{
	display = "LVL[" + std::to_string(this->level) + "]\n" +
			"SP[" + std::to_string(this->skill_point) + "]\n" +
			"EXP[" + std::to_string(this->exp) + "/" + std::to_string(this->exp_next) + "]\n\n"
			"STR[" + std::to_string(this->strength) + "]\n" + 
			"AGI[" + std::to_string(this->agility) + "]\n" + 
			"INT[" + std::to_string(this->intelligence) + "]\n";

	return display;
}