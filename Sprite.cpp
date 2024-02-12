#include "Sprite.h"
//Constructors and Destructors
Sprite::Sprite(float x, float y, float pixel_width, float pixel_height, 
	float scale, sf::Texture& sprite_texture)
{
	this->sprite.setTexture(sprite_texture);
	this->sprite.setPosition(x, y);
	this->sprite.setScale(scale, scale);
	this->sprite.setTextureRect(sf::IntRect(sheet_walk_x, sheet_walk_y, pixel_width, pixel_height));

	//Animation Variables
	this->movementSpeed = 1.5f;
	this->animationFrame = -1;

	this->velocity.x = 0.f;
	this->velocity.y = 0.f;

	this->frame = 0;
	this->frameInit = false;

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

	this->loadAssets();
}

Sprite::~Sprite()
{

}

//Core Functions
void Sprite::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

//Animation Functions
void Sprite::animateMovement()
{
	this->animateWalk(zin_walk_up, zin_walk_down, zin_walk_left, zin_walk_right);
	this->animateRoll(zin_roll_up, zin_roll_down, zin_roll_left, zin_roll_right);
}

const sf::Vector2f Sprite::getPosition() const
{
	return this->sprite.getPosition();
}

//Private Animation Functions
void Sprite::animateTimer(float speed)
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

void Sprite::animateSheet(float speed, bool movement, int sheet)
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
		sprite.setTextureRect(sf::IntRect(sheet, sheet_walk_y, 16, 16));
	}
}

void Sprite::animateWalk(sf::Texture& walk_up, sf::Texture& walk_down, sf::Texture& walk_left, sf::Texture& walk_right)
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
		this->sprite.setTexture(walk_up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->player_walking = true;
		this->last_key_w = false;
		this->last_key_a = false;
		this->last_key_s = true;
		this->last_key_d = false;
		this->sprite.setTexture(walk_down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->player_walking = true;
		this->last_key_w = false;
		this->last_key_a = true;
		this->last_key_s = false;
		this->last_key_d = false;
		this->sprite.setTexture(walk_left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->player_walking = true;
		this->last_key_w = false;
		this->last_key_a = false;
		this->last_key_s = false;
		this->last_key_d = true;
		this->sprite.setTexture(walk_right);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->player_walking = true;
		this->sprite.setTexture(zin_walk_diagnol_left_down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->player_walking = true;
		this->sprite.setTexture(zin_walk_diagnol_right_down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->player_walking = true;
		this->sprite.setTexture(zin_walk_diagnol_left_up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->player_walking = true;
		this->sprite.setTexture(zin_walk_diagnol_right_up);
	}

	//Character stops moving
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sheet_walk_x = 0;
		sheet_walk_y = 0;
		sprite.setTextureRect(sf::IntRect(sheet_walk_x, sheet_walk_y, 16, 16));
		this->player_walking = false;
	}
}

void Sprite::animateRoll(sf::Texture& roll_up, sf::Texture& roll_down, sf::Texture& roll_left, sf::Texture& roll_right)
{
	//Set rolling to true if able to roll time wise
	dodge_elapsed = dodge_timer.getElapsedTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && dodge_elapsed.asSeconds() >= 0.5) {
		dodge_timer.restart();
		//Reset Animation Frame
		this->animationFrame = -1;
		this->player_rolling = true;
	}
	else if (!this->player_rolling && dodge_elapsed.asSeconds() >= 0.4) {
		this->sheet_roll_x = 0;
	}

	//Animate the roll if rolling is true
	if (this->player_rolling) {
		//Animate rolling
		if (last_key_w) {
			this->sprite.setTexture(roll_up);
		}
		if (last_key_s) {
			this->sprite.setTexture(roll_down);
		}
		if (last_key_a) {
			this->sprite.setTexture(roll_left);
		}
		if (last_key_d) {
			this->sprite.setTexture(roll_right);
		}
		//Animate roll cycle
		this->animateSheet(0.16, player_rolling, sheet_roll_x);
	}
}

//Assets
void Sprite::loadAssets()
{
	this->zin_walk_up.loadFromFile("Assets/SpriteSheets/zinWalkUpSpriteSheet.png");
	this->zin_walk_down.loadFromFile("Assets/SpriteSheets/zinWalkSpriteSheet.png");
	this->zin_walk_left.loadFromFile("Assets/SpriteSheets/zinWalkLeftSpriteSheet.png");
	this->zin_walk_right.loadFromFile("Assets/SpriteSheets/zinWalkRightSpriteSheet.png");
	this->zin_walk_diagnol_left_down.loadFromFile("Assets/SpriteSheets/zinWalkDiagnolAS.png");
	this->zin_walk_diagnol_right_down.loadFromFile("Assets/SpriteSheets/zinWalkDiagnolDS.png");
	this->zin_walk_diagnol_left_up.loadFromFile("Assets/SpriteSheets/zinWalkDiagnolAW.png");
	this->zin_walk_diagnol_right_up.loadFromFile("Assets/SpriteSheets/zinWalkDiagnolDW.png");

	this->zin_roll_up.loadFromFile("Assets/SpriteSheets/zinDodgeRollSpriteSheetUp.png");
	this->zin_roll_down.loadFromFile("Assets/SpriteSheets/zinDodgeRollSpriteSheet.png");
	this->zin_roll_left.loadFromFile("Assets/SpriteSheets/zinDodgeRollSpriteSheetLeft.png");
	this->zin_roll_right.loadFromFile("Assets/SpriteSheets/zinDodgeRollSpriteSheetRight.png");
}