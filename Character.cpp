#include "Character.h"
//Constructors and Destructors
Character::Character(sf::Sprite* sprite)
{
	//Initialization
	this->loadAssets();

	this->zin = sprite;
	this->animation = new AnimationModule(this->zin);
	this->combat = new CombatModule();
	std::cout << this->zin << "\n";
}

Character::~Character()
{
	delete this->animation;
	delete this->combat;
}

//Core Functions
void Character::updateCharacter(const sf::Vector2f mousePos)
{
	this->animation->animateMovement(zin_walk_up, zin_walk_down, zin_walk_left, zin_walk_right,
		zin_walk_diagnol_left_down, zin_walk_diagnol_right_down, zin_walk_diagnol_right_up,
		zin_walk_diagnol_left_up, zin_roll_up, zin_roll_down, zin_roll_left, zin_roll_right);
	this->detectOctMousePosition(mousePos);
}

//Detection Functions
void Character::detectOctMousePosition(const sf::Vector2f mousePos)
{
	std::cout << combat->getSheathed() << "\n";
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