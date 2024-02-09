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
	void update(const sf::Vector2f mousePos);
	void checkForInput();

	//Inventory Functions
	//void addItem(Item* item);
	void deleteItem(std::string input);

	//Item Functions
	void initItems();
	void renderItems(sf::RenderTarget* target);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

private:

	std::string item_name;
	sf::Clock timer;
	sf::Time elapsed;

	std::map<std::string, Rectangle*> rectangles;
	std::map<std::string, Item*> items;

};

