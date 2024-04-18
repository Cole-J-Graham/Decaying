#pragma once
#include<iostream>
#include<random>
#include"Sprite.h"
#include<stack>
class AnimationModule
{
public:
	//Constructors and Destructors
	AnimationModule(sf::Sprite* sprite);
	~AnimationModule();

	//Core Functions
	void addAnimation(std::string key, sf::Texture& texture,
		int maxFrame, float offset, float speed, int sheetSize, float rand);
	void play(std::string key);
	void reset(std::string key);
	void setAnimation(std::string key, std::string texture, float speed);

private:
	//Animation Class
	class Animation
	{
	public:
		//Constructors and Deconstructors
		Animation(sf::Sprite* sprite, sf::Texture& texture, int maxFrame, float offset, float speed,
			int sheetSize, float rand) : sprite(sprite), texture(texture)
		{
			this->sprite = sprite;
			this->texture = texture;
			this->animationFrame = 0;
			this->maxFrame = maxFrame;
			this->offset = offset;
			this->speed = speed;
			this->sheetSize = sheetSize;
			this->rand = rand;
		}

		//Core Functions
		void animateTimer()
		{
			//Get random number for randomized animations timing
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> random_number(0, this->rand);
			//Start animation timer
			this->animationElapsed = this->animationTimer.getElapsedTime();
			if (this->animationElapsed.asSeconds() >= speed + random_number(rng))
			{
				//Animate frames at the speed
				this->animationFrame++;
				this->animationTimer.restart();
			}
			else if (this->animationFrame >= maxFrame)
			{
				//Reset if max frames has been reached
				this->animationFrame = 0;
			}
		}
		void animateSheet()
		{
			this->animateTimer();
			if (this->animationFrame < maxFrame)
			{
				currentOffset = offset * this->animationFrame;
			}
			sprite->setTexture(texture);
			sprite->setTextureRect(sf::IntRect(currentOffset, 0, sheetSize, sheetSize));
		}
		void reset()
		{
			this->animationFrame = 0;
			this->animationTimer.restart();
		}
		void setAnimation(std::string texture, float speed)
		{
			this->speed = speed;
			this->texture.loadFromFile(texture);
		}

	private:
		sf::Texture& texture;
		int animationFrame;
		int maxFrame;
		float offset;
		float speed;
		float rand;
		int sheetSize;
		int currentOffset;

		sf::Sprite* sprite;
		sf::Clock animationTimer;
		sf::Time animationElapsed;
	};

	//AnimationModule Variables
	std::map<std::string, Animation*> animations;
	sf::Sprite* sprite;

	sf::Vector2f velocity;
	sf::Clock dodge_timer;
	sf::Time dodge_elapsed;

	int animationFrame;
	float movementSpeed;

};

