#include "Inventory.h"
//Constructors and Desconstructors
Inventory::Inventory()
{
	//Init
	this->initItems();
	this->initWeapons();
	this->initRelics();

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
	//Update Items
	for (auto& it : this->items) {it.second->update(sprite, mousePos);}
	//Update Weapons
	for (auto& it : this->weapons) {it.second->update(sprite, mousePos);}
	//Update Relics
	for (auto& it : this->relics) {it.second->update(sprite, mousePos);}

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
	if (elapsed.asSeconds() >= 0.2) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && GUI->getRectangles()["INV_BORDER"]->getHidden()) {
			for (auto& it : GUI->getRectangles()) {
				it.second->setShown();
				GUI->getRectangles()["SKILLS_MENU"]->setString(skills->displayStats());
			}
			//Show all items
			for (auto& it : this->items) { it.second->setShown(); }
			for (auto& it : this->weapons) { it.second->setShown(); }
			for (auto& it : this->relics) { it.second->setShown(); }
			this->timer.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !GUI->getRectangles()["INV_BORDER"]->getHidden()) {
			for (auto& it : GUI->getRectangles()) { it.second->setHidden(); }
			//Hide all items
			for (auto& it : this->items) { it.second->setHidden(); }
			for (auto& it : this->weapons) { it.second->setHidden(); }
			for (auto& it : this->relics) { it.second->setHidden(); }
			this->timer.restart();
		}
	}
}

//Inventory Functions
void Inventory::addItem(Item* item)
{
	item->setHidden();
	item->inInventory() = true;
	this->inventory_items.push_back(item);
}

void Inventory::addWeapon(Weapon* weapon)
{
	weapon->setHidden();
	weapon->inInventory() = true;
	this->inventory_weapons.push_back(weapon);
}

void Inventory::addRelic(Relic* relic)
{
	relic->setHidden();
	relic->inInventory() = true;
	this->inventory_relics.push_back(relic);
}

void Inventory::deleteItem(Item* item)
{
	//TEST TO SEE IF FUNCTIONAL
	this->inventory_items.emplace_back(item);
	this->inventory_items.pop_back();
	delete item;
}

//Item Functions
void Inventory::initItems()
{

}

void Inventory::pickupItem()
{
	//Pickup Generic Items
	for (auto& it : this->items) {
		if (it.second->isInteracted()) { this->addItem(it.second); }
	}
	//Pickup weapons
	for (auto& it : this->weapons) {
		if (it.second->isInteracted()) { this->addWeapon(it.second); }
	}
	//Pickup relics
	for (auto& it : this->relics) {
		if (it.second->isInteracted()) { this->addRelic(it.second); }
	}
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
	for (auto& it : this->inventory_weapons) {
		if (it->inInventory()) {
			it->setInventoryPosition(x += 50, 100);
			it->render(target);
		}
	}
	for (auto& it : this->inventory_relics) {
		if (it->inInventory()) {
			it->setInventoryPosition(x += 50, 100);
			it->render(target);
		}
	}
	
}

void Inventory::renderMapItems(sf::RenderTarget* target)
{
	//Render Items on map
	for (auto& it : this->items) {
		if (!it.second->inInventory()) {
			it.second->render(target);
		}
	}
	//Render Weapons on map
	for (auto& it : this->weapons) {
		if (!it.second->inInventory()) {
			it.second->render(target);
		}
	}
	//Render Relics on map
	for (auto& it : this->relics) {
		if (!it.second->inInventory()) {
			it.second->render(target);
		}
	}
}

//Weapon Functions
void Inventory::initWeapons()
{
	this->weapons["Staff"] = new Weapon(250.f, 250.f, "Staff",
		"Zin's staff, useful for a\nvariety of tasks such as self\ndefense.\n\nWEAPON\nCOMMON", "Assets/Items/zin_staff.png",
		10.f, 1.f);
}

//relic Functions
void Inventory::initRelics()
{
	this->relics["Eternal Dust"] = new Relic(400.f, 400.f, "Eternal Dust",
		"A strange unending pile of\ndust, seeming capable\nof replenishing itself\n\nRELIC\nUNIQUE", "Assets/Items/eternal_dust.png",
		100.f);
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