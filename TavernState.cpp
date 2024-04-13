#include "TavernState.h"
//Constructors and Destructors
TavernState::TavernState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
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

}

TavernState::~TavernState()
{
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

void TavernState::endState()
{

}

//Core Tavern Functions
void TavernState::enterDungeon()
{
	this->states->push(new DungeonState(this->window, this->states));
}

//State Functions
void TavernState::updateKeybinds(const float& dt)
{
	//this->sprites["player"]->animateMovement();
	this->inventory["PLAYER_INVENTORY"]->checkForInput();
	this->updateMousePositions();
	this->checkForQuit();
}

void TavernState::update(const float& dt)
{
	this->updateKeybinds(dt);
	//this->tile_maps["TAVERN"]->detectMap(this->character, this->inventory["PLAYER_INVENTORY"], this->sprites["player"]->getSprite());
	this->inventory["PLAYER_INVENTORY"]->update(this->sprites["player"]->getSprite(), this->getMousePosView());
	if (this->tile_maps["TAVERN"]->getCollidingEntrance()) { this->enterDungeon(); };
}

void TavernState::render(sf::RenderTarget* target)
{
	this->renderTileMaps(target);
	this->renderSprites(target);
}

//Sprite Functions
void TavernState::initSprites()
{
	this->sprites["player"] = new Sprite(900.f, 500.f, 16.f, 16.f, 4.0f, "Assets/SpriteSheets/playerWalkSpriteSheet.png", false);
}

void TavernState::renderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites) {
		it.second->render(target);
	}
}

//TileMap Functions
void TavernState::initTileMaps()
{
	this->tile_maps["TAVERN"] = new TileMap(0.f, 0.f, 30, 30, 64.f, tavern_sheet, "Assets/SpriteData/dungeon.txt");
}

void TavernState::renderTileMaps(sf::RenderTarget* target)
{
	for (auto& it : this->tile_maps) {
		it.second->render(target);
	}
}

//Asset Functions
void TavernState::loadAssets()
{
	this->tavern_sheet.loadFromFile("Assets/SpriteSheets/TavernTileSheet.png");
}