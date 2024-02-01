#pragma once
//States
#include"State.h"
//Assets
#include"TileMap.h"
#include"Sprite.h"

class TravelState : public State
{
public:
	//Constructors and Destructors
	TravelState();
	~TravelState();

	//Core Travel Functions
	void setLocation();

	//State Functions
	void endState();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);

	//Sprite Functions
	void initSprites();
	void renderSprites(sf::RenderTarget* target);

	//Assets
	void setAssets();
	void loadAssets();

private:
	//Core Variables
	int location;

	std::map<std::string, Sprite*> sprites;

	//Assets
	sf::Texture mapImage;
	sf::Sprite mapSprite;

	sf::Texture zin_up;
	sf::Texture zin_down;
	sf::Texture zin_left;
	sf::Texture zin_right;




};