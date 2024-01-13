#include "TileMap.h"
//Constructors and Destructors
TileMap::TileMap()
{
	//Core Variables
	this->gridSizeF = 64.f;
	this->col = 16;
	this->row = 16;
	this->sheetX;
	this->sheetY;

	//Assets
	this->loadAssets();
}

TileMap::~TileMap()
{

}

//Core Functions
void TileMap::loadMap(std::vector<std::vector<sf::Sprite>>& map, sf::Texture& mapSpriteSheet, std::vector<std::vector<int>>& tileData)
{
	//Draw a specific set texture tile based on which input is recieved from a tilemap vector
	map.resize(row, std::vector<sf::Sprite>(col));
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			map[x][y].setScale(sf::Vector2f(4.0f, 4.0f));
			map[x][y].setPosition(x * gridSizeF + 440, y * gridSizeF);
			map[x][y].setTexture(mapSpriteSheet);
			if (tileData[x][y] == 0) {
				this->sheetX = 0;
				map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
			else if (tileData[x][y] == 1) {
				this->sheetX = 16;
				map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
			else if (tileData[x][y] == 2) {
				this->sheetX = 32;
				map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
			else if (tileData[x][y] == 3) {
				this->sheetX = 48;
				map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
		}
	}
}

void TileMap::detectCollision(std::vector<std::vector<sf::Sprite>>& colSprite, std::vector<std::vector<int>>& inData, sf::Sprite& inSprite)
{
	//Collision Function
	for (int x = 0; x < colSprite.size(); x++) {
		for (int y = 0; y < colSprite.size(); y++) {
			if (inSprite.getGlobalBounds().intersects(colSprite[x][y].getGlobalBounds())) {
				if (inData[x][y] == 1) {
					sf::FloatRect playerBounds = inSprite.getGlobalBounds();
					sf::FloatRect wallBounds = colSprite[x][y].getGlobalBounds();
					sf::FloatRect area;
					if (inSprite.getGlobalBounds().intersects(colSprite[x][y].getGlobalBounds(), area))
					{
						// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
						if (area.width > area.height)
						{
							if (area.contains({ area.left, inSprite.getPosition().y }))
							{
								// Up side crash
								inSprite.setPosition({ inSprite.getPosition().x, inSprite.getPosition().y + area.height });
							}
							else
							{
								// Down side crash
								inSprite.setPosition({ inSprite.getPosition().x, inSprite.getPosition().y - area.height });
							}
						}
						else if (area.width < area.height)
						{
							if (area.contains({ inSprite.getPosition().x + inSprite.getGlobalBounds().width - 1.f, area.top + 1.f }))
							{
								//Right side crash
								inSprite.setPosition({ inSprite.getPosition().x - area.width, inSprite.getPosition().y });
							}
							else
							{
								//Left side crash
								inSprite.setPosition({ inSprite.getPosition().x + area.width, inSprite.getPosition().y });
							}
						}
					}
				}
			}
		}
	}
}

//Load Functions
void TileMap::loadForest(sf::RenderTarget& target, sf::Sprite& sprite)
{
	//Create Level
	std::vector<std::vector<int>> forest{
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

	//Resize the 2d vector to rows and columns of a specific size
	this->loadMap(tileMap, forestSheet, forest);
	this->detectCollision(tileMap, forest, sprite);
	//Draw the 2d vector aka tilemap
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			target.draw(tileMap[x][y]);
		}
	}
}

//State Functions
void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{

}

//Assets
void TileMap::loadAssets()
{
	this->forestSheet.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/landSpriteSheet.png");
}