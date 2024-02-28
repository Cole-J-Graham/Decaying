#pragma once
#include"Rectangle.h"
#include<SFML/Graphics.hpp>
#include<iostream>
#include<Math.h>
class CombatModule
{
public:
	//Constructors and Destructors
	CombatModule();
	~CombatModule();

	//Core Functions
	void renderAttacks(sf::RenderTarget* target);

	//Detection Functions
	void detectCombatKeybinds(const sf::Vector2f mousePos, sf::Sprite& sprite);
	void detectUnsheathe(const sf::Vector2f mousePos);
	void detectAttack(const sf::Vector2f mousePos, sf::Sprite& sprite);
	void detectOctMousePosition(const sf::Vector2f mousePos);

	//Asset Functions
	void loadAssets();

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

private:
	sf::Clock clock;
	sf::Time elapsed;
	std::map<std::string, Rectangle*> rectangles;

	bool sheathed;
	bool attacking;
	float proj;
	float projectile_speed;
	sf::FloatRect area;
	sf::Texture player_projectile_tex;
	sf::Sprite player_projectile;

};

