#include "Npcs.h"
//Constructors and Deconstructors
Npcs::Npcs(float x, float y, std::string texture)
{
	this->textureInput = texture;
	this->npcTexture.loadFromFile(texture);
	this->npc.setTexture(this->npcTexture);
	this->x = x;
	this->y = y;
	this->npc.setPosition(this->x, this->y);
	this->npc.setScale(4.0f, 4.0f);

	//Initialization
	this->animation = new AnimationModule(&this->npc);
	this->initAnimations();
}

Npcs::~Npcs()
{
	delete this->animation;
	//Deconstruct Rectangles
	auto ir = this->rectangles.begin();
	for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
		delete ir->second;
	}
}

//Core Functions
void Npcs::update(sf::FloatRect playerPos)
{
	this->updateAnimations();
	//this->detectInteract(playerPos);
}

void Npcs::render(sf::RenderTarget* target)
{
	target->draw(this->npc);
	//this->renderRects(target);
}

//Detection Functions
void Npcs::detectInteract(sf::FloatRect playerPos)
{
	if (this->npc.getGlobalBounds().intersects(playerPos)) {
		std::cout << "Colliding" << "\n";
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			std::cout << "Interacted" << "\n";
			this->rectangles["DIALOGUE"]->setShown();
		}
	}
	else {
		this->rectangles["DIALOGUE"]->setHidden();
	}
}

//Animation Functions
void Npcs::updateAnimations()
{
	this->animation->play("IDLE");
}

void Npcs::initAnimations()
{
	this->animation->addAnimation("IDLE", this->npcTexture, 4, 32, 5.2, 32, 0.f);
}