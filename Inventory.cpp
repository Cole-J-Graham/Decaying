#include "Inventory.h"
//Constructors and Desconstructors
Inventory::Inventory()
{
	//Init
	this->initItems();

	this->GUI = new PlayerGUI();
}

Inventory::~Inventory()
{
	delete this->GUI;

	//Deconstruct Items
	auto it = this->items.begin();
	for (it = this->items.begin(); it != this->items.end(); ++it) {
		delete it->second;
	}
}

//Core Functions
void Inventory::render(sf::RenderTarget* target)
{
	this->renderMapItems(target);
	this->GUI->render(target);
	this->renderInventoryItems(target);
}

void Inventory::update(sf::Sprite sprite, const sf::Vector2f mousePos)
{
	for (auto& it : this->items) {
		it.second->update(sprite, mousePos);
	}
}

void Inventory::checkForInput()
{
	elapsed = timer.getElapsedTime();
	if (elapsed.asSeconds() >= 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && GUI->getRectangles()["INV_BORDER"]->getHidden()) {
			for (auto& it : GUI->getRectangles()) {
				it.second->setShown();
			}
			for (auto& it : this->items) {
				it.second->setShown();
			}
			this->timer.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !GUI->getRectangles()["INV_BORDER"]->getHidden()) {
			for (auto& it : GUI->getRectangles()) {
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
void Inventory::addItem(Item* item)
{
	item->getInInventory() = true;
	this->inventory_items.push_back(item);
}

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
void Inventory::pickupItem()
{
	for (auto& it : this->items) {
		if (it.second->isInteracted()) {
			this->addItem(it.second);
		}
	}
}

void Inventory::initItems()
{
	this->items["Staff"] = new Item(250.f, 250.f, 0.f, 100.f, "Staff",
		"Zin's staff, useful for a\nvariety of tasks such as self\ndefense.\n\nWEAPON\nCOMMON", "Assets/Items/zin_staff.png", true, false,
		WEAPON, COMMON);
	this->items["Eternal Dust"] = new Item(400.f, 400.f, 0.f, 100.f, "Eternal Dust",
		"A strange unending pile of\ndust, seeming capable\nof replenishing itself\n\nRELIC\nUNIQUE", "Assets/Items/eternal_dust.png", true, false,
		RELIC, UNIQUE);
}

void Inventory::renderInventoryItems(sf::RenderTarget* target)
{
	int x = 50;
	for (auto& it : this->inventory_items) {
		if (it->getInInventory()) {
			it->setInventoryPosition(x += 50, 100);
			it->render(target);
		}
	}
}

void Inventory::renderMapItems(sf::RenderTarget* target)
{
	for (auto& it : this->items) {
		if (!it.second->getInInventory()) {
			it.second->render(target);
		}
	}
}