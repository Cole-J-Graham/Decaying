#pragma once
#include"Sprite.h"
#include<SFML/Graphics.hpp>
#include<map>
class CollisionModule
{
public:
	//Constructors and Destructors
	CollisionModule();
	~CollisionModule();

	//Core Functions
	void setMapCollision(sf::Sprite& character, 
		std::vector<std::vector<sf::Sprite>>& map, 
		std::vector<std::vector<int>> mapdata, sf::FloatRect area,
		int col, int row);
	typedef std::map<std::string, std::string> map_type;
	void addItemToMapCollision(int& x, int& y, Sprite& sprite);

private:
	bool colliding;
	const sf::Vector2f mapPosition;

};

