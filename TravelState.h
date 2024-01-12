#pragma once
#include"State.h"
#include"TileMap.h"

class TravelState : public State
{
public:
	//Constructors and Destructors
	TravelState();
	~TravelState();

	//Core Travel Functions
	void setLocation();
	void checkForMovement();

	//State Functions
	void endState();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

	//Assets
	void setAssets();
	void loadAssets();
	void animateTimer();
	void animateFourFrames(sf::Sprite& inSprite, int xOffset, float posX, float posY);

private:
	//Core Variables
	int location;
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