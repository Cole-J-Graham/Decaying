#pragma once
#include<SFML/Graphics.hpp>
#include"iostream"
enum item_states { ITM_IDLE = 0, ITM_COLLIDING, ITM_INTERACTED };
class Item
{

public:
	//Constructors and Destructors
	Item();
	~Item();

	//Core Functions
	void render(sf::RenderTarget* target);
	void update(const sf::Vector2f player_pos);

	//Accessors
	const bool isInteracted() const;
	const bool isColliding() const;

	//Assets
	void loadAssets();

private:

	sf::Sprite item;
	bool colliding;
	short unsigned item_state;
};