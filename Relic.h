#pragma once
#include"Item.h"
class Relic : virtual public Item
{
public:
	//Constructors and Destructors
	Relic(float x, float y, std::string item_name,
		std::string item_description, std::string texture_input,
		float modifiers);
	~Relic();

	//Core Functions

	//Item Functions
	void initRelic();
	void render(sf::RenderTarget* target);
	void moveItem(sf::Vector2f move);
	void update(const sf::Sprite sprite, const sf::Vector2f mousePos);
	void setMapPosition(sf::Vector2f position);

	//Accessors
	const bool isInteracted() const { return this->item->isInteracted(); }

	//Setters
	bool& inInventory() { return this->item->inInventory(); };
	void setInventoryPosition(float x, float y) { this->item->setInventoryPosition(x, y); };
	bool& setHidden() { return this->item->setHidden() = true; };
	bool& setShown() { return this->item->setShown() = false; };

private:
	Item* item;
	sf::Vector2f position;

	bool interacted;
	float modifiers;

};