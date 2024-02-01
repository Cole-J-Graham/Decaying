#include "TravelState.h"
//Constructors and Destructors
TravelState::TravelState()
{
	//Core Variables
	this->location = 0;

	//Assets
	this->loadAssets();
	this->setAssets();
	this->initSprites();
}

TravelState::~TravelState()
{
	//Deconstruct Sprites
	auto is = this->sprites.begin();
	for (is = this->sprites.begin(); is != this->sprites.end(); ++is) {
		delete is->second;
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
	//this->checkForMovement();
	this->sprites["ZIN"]->checkForMovement(zin_up, zin_down, zin_left, zin_right);
	this->checkForQuit();
}

void TravelState::update(const float& dt)
{
	this->updateKeybinds(dt);
}

void TravelState::render(sf::RenderTarget* target)
{
	TileMap tilemap;
	tilemap.loadForest(*target, zinPixelSprite);
	//tilemap.loadCollisionMap(*target, this->sprites["ZIN"]);
	this->renderSprites(target);
}

//Sprite Functions
void TravelState::initSprites()
{
	this->sprites["ZIN"] = new Sprite(0.f, 0.f, 16.f, 16.f, 4.0f, zin_down);
}

void TravelState::renderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites) {
		it.second->render(target);
	}
}

//Assets
void TravelState::setAssets()
{
	//mapImage.loadFromFile("Assets/Wallpapers/Forest/forest1.jpeg");
	//mapSprite.setTexture(mapImage);
}

void TravelState::loadAssets()
{
	zin_up.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkUpSpriteSheet.png");
	zin_down.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkSpriteSheet.png");
	zin_left.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkLeftSpriteSheet.png");
	zin_right.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkRightSpriteSheet.png");
}