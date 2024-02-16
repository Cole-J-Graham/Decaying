#pragma once
#include"Rectangle.h"
class PlayerGUI
{
public:
	//Constructors and Deconstructors
	PlayerGUI();
	~PlayerGUI();

	//Core Functions
	void render(sf::RenderTarget* target);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

	std::map<std::string, Rectangle*>& getRectangles() { return this->rectangles; };

private:
	std::map<std::string, Rectangle*> rectangles;

};

