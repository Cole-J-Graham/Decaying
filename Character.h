#pragma once
//Modules
#include"Inventory.h"
#include"AnimationModule.h"
class Character
{
public:
	//Constructors and Destructors
	Character(sf::Sprite* sprite);
	~Character();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Movement Functions
	void initAnimations();
	void characterMovement();
	void priorityAnimations();
	void walk();
	void roll();
	void sprint();

	//Asset Functions
	void loadAssets();

	//Rectangle Functions
	void initRects();
	void updateRects();
	void renderRects(sf::RenderTarget* target);

	Inventory* inventory;
	sf::Sprite* player;

	//Accessors
	sf::Vector2f& getVelocity() { return this->velocity; };
	int& getHp() { return this->hp; }
	int& getDamage() { return this->damage; }

	sf::FloatRect getGlobalBounds() const { return this->player->getGlobalBounds(); }

	std::map<std::string, sf::Texture>& getPlayerAnimations() { return this->playerAnimations; };
	AnimationModule* animation;

private:
	//Variables
	int hp;
	int hpMax;
	int damage;

	//Movement
	int stamina;
	int staminaMax;
	float movementSpeed;
	float dodgeTime;

	sf::Vector2f velocity;
	sf::Clock dodge_timer;
	sf::Time dodge_elapsed;

	bool rolling;
	bool walking;

	std::map<std::string, Rectangle*> rectangles;

	//Assets
	std::map<std::string, sf::Texture> playerAnimations;
};

