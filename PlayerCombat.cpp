#include "PlayerCombat.h"
//Constructors and Destructors
PlayerCombat::PlayerCombat()
{
	this->projectile_speed = 15;
	this->player_projectile.setScale(3.0f, 3.0f);
	this->attacking = false;
	this->sheathed = true;

	//Initialization
	this->loadAssets();
	this->initRects();
}

PlayerCombat::~PlayerCombat()
{
	//Deconstruct Rectangles
	auto ir = this->rectangles.begin();
	for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
		delete ir->second;
	}
}

//Core Functions
void PlayerCombat::renderAttacks(sf::RenderTarget* target)
{
	//Render Attacks
	if(this->attacking)
		target->draw(this->player_projectile);

	//Render Everything Else
	this->renderRects(target);
}

//Detection Functions
void PlayerCombat::detectCombatKeybinds(const sf::Vector2f mousePos, sf::Sprite& sprite)
{
	this->detectUnsheathe(mousePos);
	this->detectAttack(mousePos, sprite);
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
}

//Asset Functions
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