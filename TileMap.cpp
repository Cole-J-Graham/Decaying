#include "TileMap.h"
//Constructors and Destructors
TileMap::TileMap(float x, float y, int col, int row, float grid_size_f)
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

void TileMap::detectCollision(sf::Sprite& in_sprite)
{
	//Collision Function
	for (int x = 0; x < tile_map.size(); x++) {
		for (int y = 0; y < tile_map.size(); y++) {
			if (in_sprite.getGlobalBounds().intersects(tile_map[x][y].getGlobalBounds())) {
				if (tile_map_data[x][y] == 1) {
					sf::FloatRect playerBounds = in_sprite.getGlobalBounds();
					sf::FloatRect wallBounds = tile_map[x][y].getGlobalBounds();
					sf::FloatRect area;
					if (in_sprite.getGlobalBounds().intersects(tile_map[x][y].getGlobalBounds(), area))
					{
						// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
						if (area.width > area.height)
						{
							if (area.contains({ area.left, in_sprite.getPosition().y }))
							{
								// Up side crash
								in_sprite.setPosition({ in_sprite.getPosition().x, in_sprite.getPosition().y + area.height });
							}
							else
							{
								// Down side crash
								in_sprite.setPosition({ in_sprite.getPosition().x, in_sprite.getPosition().y - area.height });
							}
						}
						else if (area.width < area.height)
						{
							if (area.contains({ in_sprite.getPosition().x + in_sprite.getGlobalBounds().width - 1.f, area.top + 1.f }))
							{
								//Right side crash
								in_sprite.setPosition({ in_sprite.getPosition().x - area.width, in_sprite.getPosition().y });
							}
							else
							{
								//Left side crash
								in_sprite.setPosition({ in_sprite.getPosition().x + area.width, in_sprite.getPosition().y });
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