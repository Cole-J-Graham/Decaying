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
	void levelUp();
	void skillUp(float skill);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

private:
	int level;
	int skill_point;

	int exp;
	int exp_next;

	float strength;
	float agility;
	float intelligence;

};