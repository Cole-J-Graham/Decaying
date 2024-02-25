#include "ForestState.h"
//Constructors and Destructors
ForestState::ForestState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
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

ForestState::~ForestState()
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

void ForestState::endState()
{

}

//Core Travel Functions
void ForestState::setLocation()
{
	switch (this->location) {
	case 0:
		
		break;
	case 1:
		break;
	case 2:
		break;
	}
}

//State Functions
void ForestState::updateKeybinds(const float& dt)
{
	this->sprites["ZIN"]->animateMovement();
	this->inventory["PLAYER_INVENTORY"]->checkForInput();
	this->updateMousePositions();
	this->checkForQuit();
}

void ForestState::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->tile_maps["FOREST"]->detectCollision(this->inventory["PLAYER_INVENTORY"], this->sprites["ZIN"]->getSprite());
	this->tile_maps["FOREST"]->detectMovement(this->inventory["PLAYER_INVENTORY"]);
	this->inventory["PLAYER_INVENTORY"]->update(this->sprites["ZIN"]->getSprite(), this->getMousePosView());
	this->inventory["PLAYER_INVENTORY"]->pickupItem();
}

void ForestState::render(sf::RenderTarget* target)
{
	this->renderTileMaps(target);
	this->renderInventory(target);
	this->renderSprites(target);
}

//Sprite Functions
void ForestState::initSprites()
{
	this->sprites["ZIN"] = new Sprite(900.f, 500.f, 16.f, 16.f, 4.0f, zin);
}

void ForestState::renderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites) {
		it.second->render(target);
	}
}

//TileMap Functions
void ForestState::initTileMaps()
{
	this->tile_maps["FOREST"] = new TileMap(0.f, 0.f, 30, 30, 64.f, forest_sheet, "Assets/SpriteData/forest.txt");
}

void ForestState::renderTileMaps(sf::RenderTarget* target)
{
	for (auto& it : this->tile_maps) {
		it.second->render(target);
	}
}

//Inventory Functions
void ForestState::renderInventory(sf::RenderTarget* target)
{
	for (auto& it : this->inventory) {
		it.second->render(target);
	}
}

//Assets
void ForestState::loadAssets()
{
	this->forest_sheet.loadFromFile("Assets/SpriteSheets/landSpriteSheet.png");

	this->zin.loadFromFile("Assets/SpriteSheets/zinWalkSpriteSheet.png");
}