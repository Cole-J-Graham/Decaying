#pragma once
#include"EquipSlot.h"
#include"Relic.h"
#include"Weapon.h"
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
	void addWeapon(Weapon* weapon);
	void addRelic(Relic* relic);
	void deleteItem(Item* item);

	//Item Functions
	void pickupItem();
	void initItems();
	void renderInventoryItems(sf::RenderTarget* target);
	void renderMapItems(sf::RenderTarget* target);

	//Weapon Functions
	void initWeapons();

	//Relic Functions
	void initRelics();

	//Equip Slot Functions
	void initSlots();
	void equipItem(Item* item);

	//Accessor Functions
	std::map<std::string, Item*> getItems() { return this->items; };
	std::map<std::string, Weapon*> getWeapons() { return this->weapons; };
	std::map<std::string, Relic*> getRelics() { return this->relics; };

private:
	PlayerGUI* GUI;
	Skills* skills;

	std::string item_name;
	sf::Clock timer;
	sf::Time elapsed;
	
	std::map<std::string, Item*> items;
	std::map<std::string, Weapon*> weapons;
	std::map<std::string, Relic*> relics;

	std::vector<Item*> inventory_items;
	std::vector<Weapon*> inventory_weapons;
	std::vector<Relic*> inventory_relics;

	std::map<std::string, Item*> equip_slots;

};

