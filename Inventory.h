#pragma once
#include"EquipSlot.h"
#include<map>
class Inventory
{
public:
	//Constructors and Desconstructors
	Inventory();
	~Inventory();

	//Core Functions
	void render(sf::RenderTarget* target);
	void update(sf::Sprite sprite, const sf::Vector2f mousePos);

	//Input Functions
	void checkForInput();
	void checkForTab();

	//Inventory Functions
	void addItem(Item* item);
	void deleteItem(Item* item);

	//Item Functions
	void pickupItem();
	void initItems();
	void renderInventoryItems(sf::RenderTarget* target);
	void renderMapItems(sf::RenderTarget* target);

	//Equip Slot Functions
	void initSlots();
	void equipItem(Item* item);

	//Accessor Functions
	void addStaff() { this->addItem(this->items["Staff"]); };
	void addStiff() { this->addItem(this->items["Stiff"]); };
	std::map<std::string, Item*> getItems() { return this->items; };

private:
	PlayerGUI* GUI;
	Skills* skills;

	std::string item_name;
	sf::Clock timer;
	sf::Time elapsed;
	
	std::map<std::string, Item*> items;
	std::vector<Item*> inventory_items;

	std::map<std::string, Item*> equip_slots;

};

