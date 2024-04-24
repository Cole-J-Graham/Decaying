#pragma once
//States
#include"State.h"
#include"DungeonState.h"
//Assets
#include"TileMap.h"
#include"Sprite.h"
#include"Npcs.h"
#include"CombatComponent.h"

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

	//Npc Functions
	void updateNpcs();
	void initNpcs();
	void renderNpcs(sf::RenderTarget* target);

	//TileMap Functions
	void initTileMaps();
	void renderTileMaps(sf::RenderTarget* target);

	//Assets
	void loadAssets();

	sf::RenderWindow* window;

private:
	//Core Variables
	int location;

	std::map<std::string, Npcs*> npcs;
	std::map<std::string, TileMap*> tile_maps;

	//Assets
	sf::Texture tavern_sheet;
	sf::Texture map_image;

	CombatComponent* combat;


};