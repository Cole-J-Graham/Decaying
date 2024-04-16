#include "DungeonState.h"
//Constructors and Destructors
DungeonState::DungeonState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	//State
	this->window = window;

	//Core Variables
	this->location = 0;

	//Initialization
	this->initTileMaps();

	//Assets
	this->loadAssets();

	this->combat = new CombatComponent();

	this->combat->spawnSlime("SLIME1", 200.f, 200.f);
	this->combat->spawnSlime("SLIME2", 400.f, 400.f);
}

DungeonState::~DungeonState()
{
	delete this->combat;

	//Deconstruct TileMaps
	auto it = this->tile_maps.begin();
	for (it = this->tile_maps.begin(); it != this->tile_maps.end(); ++it) {
		delete it->second;
	}
}

void DungeonState::endState()
{

}

//Core Travel Functions
void DungeonState::generateNewLocation()
{
	//Generate random number for tilemap generation
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> random_number(0, 2);
	this->location = random_number(rng);
	std::cout << this->location << "\n";

	switch (this->location) {
	case 0:
		this->tile_maps["DUNGEON"]->loadMapData("Assets/SpriteData/dungeon.txt");
		this->tile_maps["DUNGEON"]->loadMap(dungeon_sheet);
		break;
	case 1:
		this->tile_maps["DUNGEON"]->loadMapData("Assets/SpriteData/dungeon1.txt");
		this->tile_maps["DUNGEON"]->loadMap(dungeon_sheet);
		break;
	case 2:
		this->tile_maps["DUNGEON"]->loadMapData("Assets/SpriteData/dungeon2.txt");
		break;
	}
}

//State Functions
void DungeonState::updateKeybinds(const float& dt)
{
	this->updateMousePositions();
	this->checkForQuit();
}

void DungeonState::update(const float& dt)
{
	this->combat->update(this->getMousePosView());
	this->updateKeybinds(dt);
	this->tile_maps["DUNGEON"]->detectMap(this->combat->playerCombat->character, this->combat, this->combat->playerCombat->sprites["player"]->getSprite());
	if (this->tile_maps["DUNGEON"]->getCollidingEntrance()) { this->generateNewLocation(); };
}

void DungeonState::render(sf::RenderTarget* target)
{
	this->renderTileMaps(target);
	this->combat->render(target);
	this->combat->render(target);
}

//TileMap Functions
void DungeonState::initTileMaps()
{
	this->tile_maps["DUNGEON"] = new TileMap(0.f, 0.f, 30, 30, 64.f, dungeon_sheet, "Assets/SpriteData/dungeon.txt");
}

void DungeonState::renderTileMaps(sf::RenderTarget* target)
{
	for (auto& it : this->tile_maps) {
		it.second->render(target);
	}
}

//Assets
void DungeonState::loadAssets()
{
	this->dungeon_sheet.loadFromFile("Assets/SpriteSheets/DungeonTileSheet.png");
}