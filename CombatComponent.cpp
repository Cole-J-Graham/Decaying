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
	//Delete Character
	delete this->character;

	//Deconstruct Sprites
	auto is = this->sprites.begin();
	for (is = this->sprites.begin(); is != this->sprites.end(); ++is) {
		delete is->second;
	}

	//Deconstruct Enemies
	for (auto ptr : this->enemies) {
		delete ptr;
	}
	enemies.clear();
}


//Core Functions
void CombatComponent::update(const sf::Vector2f mousePos)
{
	this->updateEnemies();
	this->character->inventory->update(this->sprites["ZIN"]->getSprite(), mousePos);
	this->character->update(mousePos);
	this->character->combat->detectCombatKeybinds(mousePos, this->sprites["ZIN"]->getSprite());
	this->detectCollision();
}

void CombatComponent::render(sf::RenderTarget* target)
{
	this->character->render(target);
	this->renderEnemies(target);
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
		if (this->sprites["ZIN"]->getSprite().getGlobalBounds().intersects(it->getGlobalBounds())) {
			std::cout << this->character->getHp() << "\n";
			this->character->getHp() -= it->getDamage();
		}
	}
}

void CombatComponent::detectPlayerAttack()
{
	for (auto& it : this->enemies) {
		if (this->character->getPlayerProjectile().getGlobalBounds().intersects(it->getGlobalBounds())) {
			//std::cout << "HURT, BABY" << "\n";
		}
	}
}

//Enemy Functions
void CombatComponent::updateEnemies()
{
	for (auto& it : this->enemies) {
		it->update(this->character->zin->getPosition()); 
	}

}

void CombatComponent::renderEnemies(sf::RenderTarget* target)
{
	for (auto& it : this->enemies) {
		it->render(target); 
	}
}

//Spawn Functions
void CombatComponent::spawnSlime(float x, float y)
{
	this->enemy = new Enemy(100.f, 2, "Assets/Enemies/slime-red.png",
		"Assets/Enemies/slime-red-idle.png", "Assets/Enemies/slime-red.png",
		"Assets/Enemies/slime-red.png", "Assets/Enemies/slime-red.png");
	this->enemy->setPosition(x, y);
	this->enemies.push_back(this->enemy);
}

//Sprite Functions
void CombatComponent::initSprites()
{
	this->sprites["ZIN"] = new Sprite(900.f, 500.f, 16.f, 16.f, 4.0f, zin);
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