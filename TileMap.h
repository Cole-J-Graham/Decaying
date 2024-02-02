#pragma once
#include<SFML/Graphics.hpp>
#include"iostream"

class TileMap
{
public:
	//Constructors and Destructors
	TileMap(float x, float y, int col, int row, float grid_size_f);
	~TileMap();

	//Core Functions
	void loadMap(sf::Texture& tile_sheet);
	void detectCollision(sf::Sprite& in_sprite);

	//State Fucntions
	void render(sf::RenderTarget* target);

private:
	//Core Map
	std::vector<std::vector<sf::Sprite>> tile_map;
	sf::Texture tile_sheet;

	//Core Map Variables
	unsigned tileSize;
	float grid_size_f;
	float x;
	float y;
	int col;
	int row;
	int sheetX;
	int sheetY;

	//Map data
	std::vector<std::vector<int>> tile_map_data {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 3, 3, 0, 0, 0, 1},
		{1, 1, 1, 0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 0, 3, 1},
		{1, 1, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 1},
		{1, 0, 3, 3, 3, 0, 2, 0, 0, 0, 3, 3, 0, 3, 0, 1},
		{1, 0, 0, 3, 3, 0, 0, 0, 3, 3, 3, 3, 0, 3, 3, 1},
		{1, 0, 3, 2, 0, 3, 0, 3, 3, 3, 0, 0, 3, 0, 0, 1},
		{1, 0, 3, 0, 2, 0, 0, 3, 3, 0, 0, 3, 0, 3, 0, 1},
		{1, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 0, 3, 0, 0, 1},
		{1, 0, 0, 0, 3, 3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1},
		{1, 3, 0, 3, 3, 0, 3, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 3, 3, 1},
		{1, 1, 0, 0, 3, 3, 0, 3, 0, 0, 3, 0, 0, 0, 3, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 3, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};
};

