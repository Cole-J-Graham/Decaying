#pragma once
//Entities
#include"Enemy.h"
#include"Character.h"
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

	//Enemy Functions
	void updateEnemies();
	void renderEnemies(sf::RenderTarget* target);

	//Spawn Functions
	void spawnSlime(float x, float y);

	//Sprite Functions
	void initSprites();
	void renderSprites(sf::RenderTarget* target);

	//Asset Functions
	void loadAssets();

	Character* character;

	std::map<std::string, Sprite*> sprites;

	Enemy* enemy;

	std::vector<Enemy*> enemies;

private:

	//Assets
	sf::Texture zin;

};

