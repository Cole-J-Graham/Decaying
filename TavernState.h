#pragma once
//States
#include"State.h"
#include"DungeonState.h"
//Assets
#include"TileMap.h"
#include"Sprite.h"

class TavernState : public State
{
public:
	//Constructors and Destructors
	TavernState(sf::RenderWindow* window,
		std::stack<State*>* states);
	~TavernState();

	//Core Travel Functions
	void enterDungeon();

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
	sf::Texture tavern_sheet;
	sf::Texture map_image;
	sf::Texture zin;


};