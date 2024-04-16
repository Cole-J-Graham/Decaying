#include "PlayerCombat.h"
//Constructors and Destructors
PlayerCombat::PlayerCombat()
{
	this->projectile_speed = 15;
	this->player_projectile.setScale(3.0f, 3.0f);
	this->attacking = false;
	this->sheathed = true;
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
void PlayerCombat::update(const sf::Vector2f mousePos)
{
	this->character->update(mousePos);
	this->detectOctMousePosition(mousePos);
	this->character->priorityAnimations();
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

void PlayerCombat::detectOctMousePosition(const sf::Vector2f mousePos)
{
	if (!this->sheathed) {
		if (this->rectangles["Quad1"]->getGlobalBounds().contains(mousePos)) {
			this->character->animation->play("WALKLEFTUP");
		}
		else if (this->rectangles["Quad2"]->getGlobalBounds().contains(mousePos)) {
			this->character->animation->play("WALKUP");
		}
		else if (this->rectangles["Quad3"]->getGlobalBounds().contains(mousePos)) {
			this->character->animation->play("WALKRIGHTUP");
		}
		else if (this->rectangles["Quad4"]->getGlobalBounds().contains(mousePos)) {
			this->character->animation->play("WALKLEFT");
		}
		else if (this->rectangles["Quad5"]->getGlobalBounds().contains(mousePos)) {
			this->character->animation->play("WALKRIGHT");
		}
		else if (this->rectangles["Quad6"]->getGlobalBounds().contains(mousePos)) {
			this->character->animation->play("WALKLEFTDOWN");
		}
		else if (this->rectangles["Quad7"]->getGlobalBounds().contains(mousePos)) {
			this->character->animation->play("WALKDOWN");
		}
		else if (this->rectangles["Quad8"]->getGlobalBounds().contains(mousePos)) {
			this->character->animation->play("WALKRIGHTDOWN");
		}
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
		this->character->animation->play("SLASHDOWN");
	}
}

//Asset Functions
void PlayerCombat::initSprites()
{
	this->sprites["player"] = new Sprite(900.f, 500.f, 16.f, 16.f, 4.0f, "Assets/SpriteSheets/Ode Walking S-Sheet.png", false);
	this->sprites["SWORD_ICON"] = new Sprite(600.f, 950.f, 16.f, 16.f, 4.0f, "Assets/Icons/Sword Icon.png", false);
	this->sprites["CROSSBOW_ICON"] = new Sprite(530.f, 950.f, 16.f, 16.f, 4.0f, "Assets/Icons/Crossbow Icon.png", false);
	this->spriteOverlay = new Sprite(600.f, 950.f, 16.f, 16.f, 4.0f, "Assets/Icons/Icon Selected.png", false);
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
void PlayerCombat::initRects()
{
	this->rectangles["Quad1"] = new Rectangle(0, 0, 640, 360, sf::Color::Blue,
		sf::Color::White, 1.f, true);
	this->rectangles["Quad2"] = new Rectangle(640, 0, 640, 360, sf::Color::Red,
		sf::Color::White, 1.f, true);
	this->rectangles["Quad3"] = new Rectangle(1280, 0, 640, 360, sf::Color::Cyan,
		sf::Color::White, 1.f, true);
	this->rectangles["Quad4"] = new Rectangle(0, 360, 640, 360, sf::Color::Magenta,
		sf::Color::White, 1.f, true);
	this->rectangles["Quad5"] = new Rectangle(1280, 360, 640, 360, sf::Color::Red,
		sf::Color::White, 1.f, true);
	this->rectangles["Quad6"] = new Rectangle(0, 720, 640, 360, sf::Color::Yellow,
		sf::Color::White, 1.f, true);
	this->rectangles["Quad7"] = new Rectangle(640, 720, 640, 360, sf::Color::Green,
		sf::Color::White, 1.f, true);
	this->rectangles["Quad8"] = new Rectangle(1280, 720, 640, 360, sf::Color::White,
		sf::Color::White, 1.f, true);
}

void PlayerCombat::renderRects(sf::RenderTarget* target)
{
	for (auto& it : this->rectangles) {
		it.second->render(target);
	}
}