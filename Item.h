#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
enum item_states { ITM_UNTOUCHED = 0, ITM_COLLIDING, ITM_INTERACTED };
enum item_inv_states { ITM_IDLE = 0, ITM_HOVER, ITM_ACTIVE };
class Item
{

public:
	//Constructors and Destructors
	Item(std::string item_name, std::string texture_input, bool hidden);
	~Item();

	//Core Functions
	void render(sf::RenderTarget* target);
	void update(const sf::Vector2f player_pos);
	void updateInventory(const sf::Vector2f mousePos);

	//Accessors
	const bool isInteracted() const;
	const bool isColliding() const;
	const bool isPressed() const;
	const bool isHovered() const;

	//Setters
	bool& setHidden() { return this->hidden = true; };
	bool& setShown() { return this->hidden = false; };

	//Assets
	void loadAsset();

private:

	bool hidden;
	sf::Sprite item;
	sf::Texture item_texture;
	std::string item_name;
	std::string texture_input;
	float x;
	float y;
	bool colliding;
	short unsigned item_state;
	short unsigned item_inv_state;
};