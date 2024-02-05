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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		std::cout << "Opening inventory" << "\n";
	}
}

//Rectangle Functions
void Inventory::initRects()
{
	this->rectangles["INV_BORDER"] = new Rectangle(322, 131, 890, 400, sf::Color::Transparent,
		sf::Color::White, 1.f);
}

void Inventory::renderRects(sf::RenderTarget* target)
{
	for (auto& it : this->rectangles) {
		it.second->render(target);
	}
}