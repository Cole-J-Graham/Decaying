#include "AnimationModule.h"
//Constructors and Destructors
AnimationModule::AnimationModule(sf::Sprite* sprite)
{
	//Animation Variables
	this->sprite = sprite;

	this->movementSpeed = 1.5f;
	this->animationFrame = 1;
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
	int maxFrame, float offset, float speed, int sheetSize, float rand)
{
	this->animations[key] = new Animation(this->sprite, texture, maxFrame, offset, speed, sheetSize, rand);
}

void AnimationModule::play(std::string key)
{
	this->animations[key]->animateSheet();
}

void AnimationModule::reset(std::string key)
{
	this->animations[key]->reset();
}

void AnimationModule::setAnimation(std::string key, std::string texture, float speed)
{
	this->animations[key]->setAnimation(texture, speed);
}