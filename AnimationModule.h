#pragma once
#include<iostream>
#include"Sprite.h"
class AnimationModule
{
public:
	//Constructors and Destructors
	AnimationModule(sf::Sprite* sprite);
	~AnimationModule();

	//Core Functions
	/*void animateSheet(float speed, bool action, int offset, int sheet, int maxFrame);
	void animateTimer(int maxFrame, float speed);*/
	void addAnimation(std::string key, sf::Texture& texture,
		int maxFrame, float offset, float speed, int sheet);
	void play(std::string key);

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
			std::cout << animationFrame << "\n";
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

	bool last_key_w;
	bool last_key_a;
	bool last_key_s;
	bool last_key_d;
	bool player_walking;
	bool player_rolling;

	int animationFrame;
	float movementSpeed;

};

