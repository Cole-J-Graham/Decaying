#pragma once
//Modules
#include"CombatModule.h"
#include"AnimationModule.h"
class Character
{
public:
	//Constructors and Destructors
	Character(sf::Sprite* sprite);
	~Character();

	//Core Functions
	void updateCharacter(const sf::Vector2f mousePos);

	//Detection Functions
	void detectOctMousePosition(const sf::Vector2f mousePos);

	//Asset Functions
	void loadAssets();

	CombatModule* combat;

private:
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

