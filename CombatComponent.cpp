#include "CombatComponent.h"
//Constructors and Deconstructors
CombatComponent::CombatComponent()
{
	this->initSprites();
	this->character = new Character(&this->sprites["player"]->getSprite());
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
	auto ie = this->enemies.begin();
	for (ie = this->enemies.begin(); ie != this->enemies.end(); ++ie) {
		delete ie->second;
	}
}


//Core Functions
void CombatComponent::update(const sf::Vector2f mousePos)
{
	this->updateEnemies();
	this->character->inventory->update(this->sprites["player"]->getSprite(), mousePos);
	this->character->update(mousePos);
	this->character->combat->detectCombatKeybinds(mousePos, this->sprites["player"]->getSprite());
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
	this->detectEnemyDeath();
}

void CombatComponent::detectPlayerDamage()
{
	for (auto& it : this->enemies) {
		if (this->sprites["player"]->getSprite().getGlobalBounds().intersects(it.second->getGlobalBounds())) {
			std::cout << this->character->getHp() << "\n";
			this->character->getHp() -= it.second->getDamage();
		}
	}
}

void CombatComponent::detectPlayerAttack()
{
	for (auto& it : this->enemies) {
		if (this->character->getPlayerProjectile().getGlobalBounds().intersects(it.second->getGlobalBounds())) {
			it.second->getHp() -= this->character->getDamage();
			std::cout << it.second->getHp() << "\n";
		}
	}
}

void CombatComponent::detectEnemyDeath()
{
	for (auto it = this->enemies.begin(); it != this->enemies.end();) {
		if (it->second->getHp() <= 0) {
			delete it->second; // Delete the enemy object
			it = this->enemies.erase(it); // Remove the enemy from the map and update the iterator
		}
		else {
			++it; // Move to the next element
		}
	}
	
}

//Enemy Functions
void CombatComponent::updateEnemies()
{
	for (auto& it : this->enemies) {
		it.second->update(this->character->player->getPosition());
	}

}

void CombatComponent::renderEnemies(sf::RenderTarget* target)
{
	for (auto& it : this->enemies) {
		it.second->render(target);
	}
}

//Spawn Functions
void CombatComponent::spawnSlime(std::string key, float x, float y)
{
	this->enemies[key] = new Enemy(100.f, 2, "Assets/Enemies/slime-red.png",
		"Assets/Enemies/slime-red-idle.png", "Assets/Enemies/slime-red.png",
		"Assets/Enemies/slime-red.png", "Assets/Enemies/slime-red.png");
	this->enemies[key]->setPosition(x, y);
}

//Sprite Functions
void CombatComponent::initSprites()
{
	this->sprites["player"] = new Sprite(900.f, 500.f, 16.f, 16.f, 4.0f, "Assets/SpriteSheets/Ode Walking S-Sheet.png", false);
}

void CombatComponent::renderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites) {
		it.second->render(target);
	}
}