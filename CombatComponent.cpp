#include "CombatComponent.h"
//Constructors and Deconstructors
CombatComponent::CombatComponent()
{
	this->playerCombat = new PlayerCombat();
}

CombatComponent::~CombatComponent()
{
	
	delete this->playerCombat;
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
	this->playerCombat->character->inventory->update(this->playerCombat->sprites["player"]->getSprite(), mousePos);
	this->playerCombat->detectCombatKeybinds(mousePos, this->playerCombat->sprites["player"]->getSprite());
	this->playerCombat->update(mousePos, this->playerCombat->character->player->getPosition());
	this->detectCollision();
}

void CombatComponent::render(sf::RenderTarget* target)
{
	this->playerCombat->render(target);
	this->renderEnemies(target);
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
		if (this->playerCombat->rectangles["PLAYERCOLLISION"]->getGlobalBounds().intersects(it.second->rectangles["HITBOX"]->getGlobalBounds())) {
			this->playerCombat->character->getHp() -= it.second->getDamage();
		}
	}
}

void CombatComponent::detectPlayerAttack()
{
	for (auto& it : this->enemies) {
		if (this->playerCombat->getPlayerProjectile().getGlobalBounds().intersects(it.second->getGlobalBounds())) {
			it.second->getHp() -= this->playerCombat->character->getDamage();
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
		it.second->update(this->playerCombat->character->player->getPosition());
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
	this->enemies[key] = new Enemy(100.f, 2, 24, "Assets/Enemies/slime-red-idle.png",
		"Assets/Enemies/slime-red-idle.png", "Assets/Enemies/slime-red-idle.png",
		"Assets/Enemies/slime-red-idle.png", "Assets/Enemies/slime-red-idle.png");
	this->enemies[key]->setPosition(x, y);
}