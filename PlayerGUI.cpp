#include "PlayerGUI.h"
//Constructors and Deconstructors
PlayerGUI::PlayerGUI()
{
	this->initRects();
	this->initButtons();
	font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
}

PlayerGUI::~PlayerGUI()
{
	//Deconstruct Rectangles
	auto ir = this->rectangles.begin();
	for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
		delete ir->second;
	}

	//Deconstruct Buttons
	auto ib = this->buttons.begin();
	for (ib = this->buttons.begin(); ib != this->buttons.end(); ++ib) {
		delete ib->second;
	}
}

//Core Functions
void PlayerGUI::update(const sf::Vector2f mousePos)
{
	this->updateButtons(mousePos);
}

void PlayerGUI::render(sf::RenderTarget* target)
{
	this->renderRects(target);
	this->renderButtons(target);
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

//Button Functions
void PlayerGUI::initButtons()
{
	this->buttons["RELIC_POUCH"] = new Button(350, 702, 100, 50, font,
		"relic\nPouch", sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), 
		sf::Color(20, 20, 20, 70), true);
}

void PlayerGUI::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void PlayerGUI::updateButtons(const sf::Vector2f mousePos)
{
	for (auto& it : this->buttons) {
		it.second->update(mousePos);
	}
}