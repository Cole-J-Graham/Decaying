#pragma once
#include"Rectangle.h"
#include<map>
#include<iostream>
class Inventory
{
public:
	//Constructors and Desconstructors
	Inventory();
	~Inventory();

	//Core Functions
	void render(sf::RenderTarget* target);
	void checkForInput();

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

private:
	sf::Clock timer;
	sf::Time elapsed;

	std::map<std::string, Rectangle*> rectangles;

};

