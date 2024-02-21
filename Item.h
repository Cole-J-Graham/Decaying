#pragma once
#include"PlayerGUI.h"
#include"Skills.h"
#include<map>
#include<iostream>
#include<string>
//Item States
enum item_states { ITM_UNTOUCHED = 0, ITM_COLLIDING, ITM_INTERACTED };
enum item_inv_states { ITM_IDLE = 0, ITM_HOVER, ITM_ACTIVE };
//Item Definitions
enum item_type { GENERIC, WEAPON, RELIC };
enum item_rarity {COMMON, UNCOMMON, RARE, UNIQUE};

class Item : public sf::Sprite
{

public:
	//Constructors and Destructors
	Item(float x, float y, std::string item_name, std::string item_description, 
		std::string texture_input, bool hidden, bool in_inventory, enum item_type, 
		enum item_rarity);
	~Item();

	//Core Functions
	void render(sf::RenderTarget* target);
	void update(sf::Sprite sprite, const sf::Vector2f mousePos);
	void updateMapItems(sf::Sprite sprite);
	void updateInventory(const sf::Vector2f mousePos);

	//Modifiers
	void setInventoryPosition(float x, float y);
	void setMapPosition(sf::Vector2f position);
	void moveItem(sf::Vector2f move);

	//Accessors
	const bool isInteracted() const;
	const bool isColliding() const;
	const bool isPressed() const;
	const bool isHovered() const;

	//Rectangle Functions
	void renderRects(sf::RenderTarget* target);
	void initRects();

	//Setters
	bool& setHidden() { return this->hidden = true; };
	bool& setShown() { return this->hidden = false; };
	bool& inInventory() { return this->in_inventory; };

	//Assets
	void loadAsset();

private:

	std::map<std::string, Rectangle*> rectangles;

	sf::Sprite item;
	sf::Texture item_texture;
	std::string item_description;
	std::string item_name;
	std::string texture_input;

	float x;
	float y;
	bool hidden;
	bool in_inventory;
	bool colliding;
	short unsigned item_state;
	short unsigned item_inv_state;
	int sheetx;
	int sheety;
};