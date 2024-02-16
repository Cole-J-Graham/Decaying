#pragma once
#include"PlayerGUI.h"
class Skills
{
public:
	//Constructors and Destructors
	Skills();
	~Skills();

	//Core Functions
	void render(sf::RenderTarget* target);
	void update();
	void checkForLevelUp();
	void skillUp(float skill);

	//Display Functions
	std::string& displayStats();

private:
	int level;
	int skill_point;

	int exp;
	int exp_next;

	float strength;
	float agility;
	float intelligence;

	std::string display;

};