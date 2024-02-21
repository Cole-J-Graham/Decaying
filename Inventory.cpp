#include "Inventory.h"
//Constructors and Desconstructors
Inventory::Inventory()
{
	//Init
	this->initItems();

	this->skills = new Skills();
	this->GUI = new PlayerGUI();
}

Inventory::~Inventory()
{
	delete this->skills;
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
	GUI->render(target);
	this->renderInventoryItems(target);
}

void Inventory::update(sf::Sprite sprite, const sf::Vector2f mousePos)
{
	for (auto& it : this->items) {
		it.second->update(sprite, mousePos);
	}

	this->skills->update();
}

//Input Functions
void Inventory::checkForInput()
{
	this->checkForTab();
}

void Inventory::checkForTab()
{
	elapsed = timer.getElapsedTime();
	if (elapsed.asSeconds() >= 0.5) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && GUI->getRectangles()["INV_BORDER"]->getHidden()) {
			for (auto& it : GUI->getRectangles()) {
				it.second->setShown();
				GUI->getRectangles()["SKILLS_MENU"]->setString(skills->displayStats());
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
	item->inInventory() = true;
	this->inventory_items.push_back(item);
}

void Inventory::deleteItem(Item* item)
{
	//TEST TO SEE IF FUNCTIONAL
	this->inventory_items.emplace_back(item);
	this->inventory_items.pop_back();
	delete item;
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
	this->items["Staff"] = new Item(250.f, 250.f, "Staff",
		"Zin's staff, useful for a\nvariety of tasks such as self\ndefense.\n\nWEAPON\nCOMMON", "Assets/Items/zin_staff.png", true, false,
		WEAPON, COMMON);
	this->items["Eternal Dust"] = new Item(400.f, 400.f, "Eternal Dust",
		"A strange unending pile of\ndust, seeming capable\nof replenishing itself\n\nRELIC\nUNIQUE", "Assets/Items/eternal_dust.png", true, false,
		RELIC, UNIQUE);
}

void Inventory::renderInventoryItems(sf::RenderTarget* target)
{
	int x = 0;
	for (auto& it : this->inventory_items) {
		if (it->inInventory()) {
			it->setInventoryPosition(x += 50, 100);
			it->render(target);
		}
	}
}

void Inventory::renderMapItems(sf::RenderTarget* target)
{
	for (auto& it : this->items) {
		if (!it.second->inInventory()) {
			it.second->render(target);
		}
	}
}

//Equip Slot Functions
void Inventory::initSlots()
{
	this->equip_slots["SLOT_MAINHAND"];
	this->equip_slots["SLOT_BACK"];
}

void Inventory::equipItem(Item* item)
{
	if (this->equip_slots["SLOT_MAINHAND"]->getGlobalBounds().intersects(item->getGlobalBounds())) {
		if (item->inInventory()) {
			//DO SOMETHING
		}
	}
}