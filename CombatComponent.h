#pragma once
//Entities
#include"Enemy.h"
#include"PlayerCombat.h"
class CombatComponent
{
public:
	//Constructors and Deconstructors
	CombatComponent();
	~CombatComponent();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Detection Functions
	void detectCollision();
	void detectPlayerDamage();
	void detectPlayerAttack();
	void detectEnemyDeath();

	//Enemy Functions
	void updateEnemies();
	void renderEnemies(sf::RenderTarget* target);

	//Spawn Functions
	void spawnSlime(std::string key, float x, float y);

	Enemy* enemy;

	PlayerCombat* playerCombat;

	//std::vector<Enemy*> enemies;
	std::map<std::string, Enemy*> enemies;

private:

};

