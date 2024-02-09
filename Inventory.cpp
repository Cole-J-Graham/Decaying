#include "Inventory.h"
//Constructors and Desconstructors
Inventory::Inventory()
{
	//Init
	this->initRects();
	this->initItems();
}

Inventory::~Inventory()
{
	//Deconstruct Rectangles
	auto ir = this->rectangles.begin();
	for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
		delete ir->second;
	}

	//Deconstruct Items
	auto it = this->items.begin();
	for (it = this->items.begin(); it != this->items.end(); ++it) {
		delete it->second;
	}
}

//Core Functions
void Inventory::render(sf::RenderTarget* target)
{
	this->renderRects(target);
	this->renderItems(target);
}

void Inventory::update(const sf::Vector2f mousePos)
{
	for (auto& it : this->items) {
		it.second->updateInventory(mousePos);
	}
}

void Inventory::checkForInput()
{
	elapsed = timer.getElapsedTime();
	if (elapsed.asSeconds() >= 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && this->rectangles["INV_BORDER"]->getHidden()) {
			for (auto& it : this->rectangles) {
				it.second->setShown();
			}
			for (auto& it : this->items) {
				it.second->setShown();
			}
			this->timer.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !this->rectangles["INV_BORDER"]->getHidden()) {
			for (auto& it : this->rectangles) {
				it.second->setHidden();
			}
			for (auto& it : this->items) {
				it.second->setHidden();
			}
			this->timer.restart();
		}
	}
}

//Inventory Functions
//void Inventory::addItem(Item* item)
//{
//	this->items.emplace(item);
//}

void Inventory::deleteItem(std::string input)
{
	std::map<std::string, Item*>::iterator itr = items.find(input);
	if (itr != items.end())
	{
		// found it - delete it
		delete itr->second;
		items.erase(itr);
	}
}

//Item Functions
void Inventory::initItems()
{
	this->items["Staff"] = new Item("Staff", "Assets/Items/zin_staff.png", true);
}

void Inventory::renderItems(sf::RenderTarget* target)
{
	for (auto& it : this->items) {
		it.second->render(target);
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