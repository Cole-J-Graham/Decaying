#pragma once
#include<iostream>
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
		int maxFrame, float offset, float speed, int sheet);
	void play(std::string key);
	void reset(std::string key);

private:
	//Animation Class
	class Animation
	{
	public:
		//Constructors and Deconstructors
		Animation(sf::Sprite* sprite, sf::Texture& texture, int maxFrame, float offset, float speed,
			int sheet) : sprite(sprite), texture(texture)
		{
			this->sprite = sprite;
			this->texture = texture;
			this->animationFrame = 0;
			this->maxFrame = maxFrame;
			this->offset = offset;
			this->speed = speed;
			this->sheet = sheet;
		}

		//Core Functions
		void animateTimer()
		{
			//Start animation timer
			this->animationElapsed = this->animationTimer.getElapsedTime();
			if (this->animationElapsed.asSeconds() >= speed)
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
				sheet = offset * this->animationFrame;
			}
			sprite->setTexture(texture);
			sprite->setTextureRect(sf::IntRect(sheet, 0, 16, 16));
		}
		void reset()
		{
			this->animationFrame = 0;
			this->animationTimer.restart();
		}

	private:
		sf::Texture& texture;
		int animationFrame;
		int maxFrame;
		float offset;
		float speed;
		int sheet;

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

