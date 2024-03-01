#include "DungeonState.h"
//Constructors and Destructors
DungeonState::DungeonState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	//State
	this->window = window;

	//Core Variables
	this->location = 0;

	//Initialization
	this->initSprites();
	this->initTileMaps();

	//Assets
	this->loadAssets();

	this->inventory["PLAYER_INVENTORY"] = new Inventory();
	this->character = new Character(&this->sprites["ZIN"]->getSprite());
	std::cout << &this->sprites["ZIN"]->getSprite() << "\n";
	
}

DungeonState::~DungeonState()
{
	delete this->character;

	//Deconstruct Sprites
	auto is = this->sprites.begin();
	for (is = this->sprites.begin(); is != this->sprites.end(); ++is) {
		delete is->second;
	}

	//Deconstruct TileMaps
	auto it = this->tile_maps.begin();
	for (it = this->tile_maps.begin(); it != this->tile_maps.end(); ++it) {
		delete it->second;
	}

	//Deconstruct Inventory
	auto in = this->inventory.begin();
	for (in = this->inventory.begin(); in != this->inventory.end(); ++in) {
		delete in->second;
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
	this->character->updateCharacter(this->getMousePosView());
	this->inventory["PLAYER_INVENTORY"]->checkForInput();
	this->updateMousePositions();
	this->checkForQuit();
	this->character->combat->detectCombatKeybinds(this->getMousePosView(), this->sprites["ZIN"]->getSprite());
}

void DungeonState::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->tile_maps["DUNGEON"]->detectMap(this->inventory["PLAYER_INVENTORY"], this->sprites["ZIN"]->getSprite());
	this->inventory["PLAYER_INVENTORY"]->update(this->sprites["ZIN"]->getSprite(), this->getMousePosView());
	if (this->tile_maps["DUNGEON"]->getCollidingEntrance()) { this->generateNewLocation(); };
}

void DungeonState::render(sf::RenderTarget* target)
{
	this->renderTileMaps(target);
	this->renderInventory(target);
	this->renderSprites(target);
	this->character->combat->renderAttacks(target);
}

//Sprite Functions
void DungeonState::initSprites()
{
	this->sprites["ZIN"] = new Sprite(900.f, 500.f, 16.f, 16.f, 4.0f, zin);
}

void DungeonState::renderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites) {
		it.second->render(target);
	}
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

//Inventory Functions
void DungeonState::renderInventory(sf::RenderTarget* target)
{
	for (auto& it : this->inventory) {
		it.second->render(target);
	}
}

//Assets
void DungeonState::loadAssets()
{
	this->dungeon_sheet.loadFromFile("Assets/SpriteSheets/DungeonTileSheet.png");

	this->zin.loadFromFile("Assets/SpriteSheets/zinWalkSpriteSheet.png");
}