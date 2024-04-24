#pragma once
#include"Enemy.h"
class Slime
{
public:
	//Constructors and Deconstructors
	Slime();
	~Slime();

	//Core Functions
	void update(sf::Vector2f playerPos);
	void render(sf::RenderTarget* target);

	//Modifiers
	void setPosition(float x, float y);

private:
	float x;
	float y;
	Enemy slime;
};