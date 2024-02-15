#pragma once
#include"Item.h"
#include"Skills.h"
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
	void checkForInput();

	//Inventory Functions
	void addItem(Item* item);
	void deleteItem(std::string input);

	//Item Functions
	void pickupItem();
	void initItems();
	void renderInventoryItems(sf::RenderTarget* target);
	void renderMapItems(sf::RenderTarget* target);

	//Accessor Functions
	void addStaff() { this->addItem(this->items["Staff"]); };
	void addStiff() { this->addItem(this->items["Stiff"]); };
	std::map<std::string, Item*> getItems() { return this->items; };

private:
	PlayerGUI* GUI;

	std::string item_name;
	sf::Clock timer;
	sf::Time elapsed;
	
	std::map<std::string, Item*> items;
	std::vector<Item*> inventory_items;

};

