#pragma once
#include"Button.h"
#include"Rectangle.h"
class PlayerGUI
{
public:
	//Constructors and Deconstructors
	PlayerGUI();
	~PlayerGUI();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

	//Button Functions
	void initButtons();
	void renderButtons(sf::RenderTarget* target);
	void updateButtons(const sf::Vector2f mousePos);

	std::map<std::string, Rectangle*>& getRectangles() { return this->rectangles; };
	std::map<std::string, Button*>& getButtons() { return this->buttons; };

private:
	sf::Font font;
	std::map<std::string, Rectangle*> rectangles;
	std::map<std::string, Button*> buttons;

};

