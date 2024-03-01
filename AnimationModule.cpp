#include "AnimationModule.h"
//COnsturctors and Destructors
AnimationModule::AnimationModule(sf::Sprite* sprite)
{
	//Animation Variables
	this->sprite = sprite;

	this->movementSpeed = 1.5f;
	this->animationFrame = -1;

	this->velocity.x = 0.f;
	this->velocity.y = 0.f;

	this->sheet_walk_x = 0;
	this->sheet_walk_y = 0;

	this->sheet_roll_x = 0;
	this->sheet_roll_y = 0;

	this->last_key_w = false;
	this->last_key_a = false;
	this->last_key_s = false;
	this->last_key_d = false;

	this->player_walking = false;
	this->player_rolling = false;

	this->frame = 0;
	this->frameInit = false;
}

AnimationModule::~AnimationModule()
{

}

//Core Functions
void AnimationModule::animateTimer(float speed)
{
	elapsed = timer.getElapsedTime();
	if (elapsed.asSeconds() >= speed) {
		if (this->animationFrame == -1) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 0) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 1) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 2) {
			this->animationFrame = -1;
			timer.restart();
		}
	}
}

void AnimationModule::animateSheet(float speed, bool movement, int sheet)
{
	if (movement) {
		this->animateTimer(speed);
		switch (this->animationFrame) {
		case -1:
			sheet = 0;
			break;
		case 0:
			sheet = 16;
			break;
		case 1:
			sheet = 32;
			break;
		case 2:
			sheet = 48;
			this->player_rolling = false;
			break;
		}
		//Set basic attributes for sprite
		sprite->setTextureRect(sf::IntRect(sheet, sheet_walk_y, 16, 16));
	}
}

//Core Movement
void AnimationModule::animateMovement(sf::Texture& walk_up, sf::Texture& walk_down,
	sf::Texture& walk_left, sf::Texture& walk_right, sf::Texture& walk_diagnol_left_down,
	sf::Texture& walk_diagnol_right_down, sf::Texture& walk_diagnol_right_up,
	sf::Texture& walk_diagnol_left_up, sf::Texture& roll_up, sf::Texture& roll_down,
	sf::Texture& roll_left, sf::Texture& roll_right)
{
	this->animateWalk(walk_up, walk_down, walk_left, walk_right, walk_diagnol_left_down,
		walk_diagnol_right_down, walk_diagnol_right_up, walk_diagnol_left_up);
	this->animateRoll(roll_up, roll_down, roll_left, roll_right);
}

void AnimationModule::animateWalk(sf::Texture& walk_up, sf::Texture& walk_down, 
	sf::Texture& walk_left, sf::Texture& walk_right, sf::Texture& walk_diagnol_left_down,
	sf::Texture& walk_diagnol_right_down, sf::Texture& walk_diagnol_right_up,
	sf::Texture& walk_diagnol_left_up)
{
	//Animate walk cycle
	this->animateSheet(0.2, player_walking, sheet_walk_x);

	//Set velocities to 0 after usage
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;

	//Animate Walking
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->player_walking = true;
		this->last_key_w = true;
		this->last_key_a = false;
		this->last_key_s = false;
		this->last_key_d = false;
		this->sprite->setTexture(walk_up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->player_walking = true;
		this->last_key_w = false;
		this->last_key_a = false;
		this->last_key_s = true;
		this->last_key_d = false;
		this->sprite->setTexture(walk_down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->player_walking = true;
		this->last_key_w = false;
		this->last_key_a = true;
		this->last_key_s = false;
		this->last_key_d = false;
		this->sprite->setTexture(walk_left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->player_walking = true;
		this->last_key_w = false;
		this->last_key_a = false;
		this->last_key_s = false;
		this->last_key_d = true;
		this->sprite->setTexture(walk_right);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->player_walking = true;
		this->sprite->setTexture(walk_diagnol_left_down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->player_walking = true;
		this->sprite->setTexture(walk_diagnol_right_down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->player_walking = true;
		this->sprite->setTexture(walk_diagnol_left_up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->player_walking = true;
		this->sprite->setTexture(walk_diagnol_right_up);
	}

	//Character stops moving
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sheet_walk_x = 0;
		sheet_walk_y = 0;
		sprite->setTextureRect(sf::IntRect(sheet_walk_x, sheet_walk_y, 16, 16));
		this->player_walking = false;
	}
}

void AnimationModule::animateRoll(sf::Texture& roll_up, sf::Texture& roll_down, 
	sf::Texture& roll_left, sf::Texture& roll_right)
{
	//Set rolling to true if able to roll time wise
	dodge_elapsed = dodge_timer.getElapsedTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && dodge_elapsed.asSeconds() >= 0.5 && this->player_walking) {
		dodge_timer.restart();
		//Reset Animation Frame
		this->animationFrame = -1;
		this->player_rolling = true;
	}

	//Animate the roll if rolling is true
	if (this->player_rolling) {
		//Animate rolling
		if (last_key_w) {
			this->sprite->setTexture(roll_up);
		}
		if (last_key_s) {
			this->sprite->setTexture(roll_down);
		}
		if (last_key_a) {
			this->sprite->setTexture(roll_left);
		}
		if (last_key_d) {
			this->sprite->setTexture(roll_right);
		}
		//Animate roll cycle
		this->animateSheet(0.16, player_rolling, sheet_roll_x);
	}
}