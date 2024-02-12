#pragma once
#include"Rectangle.h"
#include<map>
#include<iostream>
#include<string>
enum item_states { ITM_UNTOUCHED = 0, ITM_COLLIDING, ITM_INTERACTED };
enum item_inv_states { ITM_IDLE = 0, ITM_HOVER, ITM_ACTIVE };
class Item
{

public:
	//Constructors and Destructors
	Item(float map_x, float map_y, float inv_x, float inv_y, std::string item_name,
		std::string item_description, std::string texture_input, bool hidden, bool in_inventory);
	~Item();

	//Core Functions
	void render(sf::RenderTarget* target);
	void update(sf::Sprite sprite, const sf::Vector2f mousePos);
	void updateMapItems(sf::Sprite sprite);
	void updateInventory(const sf::Vector2f mousePos);

	//Modifiers
	void setPosition(float x, float y);
	void setMapPosition();
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
	bool& getInInventory() { return this->in_inventory; };

	//Assets
	void loadAsset();

private:

	std::map<std::string, Rectangle*> rectangles;

	sf::Sprite item;
	sf::Texture item_texture;
	std::string item_description;
	std::string item_name;
	std::string texture_input;

	float inv_x;
	float inv_y;
	float map_x;
	float map_y;
	bool hidden;
	bool in_inventory;
	bool colliding;
	short unsigned item_state;
	short unsigned item_inv_state;
	int sheetx;
	int sheety;
};