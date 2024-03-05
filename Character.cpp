#include "Character.h"
//Constructors and Destructors
Character::Character(sf::Sprite* sprite)
{
	this->zin = sprite;

	//Initialization
	this->loadAssets();
	this->combat = new CombatModule();
	this->animation = new AnimationModule(this->zin);
	this->initAnimations();
	
}

Character::~Character()
{
	delete this->animation;
	delete this->combat;
}

//Core Functions
void Character::updateCharacter(const sf::Vector2f mousePos)
{
	
	this->animateMovement();
	this->detectOctMousePosition(mousePos);
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

//Animation Functions
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
}

void Character::animateMovement()
{
	//Animate Walking
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		std::cout << "Here" << "\n";
		this->animation->play("WALKUP");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->animation->play("WALKDOWN");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->animation->play("WALKLEFT");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->animation->play("WALKRIGHT");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->animation->play("WALKLEFTDOWN");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->animation->play("WALKRIGHTDOWN");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->animation->play("WALKLEFTUP");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->animation->play("WALKRIGHTUP");
	}

	//Character stops moving
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->zin->setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
}

void Character::animateRoll()
{
	//Set rolling to true if able to roll time wise
	/*dodge_elapsed = dodge_timer.getElapsedTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && dodge_elapsed.asSeconds() >= 0.5 && this->player_walking) {
		dodge_timer.restart();
		//Reset Animation Frame
		this->animationFrame = 1;
		this->player_rolling = true;
	}*/

	//Animate the roll if rolling is true
	//Animate rolling
	/*if (last_key_w) {
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
	Animate roll cycle
	this->animateSheet(0.16, player_rolling, 16, 16, 4);*/
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