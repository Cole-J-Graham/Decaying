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

	//Movement
	this->stamina = 100;
	this->movementSpeed = 1.5f;
	this->velocity.x = 0;
	this->velocity.y = 0;
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
	//Draw a specific set texture tile based on which input is recieved from a tilemap vector
	this->tile_map.resize(row, std::vector<sf::Sprite>(col));
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			this->tile_map[x][y].setScale(sf::Vector2f(4.0f, 4.0f));
			this->tile_map[x][y].setPosition(x * grid_size_f + this->x, y * grid_size_f + this->y);
			this->tile_map[x][y].setTexture(tile_sheet);

			//Fill in data depending on the case found in the map file
			switch (this->tile_map_data[x][y]) {
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
			}
		}
	}
}

void TileMap::loadMapData(std::string input)
{
	map_data.open(input);

	if (map_data.is_open()) {
		for (int x = 0; x < col; x++) {
			for (int y = 0; y < row; y++) {
				map_data >> tile_map_data[x][y];
			}
		}
	}
	else {
		std::cout << "ERROR LOADING TILEMAP FILE..." << "\n";
	}

	map_data.close();
}

//Detection Functions
void TileMap::detectMap(Inventory* inventory, sf::Sprite& in_sprite)
{
	this->detectCollision(inventory, in_sprite);
	this->detectEntrance(in_sprite);
	this->detectMovement(inventory);
}

void TileMap::detectCollision(Inventory* inventory, sf::Sprite& in_sprite)
{
	//Collision Function
	for (int x = 0; x < tile_map.size(); x++) {
		for (int y = 0; y < tile_map.size(); y++) {
			if (tile_map_data[x][y] == 0) {
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

							for (auto& it : inventory->getItems()) {
								it.second->setMapPosition({ it.second->getPosition().x, it.second->getPosition().y + area.height });
							}
							for (auto& it : inventory->getWeapons()) {
								it.second->setMapPosition({ it.second->getPosition().x, it.second->getPosition().y + area.height });
							}
							for (auto& it : inventory->getRelics()) {
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

							for (auto& it : inventory->getItems()) {
								it.second->setMapPosition({ it.second->getPosition().x, it.second->getPosition().y - area.height });
							}
							for (auto& it : inventory->getWeapons()) {
								it.second->setMapPosition({ it.second->getPosition().x, it.second->getPosition().y - area.height });
							}
							for (auto& it : inventory->getRelics()) {
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

							for (auto& it : inventory->getItems()) {
								it.second->setMapPosition({ it.second->getPosition().x - area.width, it.second->getPosition().y });
							}
							for (auto& it : inventory->getWeapons()) {
								it.second->setMapPosition({ it.second->getPosition().x - area.width, it.second->getPosition().y});
							}
							for (auto& it : inventory->getRelics()) {
								it.second->setMapPosition({ it.second->getPosition().x - area.width, it.second->getPosition().y });
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

							for (auto& it : inventory->getItems()) {
								it.second->setMapPosition({ it.second->getPosition().x + area.width, it.second->getPosition().y });
							}
							for (auto& it : inventory->getWeapons()) {
								it.second->setMapPosition({ it.second->getPosition().x + area.width, it.second->getPosition().y });
							}
							for (auto& it : inventory->getRelics()) {
								it.second->setMapPosition({ it.second->getPosition().x + area.width, it.second->getPosition().y });
							}
						}
					}
				}
			}
		}
	}
}

void TileMap::detectEntrance(sf::Sprite& in_sprite)
{
	for (int x = 0; x < tile_map.size(); x++) {
		for (int y = 0; y < tile_map.size(); y++) {
			if (tile_map_data[x][y] == 1) {
				if (tile_map[x][y].getGlobalBounds().intersects(in_sprite.getGlobalBounds(), area))
				{
					std::cout << "Colliding With Entrance" << "\n";
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
void TileMap::detectMovement(Inventory* inventory)
{
	//Detect Movement
	this->detectWalk();
	this->detectDodgeRoll();
	this->detectSprint();

	//Move based on movement function
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			this->tile_map[x][y].move(velocity);
		}
	}

	//Move Items with map
	this->moveItems(inventory);
}

void TileMap::detectWalk()
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
}

void TileMap::detectDodgeRoll()
{
	dodge_elapsed = dodge_timer.getElapsedTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && dodge_elapsed.asSeconds() >= 0.4) {
		movementSpeed += 5;
		dodge_timer.restart();
	}
	else if (dodge_elapsed.asSeconds() >= 0.4) {
		movementSpeed = 1.5;
	}
}

void TileMap::detectSprint()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && this->stamina > 0) {
		movementSpeed += 2.5;
	}
	else if (this->stamina < 0) {
		movementSpeed = 1.5f;
	}
}

//Item Functions
void TileMap::moveItems(Inventory* inventory)
{
	for (auto& it : inventory->getItems()) { it.second->moveItem(velocity); }
	for (auto& it : inventory->getWeapons()) {it.second->moveItem(velocity);}
	for (auto& it : inventory->getRelics()) {it.second->moveItem(velocity);}
}

void TileMap::holdItemPosition(Inventory* inventory)
{
	for (auto& it : inventory->getItems()) {
		it.second->setMapPosition({ it.second->getPosition().x + area.width, it.second->getPosition().y });
	}
	for (auto& it : inventory->getWeapons()) {
		it.second->setMapPosition({ it.second->getPosition().x + area.width, it.second->getPosition().y });
	}
	for (auto& it : inventory->getRelics()) {
		it.second->setMapPosition({ it.second->getPosition().x + area.width, it.second->getPosition().y });
	}
}