#pragma once
//States
#include"State.h"
//Assets
#include"TileMap.h"
#include"Sprite.h"
//Character
#include"Character.h"

class DungeonState : public State
{
public:
	//Constructors and Destructors
	DungeonState(sf::RenderWindow* window,
		std::stack<State*>* states);
	~DungeonState();

	//Core Travel Functions
	void generateNewLocation();

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
	sf::Clock fps_clock;
	sf::Time fps_time;

	//Core Variables
	int location;

	std::map<std::string, TileMap*> tile_maps;
	std::map<std::string, Sprite*> sprites;
	std::map<std::string, Inventory*> inventory;

	Character* character;

	//Assets
	sf::Texture dungeon_sheet;
	sf::Texture map_image;
	sf::Texture zin;


};