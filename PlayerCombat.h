#pragma once
#include"Sprite.h"
#include"Rectangle.h"
#include<SFML/Graphics.hpp>
#include<iostream>
#include<Math.h>
class PlayerCombat
{
public:
	//Constructors and Destructors
	PlayerCombat();
	~PlayerCombat();

	//Core Functions
	void renderAttacks(sf::RenderTarget* target);

	//Detection Functions
	void detectCombatKeybinds(const sf::Vector2f mousePos, sf::Sprite& sprite);
	void detectUnsheathe(const sf::Vector2f mousePos);
	void detectAttack(const sf::Vector2f mousePos, sf::Sprite& sprite);
	void detectMoveSelect();

	//Attack Functions
	void fireCrossbow(const sf::Vector2f mousePos, sf::Sprite& sprite);
	void slashSword();

	//Asset Functions
	void initSprites();
	void renderSprites(sf::RenderTarget* target);
	void loadAssets();

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

	//Getters
	const bool& getSheathed() { return this->sheathed; };
	sf::Sprite& getPlayerProjectile() { return this->player_projectile; }
	std::map<std::string, Rectangle*>& getRectangles() { return this->rectangles; };

private:
	sf::Clock clock;
	sf::Time elapsed;
	std::map<std::string, Rectangle*> rectangles;
	std::map<std::string, Sprite*> sprites;

	int moveSelection;
	bool sheathed;
	bool attacking;
	const float pie = 3.14159265;
	float proj;
	float projectile_speed;
	sf::FloatRect area;
	sf::Texture player_projectile_tex;
	sf::Sprite player_projectile;
};

