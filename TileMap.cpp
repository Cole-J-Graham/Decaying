#include "TileMap.h"
//Constructors and Destructors
TileMap::TileMap(float x, float y, int col, int row, float grid_size_f, sf::Texture& tile_sheet,
	std::string map_data_string)
{
	//Core Variables
	this->tile_sheet = tile_sheet;
	this->grid_size_f = grid_size_f;
	this->col = col;
	this->row = row;
	this->x = x;
	this->y = y;
	this->map_data_string = map_data_string;

	this->sheetX;
	this->sheetY;

	this->colliding = false;
	this->colliding_entrance = false;

	this->loadMapData(map_data_string);
	this->loadMap(tile_sheet);
}

TileMap::~TileMap()
{

}

//Core Functions
void TileMap::loadMap(sf::Texture& tile_sheet)
{
	// Resize tile_map to match the specified dimensions
    tile_map.resize(col, std::vector<Tile>(row));
    for (int x = 0; x < col; x++) {
        for (int y = 0; y < row; y++) {
            // Check if the tile_map_data vector has been properly initialized
            if (x < tile_map_data.size() && y < tile_map_data[x].size()) {
                // Load the tile sprite based on tile_map_data
                tile_map[x][y].setScale(sf::Vector2f(4.0f, 4.0f));
                tile_map[x][y].setPosition(x * grid_size_f + this->x, y * grid_size_f + this->y);
                tile_map[x][y].setTexture(tile_sheet);

                // Set the texture rectangle based on tile_map_data
                switch (tile_map_data[x][y]) {
				case 0:
					this->sheetX = 0;
					this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
					break;
				case 1:
					this->sheetX = 16;
					this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
					break;
				case 2:
					this->sheetX = 32;
					this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
					break;
				case 3:
					this->sheetX = 48;
					this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
					break;
				case 4:
					this->sheetX = 64;
					this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
					break;
				case 5:
					this->sheetX = 80;
					this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
					break;
				case 6:
					this->sheetX = 96;
					this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
					break;
				case 7:
					this->sheetX = 112;
					this->tile_map[x][y].setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
					break;
                    // Handle different tile types
                }
            } else {
                // Handle the case where tile_map_data is not properly initialized
                std::cout << "ERROR: Tile map data is not properly initialized." << std::endl;
                break;
            }
        }
    }
}

void TileMap::loadMapData(std::string input)
{
	map_data.open(input);

	if (map_data.is_open()) {
		// Resize tile_map_data to match the specified dimensions
		tile_map_data.resize(col, std::vector<int>(row));

		for (int x = 0; x < col; x++) {
			for (int y = 0; y < row; y++) {
				// Check if there is more data to read
				if (!map_data.eof()) {
					map_data >> tile_map_data[x][y];
				}
				else {
					// Handle the case where there is not enough data in the file
					std::cout << "ERROR: Not enough data in the tilemap file." << std::endl;
					break;
				}
			}
		}
	}
	else {
		std::cout << "ERROR LOADING TILEMAP FILE..." << std::endl;
	}

	map_data.close();
}

//Detection Functions
void TileMap::detectMap(Character* character, CombatComponent* combat, sf::FloatRect playerPos)
{
	this->detectCollision(combat, playerPos);
	this->detectEntrance(playerPos);
	this->detectMovement(character, combat);
}

void TileMap::detectCollision(CombatComponent* combat, sf::FloatRect playerPos)
{
	//Collision Function
	for (int x = 0; x < tile_map.size(); x++) {
		for (int y = 0; y < tile_map.size(); y++) {
			if (tile_map_data[x][y] == 0) {
				if (tile_map[x][y].getGlobalBounds().intersects(playerPos, area))
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

							//Must stay below this point
							for (auto& it : combat->playerCombat->character->inventory->getItems()) {
								it.second->setMapPosition({ it.second->getPosition().x, it.second->getPosition().y + area.height });
							}
							for (auto& it : combat->enemies) {
								it.second->setMapPosition({ it.second->getPosition().x, it.second->getPosition().y + area.height });
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

							//Must stay below this point
							for (auto& it : combat->playerCombat->character->inventory->getItems()) {
								it.second->setMapPosition({ it.second->getPosition().x, it.second->getPosition().y - area.height });
							}
							for (auto& it : combat->enemies) {
								it.second->setMapPosition({ it.second->getPosition().x, it.second->getPosition().y - area.height });
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

							//Must stay below this point
							for (auto& it : combat->playerCombat->character->inventory->getItems()) {
								it.second->setMapPosition({ it.second->getPosition().x - area.width, it.second->getPosition().y });
							}
							for (auto& it : combat->enemies) {
								it.second->setMapPosition({ it.second->getPosition().x - area.width, it.second->getPosition().y});
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

							//Must stay below this point
							for (auto& it : combat->playerCombat->character->inventory->getItems()) {
								it.second->setMapPosition({ it.second->getPosition().x + area.width, it.second->getPosition().y });
							}
							for (auto& it : combat->enemies) {
								it.second->setMapPosition({ it.second->getPosition().x + area.width, it.second->getPosition().y });
							}
						}
					}
				}
			}
		}
	}
}

void TileMap::detectEntrance(sf::FloatRect playerPos)
{
	for (int x = 0; x < tile_map.size(); x++) {
		for (int y = 0; y < tile_map.size(); y++) {
			if (tile_map_data[x][y] == 1) {
				if (tile_map[x][y].getGlobalBounds().intersects(playerPos, area))
				{
					this->colliding_entrance = true;
				}
				else {
					this->colliding_entrance = false;
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

//Movement Functions
void TileMap::detectMovement(Character* character, CombatComponent* combat)
{
	//Move based on movement function
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			this->tile_map[x][y].move(character->getVelocity());
		}
	}

	//Move Items with map
	this->moveItems(character, combat);
}

//Item Functions
void TileMap::moveItems(Character* character, CombatComponent* combat)
{
	for (auto& it : character->inventory->getItems()) { it.second->moveItem(character->getVelocity()); }
	for (auto& it : combat->enemies) { it.second->moveEnemy(character->getVelocity()); }
}