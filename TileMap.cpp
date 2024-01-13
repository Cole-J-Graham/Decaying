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
void TileMap::loadingOnTile(std::vector<std::vector<sf::Sprite>>& inSprite, sf::Texture& spriteSheet, std::vector<std::vector<int>>& tileData)
{
	//Draw a specific set texture tile based on which input is recieved from a tilemap vector
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			inSprite[x][y].setTexture(spriteSheet);
			if (tileData[x][y] == 0) {
				this->sheetX = 0;
				inSprite[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
			else if (tileData[x][y] == 1) {
				this->sheetX = 16;
				inSprite[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
			else if (tileData[x][y] == 2) {
				this->sheetX = 32;
				inSprite[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
			else if (tileData[x][y] == 3) {
				this->sheetX = 48;
				inSprite[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
		}
	}
}

void TileMap::loadForest(sf::RenderTarget& target)
{
	/*Inserted map data must change to allow for mass produced levels with varying collision
	based off of what is needed for the game which will allow for scalability...*/
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
	tileMap.resize(row, std::vector<sf::Sprite>(col));
	//Set attributes for the 2d vector
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			tileMap[x][y].setScale(sf::Vector2f(4.0f, 4.0f));
			tileMap[x][y].setPosition(x * gridSizeF + 440, y * gridSizeF);
			loadingOnTile(tileMap, forestSheet, forest);
		}
	}
	//Draw the 2d vector aka tilemap
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			target.draw(tileMap[x][y]);
		}
	}
}

void TileMap::loadCollisionMap(sf::RenderTarget& target, sf::Sprite& sprite)
{
	std::vector<std::vector<int>> collisionData = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	//Resize the 2d vector to rows and columns of a specific size
	collisionMap.resize(row, std::vector<sf::RectangleShape>(col));
	//Set attributes for the 2d vector
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			collisionMap[x][y].setScale(sf::Vector2f(0.4f, 0.4f));
			collisionMap[x][y].setPosition(x * gridSizeF + 440, y * gridSizeF);
		}
	}
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			collisionMap[x][y].setSize(sf::Vector2f(160.f, 160.f));
			if (collisionData[x][y] == 0) {
				collisionMap[x][y].setFillColor(sf::Color::Transparent);
			}
			else if (collisionData[x][y] == 1) {
				collisionMap[x][y].setFillColor(sf::Color::Transparent);
			}
		}
	}

	//Draw the 2d vector aka tilemap
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			target.draw(collisionMap[x][y]);
		}
	}

	//Collision Function
	for (int x = 0; x < collisionMap.size(); x++) {
		for (int y = 0; y < collisionMap.size(); y++) {
			if (sprite.getGlobalBounds().intersects(collisionMap[x][y].getGlobalBounds())) {
				if (collisionData[x][y] == 1) {
					sf::FloatRect playerBounds = sprite.getGlobalBounds();
					sf::FloatRect wallBounds = collisionMap[x][y].getGlobalBounds();

					sf::FloatRect area;
					if (sprite.getGlobalBounds().intersects(collisionMap[x][y].getGlobalBounds(), area))
					{
						// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
						if (area.width > area.height)
						{
							if (area.contains({ area.left, sprite.getPosition().y }))
							{
								// Up side crash
								sprite.setPosition({ sprite.getPosition().x, sprite.getPosition().y + area.height });
							}
							else
							{
								// Down side crash
								sprite.setPosition({ sprite.getPosition().x, sprite.getPosition().y - area.height });
							}
						}
						else if (area.width < area.height)
						{
							if (area.contains({ sprite.getPosition().x + sprite.getGlobalBounds().width - 1.f, area.top + 1.f }))
							{
								//Right side crash
								sprite.setPosition({ sprite.getPosition().x - area.width, sprite.getPosition().y });
							}
							else
							{
								//Left side crash
								sprite.setPosition({ sprite.getPosition().x + area.width, sprite.getPosition().y });
							}
						}
					}
				}
			}
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