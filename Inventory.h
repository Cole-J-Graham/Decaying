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
	void checkForInput();

	//Item Functions
	void addItem(Item* item);
	void deleteItem();

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

private:
	sf::Clock timer;
	sf::Time elapsed;

	std::map<std::string, Rectangle*> rectangles;
	std::vector<Item*> item_vector;

};

