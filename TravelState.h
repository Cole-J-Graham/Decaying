#pragma once
#include<SFML/Graphics.hpp>
#include"State.h"

class TravelState : public State
{
public:
	//Constructors and Destructors
	TravelState();
	~TravelState();

	//Core Travel Functions
	void loadingOnTile(std::vector<std::vector<sf::Sprite>>& inSprite, std::vector<std::vector<int>> tiles, sf::Texture& tex1, sf::Texture& tex2, sf::Texture& tex3, sf::Texture& tex4);
	void checkForMovement();
	void loadMap(sf::RenderWindow& window);
	void loadCollisionMap(sf::RenderWindow& window);

	//State Functions
	void endState();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

	//Assets
	void setAssets();
	void animateTimer();
	void animateFourFrames(sf::Sprite& inSprite, int xOffset, float posX, float posY);

private:
	std::vector<std::vector<sf::Sprite>> tileMap;
	std::vector<std::vector<sf::RectangleShape>> collisionMap;

	sf::Texture forestTile1;
	sf::Texture forestTile2;
	sf::Texture forestTile3;
	sf::Texture forestTile4;
	//sf::RectangleShape playerDetection;

	//Core Variables
	float gridSizeF;
	int col;
	int row;

	int frame;
	bool frameInit;

	//Assets
	sf::Texture mapImage;
	sf::Sprite mapSprite;

	sf::Sprite zinPixelSprite;
	sf::Texture zinWalkDown;
	sf::Texture zinWalkLeft;
	sf::Texture zinWalkRight;
	sf::Texture zinWalkUp;

	//Animation Variables
	int sheetX;
	int sheetY;

	bool playerMoving;
	int animationFrame;
	float movementSpeed;
	sf::Vector2f velocity;

	sf::Clock timer;
	sf::Time elapsed;




};