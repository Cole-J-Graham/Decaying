#pragma once
//States
#include"State.h"
//Assets
#include"TileMap.h"
#include"Sprite.h"

class TravelState : public State
{
public:
	//Constructors and Destructors
	TravelState(sf::RenderWindow* window);
	~TravelState();

	//Core Travel Functions
	void setLocation();

	//State Functions
	void endState();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);

	//Sprite Functions
	void initSprites();
	void renderSprites(sf::RenderTarget* target);

	//TileMap Functions
	void initTileMaps();
	void renderTileMaps(sf::RenderTarget* target);

	//Inventory && Item Functions
	void renderInventory(sf::RenderTarget* target);

	//Assets
	void loadAssets();

	sf::RenderWindow* window;

private:
	//Core Variables
	int location;

	std::map<std::string, TileMap*> tile_maps;
	std::map<std::string, Sprite*> sprites;

	std::map<std::string, Inventory*> inventory;

	//Assets
	sf::Texture forest_sheet;
	sf::Texture map_image;
	sf::Texture zin;
};