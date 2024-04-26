#pragma once
#include"AnimationModule.h"
#include"Rectangle.h"
class Npcs
{
public:
	//Constructors and Deconstructors
	Npcs(float x, float y, std::string texture);
	~Npcs();

	//Core Functions
	void update(sf::FloatRect playerPos, sf::Vector2f playerVelocity);
	void render(sf::RenderTarget* target);
	void moveNpcWithMap(sf::Vector2f playerVelocity);

	//Detection Functions
	void detectInteract(sf::FloatRect playerPos);

	//Animation Functions
	void updateAnimations();
	void initAnimations();

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);
	void updateRects();

private:
	float x;
	float y;

	AnimationModule* animation;
	std::map<std::string, sf::Texture> npcAnimations;
	sf::Sprite npc;
	std::string textureInput;
	sf::Texture npcTexture;
	std::stack<std::string> dialogue;
	std::map<std::string, Rectangle*> rectangles;
};

