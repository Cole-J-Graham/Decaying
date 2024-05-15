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
	void update(sf::Vector2f playerPos, sf::Vector2f playerVelocity);
	void render(sf::RenderTarget* target);
	void moveNpcWithMap(sf::Vector2f playerVelocity);
	void followPlayer(sf::Vector2f playerPos);

	//Detection Functions
	void detectNpc(sf::Vector2f playerPos);
	void detectInteract(sf::Vector2f playerPos);
	void detectFollow(sf::Vector2f playerPos);

	//Animation Functions
	void updateAnimations();
	void initAnimations();

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);
	void updateRects();

	//Dialogue Functions
	void addDialogue(std::string text);
	void displayDialogue();

private:
	float x;
	float y;
	float moveSpeed;
	bool followingPlayer;

	sf::Clock dialogueTimer;
	sf::Time dialogueElapsed;

	AnimationModule* animation;
	std::map<std::string, sf::Texture> npcAnimations;
	sf::Sprite npc;
	std::string textureInput;
	sf::Texture npcTexture;
	std::stack<std::string> dialogue;
	std::map<std::string, Rectangle*> rectangles;
};
