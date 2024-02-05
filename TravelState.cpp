#include "TravelState.h"
//Constructors and Destructors
TravelState::TravelState()
{
	//Core Variables
	this->location = 0;

	//Initialization
	this->initSprites();
	this->initTileMaps();

	//Assets
	this->loadAssets();

	this->inventory = new Inventory();
}

TravelState::~TravelState()
{
	delete this->inventory;

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
}

void TravelState::endState()
{

}

//Core Travel Functions
void TravelState::setLocation()
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
void TravelState::updateKeybinds(const float& dt)
{
	this->sprites["ZIN"]->checkForMovement(zin_up, zin_down, zin_left, zin_right);
	this->inventory->checkForInput();
	this->checkForQuit();
}

void TravelState::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->tile_maps["FOREST"]->detectCollision(this->sprites["ZIN"]->getSprite());
	this->tile_maps["FOREST"]->detectMovement();
}

void TravelState::render(sf::RenderTarget* target)
{
	this->renderTileMaps(target);
	this->renderSprites(target);
	this->inventory->render(target);
}

//Sprite Functions
void TravelState::initSprites()
{
	this->sprites["ZIN"] = new Sprite(900.f, 500.f, 16.f, 16.f, 4.0f, zin_down);
}

void TravelState::renderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites) {
		it.second->render(target);
	}
}

//TileMap Functions
void TravelState::initTileMaps()
{
	this->tile_maps["FOREST"] = new TileMap(0.f, 0.f, 30, 30, 64.f, forest_sheet, "Assets/SpriteData/forest.txt");
}

void TravelState::renderTileMaps(sf::RenderTarget* target)
{
	for (auto& it : this->tile_maps) {
		it.second->render(target);
	}
}

//Assets
void TravelState::loadAssets()
{
	this->forest_sheet.loadFromFile("Assets/SpriteSheets/landSpriteSheet.png");
	this->map_image.loadFromFile("Assets/Wallpapers/Forest/forest1.jpeg");

	this->zin_up.loadFromFile("Assets/SpriteSheets/zinWalkUpSpriteSheet.png");
	this->zin_down.loadFromFile("Assets/SpriteSheets/zinWalkSpriteSheet.png");
	this->zin_left.loadFromFile("Assets/SpriteSheets/zinWalkLeftSpriteSheet.png");
	this->zin_right.loadFromFile("Assets/SpriteSheets/zinWalkRightSpriteSheet.png");
}