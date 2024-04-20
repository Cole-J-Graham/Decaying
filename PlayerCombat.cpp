#include "PlayerCombat.h"
//Constructors and Destructors
PlayerCombat::PlayerCombat()
{
	this->projectile_speed = 15;
	this->player_projectile.setScale(3.0f, 3.0f);
	this->attacking = false;
	this->sheathed = true;
	this->resetAnimation = false;
	this->moveSelection = 1;

	//Initialization
	this->loadAssets();
	this->initRects();
	this->initSprites();
	this->character = new Character(&this->sprites["player"]->getSprite());
}

PlayerCombat::~PlayerCombat()
{
	//Delete Character
	delete this->character;

	//Deconstruct Rectangles
	auto ir = this->rectangles.begin();
	for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
		delete ir->second;
	}

	//Deconstruct Sprites
	delete this->spriteOverlay;
	auto is = this->sprites.begin();
	for (is = this->sprites.begin(); is != this->sprites.end(); ++is) {
		delete is->second;
	}
}

//Core Functions
void PlayerCombat::update(const sf::Vector2f mousePos, sf::Vector2f playerPos)
{
	this->character->update(mousePos);
	this->detectAnimationPos(mousePos, playerPos);
	this->character->priorityAnimations();
	this->updateRects(playerPos);
}

void PlayerCombat::render(sf::RenderTarget* target)
{
	//Render Attacks
	if(this->attacking)
		target->draw(this->player_projectile);

	//Render Everything Else
	this->character->render(target);
	this->renderRects(target);
	this->renderSprites(target);
}

//Detection Functions
void PlayerCombat::detectCombatKeybinds(const sf::Vector2f mousePos, sf::Sprite& sprite)
{
	this->detectUnsheathe(mousePos);
	this->detectAttack(mousePos, sprite);
	this->detectMoveSelect();
}

void PlayerCombat::detectUnsheathe(const sf::Vector2f mousePos)
{
	this->elapsed = this->clock.getElapsedTime();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->sheathed && this->elapsed.asSeconds() > 0.2) {
		this->sheathed = false;
		clock.restart();
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !this->sheathed && this->elapsed.asSeconds() > 0.2) {
		this->sheathed = true;
		clock.restart();
	}
}

void PlayerCombat::detectAttack(const sf::Vector2f mousePos, sf::Sprite& sprite)
{
	if (!this->sheathed) {
		switch (this->moveSelection) {
		case 1:
			this->fireCrossbow(mousePos, sprite);
			break;
		case 2:
			this->slashSword();
			break;
		}
	}
}

void PlayerCombat::detectMoveSelect()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		this->spriteOverlay->setPosition(530.f, 950.f);
		this->moveSelection = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		this->spriteOverlay->setPosition(600.f, 950.f);
		this->moveSelection = 2;
	}
}

//Animation Functions
void PlayerCombat::detectAnimationPos(const sf::Vector2f mousePos, sf::Vector2f playerPos)
{
	if (!this->sheathed) {
		// Inside your game loop:
		sf::Vector2f direction = mousePos - playerPos;
		direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y); // Normalize

		// Calculate the angle (in radians) from the positive x-axis
		float angle = std::atan2(direction.y, direction.x);
		float M_PI = 3.14159;
		// Convert angle to degrees (0 to 360)
		if (angle < 0) {
			angle += 2 * M_PI;
		}
		float degrees = angle * 180.0f / M_PI;

		// Determine the quadrant based on the angle
		this->quadrant = static_cast<int>((degrees + 22.5f) / 45.0f) % 8;

		switch (this->quadrant) {
		case 0: // RIGHT
			this->character->animation->play("WALKRIGHT");
			this->rectangles["PLAYERATTACK"]->setOrientation(playerPos.x + 65, playerPos.y + 15, 75, 95);
			break;
		case 1: // BOTTOM-RIGHT
			this->character->animation->play("WALKRIGHTDOWN");
			this->rectangles["PLAYERATTACK"]->setOrientation(playerPos.x + 45, playerPos.y + 70, 95, 75);
			break;
		case 2: // BOTTOM
			this->character->animation->play("WALKDOWN");
			this->rectangles["PLAYERATTACK"]->setOrientation(playerPos.x + 16, playerPos.y + 70, 95, 75);
			break;
		case 3: // BOTTOM-LEfT
			this->character->animation->play("WALKLEFTDOWN");
			this->rectangles["PLAYERATTACK"]->setOrientation(playerPos.x - 13, playerPos.y + 70, 95, 75);
			break;
		case 4: // LEFT
			this->character->animation->play("WALKLEFT");
			this->rectangles["PLAYERATTACK"]->setOrientation(playerPos.x - 20, playerPos.y + 15, 75, 95);
			break;
		case 5: // TOP-LEFT
			this->character->animation->play("WALKLEFTUP");
			this->rectangles["PLAYERATTACK"]->setOrientation(playerPos.x - 13, playerPos.y - 13, 95, 75);
			break;
		case 6: // TOP
			this->character->animation->play("WALKUP");
			this->rectangles["PLAYERATTACK"]->setOrientation(playerPos.x + 16, playerPos.y - 10, 95, 75);
			break;
		case 7: // TOP-RIGHT
			this->character->animation->play("WALKRIGHTUP");
			this->rectangles["PLAYERATTACK"]->setOrientation(playerPos.x + 45, playerPos.y - 13, 95, 75);
			break;
		}
	}
}

