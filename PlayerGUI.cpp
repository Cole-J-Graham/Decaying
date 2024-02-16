#include "PlayerGUI.h"
//Constructors and Deconstructors
PlayerGUI::PlayerGUI()
{
	this->initRects();
}

PlayerGUI::~PlayerGUI()
{
	//Deconstruct Rectangles
	auto ir = this->rectangles.begin();
	for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
		delete ir->second;
	}
}

//Core Functions
void PlayerGUI::render(sf::RenderTarget* target)
{
	this->renderRects(target);
}

//Rectangle Functions
void PlayerGUI::initRects()
{
	this->rectangles["INV_BORDER"] = new Rectangle(50, 100, 400, 600, sf::Color::Black,
		sf::Color::White, 1.f, true);
	this->rectangles["SKILLS_MENU"] = new Rectangle(1650, 100, 200, 600, sf::Color::Black,
		sf::Color::White, 1.f, "example", 16, true);

	this->rectangles["EQUIPSLOT_MAINHAND"] = new Rectangle(50, 725, 50, 50, sf::Color::Black,
		sf::Color::White, 1.f, true);
	this->rectangles["EQUIPSLOT_OFFHAND"] = new Rectangle(110, 725, 50, 50, sf::Color::Black,
		sf::Color::White, 1.f, true);
	this->rectangles["EQUIPSLOT_OUTFIT"] = new Rectangle(170, 725, 50, 50, sf::Color::Black,
		sf::Color::White, 1.f, true);
	this->rectangles["EQUIPSLOT_HAT"] = new Rectangle(170, 776, 50, 50, sf::Color::Black,
		sf::Color::White, 1.f, true);
}

void PlayerGUI::renderRects(sf::RenderTarget* target)
{
	for (auto& it : this->rectangles) {
		it.second->render(target);
	}
}