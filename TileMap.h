#pragma once
#include<SFML/Graphics.hpp>

class TileMap
{
public:
	//Constructors and Destructors
	TileMap();
	TileMap(unsigned width, unsigned height, sf::Texture& tile_sheet, unsigned tile_size);
	~TileMap();

	//Core Functions
	void loadingOnTile(std::vector<std::vector<sf::Sprite>>& inSprite, sf::Texture& spriteSheet, std::vector<std::vector<int>>& tileData);
	void loadForest(sf::RenderTarget& target);
	void loadCollisionMap(sf::RenderTarget& target, sf::Sprite& sprite);

	//State Fucntions
	void update();
	void render(sf::RenderTarget& target);

	//Assets
	void loadAssets();

private:
	std::vector<std::vector<sf::Sprite>> tileMap;
	std::vector<std::vector<sf::RectangleShape>> collisionMap;
	std::vector<std::vector<int>> collisionData;

	//Map data
	std::vector<std::vector<int>> forest;

	sf::Texture tileSheet;
	unsigned tileSize;

	float gridSizeF;
	int col;
	int row;
	int sheetX;
	int sheetY;

	sf::Texture forestSheet;
};