void PlayerCombat::resetAnimationPos()
{
	//Reset Animation is used to ensure this function only plays when needed
	if (!this->resetAnimation) {
		this->character->animation->setAnimation("WALKDOWN", "Assets/SpriteSheets/Ode Walking S-Sheet.png", 0.2);
		this->character->animation->setAnimation("WALKUP", "Assets/SpriteSheets/Ode Walking W-Sheet.png", 0.2);
		this->character->animation->setAnimation("WALKLEFT", "Assets/SpriteSheets/Ode Walking A-Sheet.png", 0.2);
		this->character->animation->setAnimation("WALKRIGHT", "Assets/SpriteSheets/Ode Walking D-Sheet.png", 0.2);
		this->character->animation->setAnimation("WALKLEFTUP", "Assets/SpriteSheets/Ode Walking AW-Sheet.png", 0.2);
		this->character->animation->setAnimation("WALKRIGHTUP", "Assets/SpriteSheets/Ode Walking DW-Sheet.png", 0.2);
		this->character->animation->setAnimation("WALKLEFTDOWN", "Assets/SpriteSheets/Ode Walking AS-Sheet.png", 0.2);
		this->character->animation->setAnimation("WALKRIGHTDOWN", "Assets/SpriteSheets/Ode Walking DS-Sheet.png", 0.2);
		this->resetAnimation = true;
	}
}

//Attack Functions
void PlayerCombat::fireCrossbow(const sf::Vector2f mousePos, sf::Sprite& sprite)
{
	//Algorithm for mouse position
	this->proj = atan2(mousePos.y - sprite.getPosition().y, mousePos.x - sprite.getPosition().x);
	//Make projectile rotate towards mouse
	sf::Vector2f curPos = player_projectile.getPosition();
	float dx = curPos.x - mousePos.x;
	float dy = curPos.y - mousePos.y;
	float rotation = (atan2(dy, dx)) * 180 / pie;


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player_projectile.move(this->projectile_speed * cos(this->proj),
			this->projectile_speed * sin(this->proj));
		this->attacking = true;
	}
	else {
		player_projectile.setRotation(rotation);
		player_projectile.setPosition(sprite.getPosition().x + 30, sprite.getPosition().y + 30);
		this->attacking = false;
	}
}

void PlayerCombat::slashSword()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->resetAnimation = false;
		this->attacking = true;
		this->character->animation->setAnimation("WALKDOWN", "Assets/SpriteSheets/Ode Attack S-Sheet.png", 0.17);
		this->character->animation->setAnimation("WALKLEFTDOWN", "Assets/SpriteSheets/Ode Attack AS-Sheet.png", 0.17);
		this->character->animation->setAnimation("WALKRIGHTDOWN", "Assets/SpriteSheets/Ode Attack DS-Sheet.png", 0.17);
		this->character->animation->setAnimation("WALKLEFTUP", "Assets/SpriteSheets/Ode Attack AW-Sheet.png", 0.17);
		this->character->animation->setAnimation("WALKRIGHTUP", "Assets/SpriteSheets/Ode Attack DW-Sheet.png", 0.17);
		this->character->animation->setAnimation("WALKUP", "Assets/SpriteSheets/Ode Attack W-Sheet.png", 0.17);
		this->character->animation->setAnimation("WALKLEFT", "Assets/SpriteSheets/Ode Attack A-Sheet.png", 0.17);
		this->character->animation->setAnimation("WALKRIGHT", "Assets/SpriteSheets/Ode Attack D-Sheet.png", 0.17);
	}
	else {
		this->resetAnimationPos();
		this->attacking = false;
	}
}

//Asset Functions
void PlayerCombat::initSprites()
{
	this->sprites["player"] = new Sprite(884.f, 484.f, 32.f, 32.f, 4.0f, "Assets/SpriteSheets/Ode Walking S-Sheet.png", false);
	this->sprites["SWORD_ICON"] = new Sprite(600.f, 950.f, 16.f, 16.f, 4.0f, "Assets/Icons/Sword Icon.png", false);
	this->sprites["CROSSBOW_ICON"] = new Sprite(530.f, 950.f, 16.f, 16.f, 4.0f, "Assets/Icons/Crossbow Icon.png", false);
	this->spriteOverlay = new Sprite(530.f, 950.f, 16.f, 16.f, 4.0f, "Assets/Icons/Icon Selected.png", false);
}

void PlayerCombat::renderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites) {
		it.second->render(target);
	}
	this->spriteOverlay->render(target);
}

void PlayerCombat::loadAssets()
{
	this->player_projectile_tex.loadFromFile("Assets/Projectiles/test.png");
	this->player_projectile.setTexture(player_projectile_tex);
}

//Rectangle Functions
void PlayerCombat::updateRects(sf::Vector2f playerPos)
{
	this->rectangles["PLAYERCOLLISION"]->setPosition(playerPos.x + 35, playerPos.y + 35);
}

void PlayerCombat::initRects()
{
	this->rectangles["PLAYERATTACK"] = new Rectangle(0, 0, 10, 10, sf::Color::Blue,
		sf::Color::White, 1.f, true);
	this->rectangles["PLAYERCOLLISION"] = new Rectangle(0, 0, 55, 60, sf::Color::Blue,
		sf::Color::White, 1.f, true);
}

void PlayerCombat::renderRects(sf::RenderTarget* target)
{
	for (auto& it : this->rectangles) {
		it.second->render(target);
	}
}