#pragma once
#include"Item.h"
#include"Rectangle.h"
#include<map>
class Inventory
{
public:
	//Constructors and Desconstructors
	Inventory();
	~Inventory();

	//Core Functions
	void render(sf::RenderTarget* target);
	void update(const sf::Vector2f player_pos, const sf::Vector2f mousePos);
	void checkForInput();

	//Inventory Functions
	void addItem(Item* item);
	void deleteItem(std::string input);

	//Item Functions
	void pickupItem();
	void initItems();
	void renderInventoryItems(sf::RenderTarget* target);
	void renderMapItems(sf::RenderTarget* target);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

	//Accessor Functions
	void addStaff() { this->addItem(this->items["Staff"]); };
	void addStiff() { this->addItem(this->items["Stiff"]); };
	std::map<std::string, Item*> getItems() { return this->items; };

private:

	std::string item_name;
	sf::Clock timer;
	sf::Time elapsed;

	std::map<std::string, Rectangle*> rectangles;
	
	std::map<std::string, Item*> items;
	std::vector<Item*> inventory_items;

};

