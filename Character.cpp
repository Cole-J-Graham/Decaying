#include "Character.h"
//Constructors and Destructors
Character::Character(sf::Sprite* sprite)
{
	this->zin = sprite;

	//Initialization
	this->loadAssets();
	this->combat = new CombatModule();
	this->animation = new AnimationModule(this->zin);
	this->inventory = new Inventory();
	this->initAnimations();
	this->initRects();
	
	//Movement
	this->rolling = false;

	this->dodgeTime = 0.4;
	this->stamina = 100;
	this->staminaMax = 100;
	this->movementSpeed = 1.5f;
	this->velocity.x = 0;
	this->velocity.y = 0;
}

Character::~Character()
{
	delete this->animation;
	delete this->combat;
	delete this->inventory;

	//Deconstruct Rectangles
	auto ir = this->rectangles.begin();
	for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
		delete ir->second;
	}
}

//Core Functions
void Character::update(const sf::Vector2f mousePos)
{
	this->inventory->checkForInput();
	this->characterMovement();
	this->detectOctMousePosition(mousePos);
	this->updateRects();
}

void Character::render(sf::RenderTarget* target)
{
	this->renderRects(target);
	this->inventory->render(target);
	combat->renderAttacks(target);
}

//Detection Functions
void Character::detectOctMousePosition(const sf::Vector2f mousePos)
{
	if (!combat->getSheathed()) {
		if (combat->getRectangles()["Quad1"]->getGlobalBounds().contains(mousePos)) {
			this->zin->setTexture(this->zin_walk_diagnol_left_up);
		}
		else if (combat->getRectangles()["Quad2"]->getGlobalBounds().contains(mousePos)) {
			this->zin->setTexture(this->zin_walk_up);
		}
		else if (combat->getRectangles()["Quad3"]->getGlobalBounds().contains(mousePos)) {
			this->zin->setTexture(this->zin_walk_diagnol_right_up);
		}
		else if (combat->getRectangles()["Quad4"]->getGlobalBounds().contains(mousePos)) {
			this->zin->setTexture(this->zin_walk_left);
		}
		else if (combat->getRectangles()["Quad5"]->getGlobalBounds().contains(mousePos)) {
			this->zin->setTexture(this->zin_walk_right);
		}
		else if (combat->getRectangles()["Quad6"]->getGlobalBounds().contains(mousePos)) {
			this->zin->setTexture(this->zin_walk_diagnol_left_down);
		}
		else if (combat->getRectangles()["Quad7"]->getGlobalBounds().contains(mousePos)) {
			this->zin->setTexture(this->zin_walk_down);
		}
		else if (combat->getRectangles()["Quad8"]->getGlobalBounds().contains(mousePos)) {
			this->zin->setTexture(this->zin_walk_diagnol_right_down);
		}
	}
}

//Movement Functions
void Character::initAnimations()
{
	this->animation->addAnimation("WALKUP", zin_walk_up, 4, 16, 0.2, 0);
	this->animation->addAnimation("WALKDOWN", zin_walk_down, 4, 16, 0.2, 0);
	this->animation->addAnimation("WALKLEFT", zin_walk_left, 4, 16, 0.2, 0);
	this->animation->addAnimation("WALKRIGHT", zin_walk_right, 4, 16, 0.2, 0);
	this->animation->addAnimation("WALKLEFTDOWN", zin_walk_diagnol_left_down, 4, 16, 0.2, 0);
	this->animation->addAnimation("WALKRIGHTDOWN", zin_walk_diagnol_right_down, 4, 16, 0.2, 0);
	this->animation->addAnimation("WALKRIGHTUP", zin_walk_diagnol_right_up, 4, 16, 0.2, 0);
	this->animation->addAnimation("WALKLEFTUP", zin_walk_diagnol_left_up, 4, 16, 0.2, 0);

	this->animation->addAnimation("ROLLUP", zin_roll_up, 4, 16, 0.1, 0);
	this->animation->addAnimation("ROLLDOWN", zin_roll_down, 4, 16, 0.1, 0);
	this->animation->addAnimation("ROLLLEFT", zin_roll_left, 4, 16, 0.1, 0);
	this->animation->addAnimation("ROLLRIGHT", zin_roll_right, 4, 16, 0.1, 0);
}

void Character::characterMovement()
{
	this->walk();
	this->roll();
	this->sprint();
}

void Character::walk()
{
	//Animate Walking
	this->velocity.x = 0;
	this->velocity.y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->animation->play("WALKUP");
		velocity.y += movementSpeed;
		this->walking = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->animation->play("WALKDOWN");
		velocity.y += -movementSpeed;
		this->walking = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->animation->play("WALKLEFT");
		velocity.x += movementSpeed;
		this->walking = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->animation->play("WALKRIGHT");
		velocity.x += -movementSpeed;
		this->walking = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->animation->play("WALKLEFTDOWN");
		this->walking = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->animation->play("WALKRIGHTDOWN");
		this->walking = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->animation->play("WALKLEFTUP");
		this->walking = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->animation->play("WALKRIGHTUP");
		this->walking = true;
	}

	//Character stops moving
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->zin->setTextureRect(sf::IntRect(0, 0, 16, 16));
		this->walking = false;
	}	
}

void Character::roll()
{
	//Set rolling to true if able to roll time wise
	dodge_elapsed = dodge_timer.getElapsedTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && dodge_elapsed.asSeconds() >= this->dodgeTime && this->stamina >= 50) {
		movementSpeed += 5;
		this->stamina -= 49;
		dodge_timer.restart();
		this->rolling = true;
	}
	else if (dodge_elapsed.asSeconds() >= this->dodgeTime) {
		//Reset roll after stopping
		this->rolling = false;
		if (this->stamina <= this->staminaMax) { this->stamina++; }
		movementSpeed = 1.5;
		this->animation->reset("ROLLUP");
		this->animation->reset("ROLLDOWN");
		this->animation->reset("ROLLLEFT");
		this->animation->reset("ROLLRIGHT");
	}
	//Animate roll
	if (this->rolling) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->animation->play("ROLLUP");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->animation->play("ROLLDOWN");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->animation->play("ROLLLEFT");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->animation->play("ROLLRIGHT");
		}
	}
}

void Character::sprint()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && this->stamina > 0) {
		this->stamina--;
		this->movementSpeed += 2.5;
	}
	else if (this->stamina <= 0) {
		this->movementSpeed = 1.5f;
	}
}

//Asset Functions
void Character::loadAssets()
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

//Rectangle Functions
void Character::updateRects()
{
	for (auto& it : this->rectangles) {
		it.second->update(this->stamina);
	}
}

void Character::initRects()
{
	this->rectangles["STAMINABAR"] = new Rectangle(1700, 950, 100, 25, sf::Color::Black,
		sf::Color::White, 1.f, "", 16, false, this->stamina);
}

void Character::renderRects(sf::RenderTarget* target)
{
	for (auto& it : this->rectangles) {
		it.second->render(target);
	}
}