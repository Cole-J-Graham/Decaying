#include "Inventory.h"
//Constructors and Desconstructors
Inventory::Inventory()
{
	//Init
	this->initRects();
}

Inventory::~Inventory()
{
	//Deconstruct Rectangles
	auto ir = this->rectangles.begin();
	for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
		delete ir->second;
	}
}

//Core Functions
void Inventory::render(sf::RenderTarget* target)
{
	this->renderRects(target);
}

void Inventory::checkForInput()
{
	elapsed = timer.getElapsedTime();
	if (elapsed.asSeconds() >= 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && this->rectangles["INV_BORDER"]->getHidden()) {
			this->rectangles["INV_BORDER"]->setShown();
			this->timer.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !this->rectangles["INV_BORDER"]->getHidden()) {
			this->rectangles["INV_BORDER"]->setHidden();
			this->timer.restart();
		}
	}
}

//Rectangle Functions
void Inventory::initRects()
{
	this->rectangles["INV_BORDER"] = new Rectangle(100, 100, 400, 600, sf::Color::Black,
		sf::Color::White, 8.f, true);
}

void Inventory::renderRects(sf::RenderTarget* target)
{
	for (auto& it : this->rectangles) {
		it.second->render(target);
	}
}