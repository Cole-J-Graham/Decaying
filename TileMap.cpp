#include "TileMap.h"
//Constructors and Destructors
TileMap::TileMap(float x, float y, int col, int row, float grid_size_f, sf::Texture& tile_sheet)
{
	//Core Variables
	this->tile_sheet = tile_sheet;
	this->grid_size_f = grid_size_f;
	this->col = col;
	this->row = row;
	this->x = x;
	this->y = y;

	this->sheetX;
	this->sheetY;

	//Movement
	this->movementSpeed = 1.5f;
	this->velocity.x = 0;
	this->velocity.y = 0;

	this->loadMap(tile_sheet);
}

TileMap::~TileMap()
{

}

//Core Functions
void TileMap::loadMap(sf::Texture& tile_sheet)
{
	//Draw a specific set texture tile based on which input is recieved from a tilemap vector
	this->tile_map.resize(row, std::vector<sf::Sprite>(col));
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			this->tile_map[x][y].setScale(sf::Vector2f(4.0f, 4.0f));
			this->tile_map[x][y].setPosition(x * grid_size_f + this->x, y * grid_size_f + this->y);
			this->tile_map[x][y].setTexture(tile_sheet);
			if (this->tile_map_data[x][y] == 0) {
				this->sheetX = 0;
				this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
			else if (this->tile_map_data[x][y] == 1) {
				this->sheetX = 16;
				this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
			else if (this->tile_map_data[x][y] == 2) {
				this->sheetX = 32;
				this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
			else if (this->tile_map_data[x][y] == 3) {
				this->sheetX = 48;
				this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
			}
		}
	}
}

void TileMap::detectMovement()
{
	this->velocity.x = 0;
	this->velocity.y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		velocity.y += movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y += -movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x += movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocity.x += -movementSpeed;
	}

	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			this->tile_map[x][y].move(velocity);
		}
	}
}

void TileMap::detectCollision(sf::Sprite& in_sprite)
{
	//Collision Function
	for (int x = 0; x < tile_map.size(); x++) {
		for (int y = 0; y < tile_map.size(); y++) {
			if (tile_map[x][y].getGlobalBounds().intersects(in_sprite.getGlobalBounds())) {
				if (tile_map_data[x][y] == 1) {
					sf::FloatRect playerBounds = in_sprite.getGlobalBounds();
					sf::FloatRect wallBounds = tile_map[x][y].getGlobalBounds();
					sf::FloatRect area;
					if (tile_map[x][y].getGlobalBounds().intersects(in_sprite.getGlobalBounds(), area))
					{
						// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
						if (area.width > area.height)
						{
							if (area.contains({ area.left, tile_map[x][y].getPosition().y }))
							{
								//Down side crash
								for (int x = 0; x < col; x++) {
									for (int y = 0; y < row; y++) {
										tile_map[x][y].setPosition({ tile_map[x][y].getPosition().x, tile_map[x][y].getPosition().y + area.height });
									}
								}
							}
							else
							{
								//Up side crash
								for (int x = 0; x < col; x++) {
									for (int y = 0; y < row; y++) {
										tile_map[x][y].setPosition({ tile_map[x][y].getPosition().x, tile_map[x][y].getPosition().y - area.height });
									}
								}
							}
						}
						else if (area.width < area.height)
						{
							if (area.contains({ tile_map[x][y].getPosition().x + tile_map[x][y].getGlobalBounds().width - 1.f, area.top + 1.f }))
							{
								//Left side crash
								for (int x = 0; x < col; x++) {
									for (int y = 0; y < row; y++) {
										tile_map[x][y].setPosition({ tile_map[x][y].getPosition().x - area.width, tile_map[x][y].getPosition().y });
									}
								}
							}
							else
							{
								//Right side crash
								for (int x = 0; x < col; x++) {
									for (int y = 0; y < row; y++) {
										tile_map[x][y].setPosition({ tile_map[x][y].getPosition().x + area.width, tile_map[x][y].getPosition().y });
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

//State Functions
void TileMap::render(sf::RenderTarget* target)
{
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			target->draw(tile_map[x][y]);
		}
	}
}