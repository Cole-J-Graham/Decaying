#pragma once
#include"Character.h"
#include"Rectangle.h"
#include<Math.h>
class PlayerCombat
{
public:
	//Constructors and Destructors
	PlayerCombat();
	~PlayerCombat();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Detection Functions
	void detectCombatKeybinds(const sf::Vector2f mousePos, sf::Sprite& sprite);
	void detectUnsheathe(const sf::Vector2f mousePos);
	void detectAttack(const sf::Vector2f mousePos, sf::Sprite& sprite);
	void detectMoveSelect();
	void detectOctMousePosition(const sf::Vector2f mousePos);

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
	sf::Sprite& getPlayerProjectile() { return this->player_projectile; }
	std::map<std::string, Sprite*> sprites;
	Character* character;

private:
	sf::Clock clock;
	sf::Time elapsed;
	std::map<std::string, Rectangle*> rectangles;
	Sprite* spriteOverlay;

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

