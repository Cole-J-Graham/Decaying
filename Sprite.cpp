#include "Sprite.h"
//Constructors and Destructors
Sprite::Sprite(float x, float y, float pixel_width, float pixel_height, 
	float scale, sf::Texture& sprite_texture)
{
	this->sprite.setTexture(sprite_texture);
	this->sprite.setPosition(x, y);
	this->sprite.setScale(scale, scale);
	this->sprite.setTextureRect(sf::IntRect(sheet_x, sheet_y, pixel_width, pixel_height));

	//Animation Variables
	this->movementSpeed = 1.5f;
	this->animationFrame = -1;

	this->velocity.x = 0.f;
	this->velocity.y = 0.f;

	this->frame = 0;
	this->frameInit = false;

	this->sheet_x = 0;
	this->sheet_y = 0;
}

Sprite::~Sprite()
{

}

//Core Functions
void Sprite::checkForMovement(sf::Texture& up, sf::Texture& down, sf::Texture& left, sf::Texture& right)
{
	//Animate walk cycle
	if (this->playerMoving) {
		this->animateTimer();
		switch (this->animationFrame) {
		case -1:
			sheet_x = 0;
			sheet_y = 0;
			break;
		case 0:
			sheet_x = 16;
			sheet_y = 0;
			break;
		case 1:
			sheet_x = 32;
			sheet_y = 0;
			break;
		case 2:
			sheet_x = 48;
			sheet_y = 0;
			break;
		}
	}

	//Set basic attributes for sprite
	sprite.setTextureRect(sf::IntRect(sheet_x, sheet_y, 16, 16));
	//Set velocities to 0 after usage
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;

	//Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		velocity.y += -movementSpeed;
		this->playerMoving = true;
		this->sprite.setTexture(up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y += movementSpeed;
		this->playerMoving = true;
		this->sprite.setTexture(down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x += -movementSpeed;
		this->playerMoving = true;
		this->sprite.setTexture(left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocity.x += movementSpeed;
		this->playerMoving = true;
		this->sprite.setTexture(right);
	}
	this->sprite.move(velocity);

	//Character stops moving
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sheet_x = 0;
		sheet_y = 0;
		this->playerMoving = false;
	}
}

void Sprite::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}


//Animation Functions
void Sprite::animateTimer()
{
	elapsed = timer.getElapsedTime();
	if (elapsed.asSeconds() >= 0.2f) {
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

void Sprite::animateFourFrames(sf::Sprite& inSprite, int xOffset, float x, float y)
{
	inSprite.setTextureRect(sf::IntRect(sheet_x, sheet_y, xOffset, xOffset));
	inSprite.setPosition(x, y);
	this->animateTimer();
	switch (this->animationFrame) {
	case -1:
		sheet_x = 0;
		sheet_y = 0;
		break;
	case 0:
		sheet_x = xOffset;
		sheet_y = 0;
		break;
	case 1:
		sheet_x = xOffset * 2;
		sheet_y = 0;
		break;
	case 2:
		sheet_x = xOffset * 3;
		sheet_y = 0;
		break;
	}
}