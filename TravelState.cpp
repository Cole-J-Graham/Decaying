#include "TravelState.h"
//Constructors and Destructors
TravelState::TravelState()
{
	//Core Variables
	this->location = 0;

	//Animation Variables
	this->movementSpeed = 1.5f;
	this->animationFrame = -1;

	this->sheetX;
	this->sheetY;

	this->velocity.x = 0.f;
	this->velocity.y = 0.f;

	this->frame = 0;
	this->frameInit = false;

	//Assets
	this->loadAssets();
	this->setAssets();
}

TravelState::~TravelState()
{

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

void TravelState::checkForMovement()
{
	//Animate walk cycle
	if (this->playerMoving) {
		this->animateTimer();
		switch (this->animationFrame) {
		case -1:
			sheetX = 0;
			sheetY = 0;
			break;
		case 0:
			sheetX = 16;
			sheetY = 0;
			break;
		case 1:
			sheetX = 32;
			sheetY = 0;
			break;
		case 2:
			sheetX = 48;
			sheetY = 0;
			break;
		}
	}
	//Set basic attributes for sprite
	zinPixelSprite.setScale(4.0f, 4.0f);
	zinPixelSprite.setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;

	//Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		velocity.y += -movementSpeed;
		this->playerMoving = true;
		zinPixelSprite.setTexture(zinWalkUp);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y += movementSpeed;
		this->playerMoving = true;
		zinPixelSprite.setTexture(zinWalkDown);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x += -movementSpeed;
		this->playerMoving = true;
		zinPixelSprite.setTexture(zinWalkLeft);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocity.x += movementSpeed;
		this->playerMoving = true;
		zinPixelSprite.setTexture(zinWalkRight);
	}
	zinPixelSprite.move(velocity);

	//Character stops moving
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sheetX = 0;
		sheetY = 0;
		this->playerMoving = false;
	}
}

//State Functions
void TravelState::updateKeybinds(const float& dt)
{
	this->checkForMovement();
	this->checkForQuit();
}

void TravelState::update(const float& dt)
{
	this->updateKeybinds(dt);
}

void TravelState::render(sf::RenderTarget* target)
{
	TileMap tilemap;
	tilemap.loadForest(*target);
	tilemap.loadCollisionMap(*target, zinPixelSprite);
	target->draw(zinPixelSprite);
}

//Assets
void TravelState::setAssets()
{
	mapImage.loadFromFile("Assets/Wallpapers/Forest/forest1.jpeg");
	mapSprite.setTexture(mapImage);
}

void TravelState::loadAssets()
{
	zinWalkDown.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkSpriteSheet.png");
	zinWalkLeft.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkLeftSpriteSheet.png");
	zinWalkRight.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkRightSpriteSheet.png");
	zinWalkUp.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkUpSpriteSheet.png");
}

void TravelState::animateTimer()
{
	elapsed = timer.getElapsedTime();
	if (elapsed.asSeconds() >= 0.2f) {
		if (this->animationFrame == -1) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 0) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 1) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 2) {
			this->animationFrame = -1;
			timer.restart();
		}
	}
}

void TravelState::animateFourFrames(sf::Sprite& inSprite, int xOffset, float posX, float posY)
{
	inSprite.setTextureRect(sf::IntRect(sheetX, sheetY, xOffset, xOffset));
	inSprite.setPosition(posX, posY);
	this->animateTimer();
	switch (this->animationFrame) {
	case -1:
		sheetX = 0;
		sheetY = 0;
		break;
	case 0:
		sheetX = xOffset;
		sheetY = 0;
		break;
	case 1:
		sheetX = xOffset * 2;
		sheetY = 0;
		break;
	case 2:
		sheetX = xOffset * 3;
		sheetY = 0;
		break;
	}
}