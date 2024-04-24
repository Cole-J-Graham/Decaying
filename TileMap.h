#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"fstream"
#include<random>
#include<map>
#include"Tile.h"
//Components
#include"CombatComponent.h"

class TileMap
{
public:
	//Constructors and Destructors
	TileMap(float x, float y, int col, int row, float grid_size_f, sf::Texture& tile_sheet,
		std::string map_data_string);
	~TileMap();

	//Core Functions
	void loadMap(sf::Texture& tile_sheet);
	void loadMapData(std::string input);

	//Detection Functions
	void detectMap(Character* character, CombatComponent* combat, sf::FloatRect playerPos);
	void detectCollision(CombatComponent* combat, sf::FloatRect playerPos);
	void detectEntrance(sf::FloatRect playerPos);

	//State Fucntions
	void render(sf::RenderTarget* target);

	//Movement Functions
	void detectMovement(Character* character, CombatComponent* combat);

	//Item Functions
	void moveItems(Character* character, CombatComponent* combat);

	const bool getCollidingEntrance()& { return this->colliding_entrance; };

private:

	//Core Map
	std::vector<std::vector<Tile>> tile_map;
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
	bool colliding;
	bool colliding_entrance;
	int current_map_data;

	//Map data
	sf::FloatRect area;
	std::string map_data_string;
	std::ifstream map_data;
	std::vector<std::vector<int>> tile_map_data;
};

