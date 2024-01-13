#pragma once
#include<SFML/Graphics.hpp>

class TileMap
{
public:
	//Constructors and Destructors
	TileMap();
	~TileMap();

	//Core Functions
	void loadMap(std::vector<std::vector<sf::Sprite>>& map, sf::Texture& mapSpriteSheet, std::vector<std::vector<int>>& tileData);
	void detectCollision(std::vector<std::vector<sf::Sprite>>& colSprite, std::vector<std::vector<int>>& inData, sf::Sprite& inSprite);

	//Load Functions
	void loadForest(sf::RenderTarget& target, sf::Sprite& sprite);
	void loadCollisionMap(sf::RenderTarget& target, sf::Sprite& sprite);

	//State Fucntions
	void update();
	void render(sf::RenderTarget& target);

	//Assets
	void loadAssets();

private:
	std::vector<std::vector<sf::Sprite>> tileMap;

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

