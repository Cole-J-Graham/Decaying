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
	void loadingOnTile(std::vector<std::vector<sf::Sprite>>& inSprite, std::vector<std::vector<int>> tiles, sf::Texture& tex1, sf::Texture& tex2, sf::Texture& tex3, sf::Texture& tex4);
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

	sf::Texture forestTile1;
	sf::Texture forestTile2;
	sf::Texture forestTile3;
	sf::Texture forestTile4;
};

