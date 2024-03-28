#pragma once
//Modules
#include"Inventory.h"
#include"CombatModule.h"
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

	//Detection Functions
	void detectOctMousePosition(const sf::Vector2f mousePos);

	//Movement Functions
	void initAnimations();
	void characterMovement();
	void walk();
	void roll();
	void sprint();

	//Asset Functions
	void loadAssets();

	//Rectangle Functions
	void initRects();
	void updateRects();
	void renderRects(sf::RenderTarget* target);

	//Accessors
	sf::Vector2f& getVelocity() { return this->velocity; };

	CombatModule* combat;
	Inventory* inventory;

private:
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
	AnimationModule* animation;
	sf::Sprite* zin;

	//Assets
	sf::Texture zin_walk_up;
	sf::Texture zin_walk_down;
	sf::Texture zin_walk_left;
	sf::Texture zin_walk_right;

	sf::Texture zin_walk_diagnol_left_down;
	sf::Texture zin_walk_diagnol_right_down;
	sf::Texture zin_walk_diagnol_right_up;
	sf::Texture zin_walk_diagnol_left_up;

	sf::Texture zin_roll_up;
	sf::Texture zin_roll_down;
	sf::Texture zin_roll_left;
	sf::Texture zin_roll_right;
};

