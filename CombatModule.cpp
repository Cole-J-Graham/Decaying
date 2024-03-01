#include "CombatModule.h"
//Constructors and Destructors
CombatModule::CombatModule()
{
	this->projectile_speed = 15;
	this->player_projectile.setScale(3.0f, 3.0f);
	this->attacking = false;
	this->sheathed = true;

	//Initialization
	this->loadAssets();
	this->initRects();
}

CombatModule::~CombatModule()
{
	//Deconstruct Rectangles
	auto ir = this->rectangles.begin();
	for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
		delete ir->second;
	}
}

//Core Functions
void CombatModule::renderAttacks(sf::RenderTarget* target)
{
	//Render Attacks
	if(this->attacking)
		target->draw(this->player_projectile);

	//Render Everything Else
	this->renderRects(target);
}

//Detection Functions
void CombatModule::detectCombatKeybinds(const sf::Vector2f mousePos, sf::Sprite& sprite)
{
	this->detectUnsheathe(mousePos);
	this->detectAttack(mousePos, sprite);
}

void CombatModule::detectUnsheathe(const sf::Vector2f mousePos)
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

void CombatModule::detectAttack(const sf::Vector2f mousePos, sf::Sprite& sprite)
{
	if (!this->sheathed) {
		this->proj = atan2(mousePos.y - sprite.getPosition().y, mousePos.x - sprite.getPosition().x);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			player_projectile.move(this->projectile_speed * cos(this->proj),
				this->projectile_speed * sin(this->proj));
			this->attacking = true;
		}
		else {
			player_projectile.setPosition(sprite.getPosition().x, sprite.getPosition().y);
			this->attacking = false;
		}
	}
}

//Asset Functions
void CombatModule::loadAssets()
{
	this->player_projectile_tex.loadFromFile("Assets/Projectiles/test.png");
	this->player_projectile.setTexture(player_projectile_tex);
}

//Rectangle Functions
void CombatModule::initRects()
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

void CombatModule::renderRects(sf::RenderTarget* target)
{
	for (auto& it : this->rectangles) {
		it.second->render(target);
	}
}