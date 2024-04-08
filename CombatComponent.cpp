#include "CombatComponent.h"
//Constructors and Deconstructors
CombatComponent::CombatComponent()
{
	this->loadAssets();
	this->initSprites();
	this->character = new Character(&this->sprites["ZIN"]->getSprite());
}

CombatComponent::~CombatComponent()
{
	delete this->character;

	//Deconstruct Sprites
	auto is = this->sprites.begin();
	for (is = this->sprites.begin(); is != this->sprites.end(); ++is) {
		delete is->second;
	}
}


//Core Functions
void CombatComponent::update(const sf::Vector2f mousePos)
{
	this->enemies["SLIME"]->update(this->character->zin->getPosition());
	this->character->inventory->update(this->sprites["ZIN"]->getSprite(), mousePos);
	this->character->update(mousePos);
	this->character->combat->detectCombatKeybinds(mousePos, this->sprites["ZIN"]->getSprite());
	this->detectCollision();
}

void CombatComponent::render(sf::RenderTarget* target)
{
	this->character->render(target);
	this->renderSprites(target);
}

//Detection Functions
void CombatComponent::detectCollision()
{
	this->detectPlayerDamage();
	this->detectPlayerAttack();
}

void CombatComponent::detectPlayerDamage()
{
	for (auto& it : this->enemies) {
		if (this->sprites["ZIN"]->getSprite().getGlobalBounds().intersects(it.second->getGlobalBounds())) {
			std::cout << "COLLISION, BABY" << "\n";
		}
		else {

		}
	}
}

void CombatComponent::detectPlayerAttack()
{
	for (auto& it : this->enemies) {
		if (this->character->getPlayerProjectile().getGlobalBounds().intersects(it.second->getGlobalBounds())) {
			std::cout << "HURT, BABY" << "\n";
		}
		else {

		}
	}
}

//Sprite Functions
void CombatComponent::initSprites()
{
	this->sprites["ZIN"] = new Sprite(900.f, 500.f, 16.f, 16.f, 4.0f, zin);

	this->enemies["SLIME"] = new Enemy(100.f, 100.f, 100.f, "Assets/Enemies/slime-red.png", 
		"Assets/Enemies/slime-red.png", "Assets/Enemies/slime-red.png", 
		"Assets/Enemies/slime-red.png", "Assets/Enemies/slime-red.png");
}

void CombatComponent::renderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites) {
		it.second->render(target);
	}
}

//Asset Functions
void CombatComponent::loadAssets()
{
	this->zin.loadFromFile("Assets/SpriteSheets/zinWalkSpriteSheet.png");
}