#include "AnimationModule.h"
//COnsturctors and Destructors
AnimationModule::AnimationModule(sf::Sprite* sprite)
{
	//Animation Variables
	this->sprite = sprite;

	this->movementSpeed = 1.5f;
	this->animationFrame = 1;

	this->player_walking = false;
	this->player_rolling = false;

}

AnimationModule::~AnimationModule()
{
	//Deconstruct Animations
	auto ia = this->animations.begin();
	for (ia = this->animations.begin(); ia != this->animations.end(); ++ia) {
		delete ia->second;
	}
}

//Core Functions
void AnimationModule::addAnimation(std::string key, sf::Texture& texture, 
	int maxFrame, float offset, float speed, int sheet)
{
	this->animations[key] = new Animation(this->sprite, texture, maxFrame, offset, speed, sheet);
}

void AnimationModule::play(std::string key)
{
	this->animations[key]->animateSheet();
}