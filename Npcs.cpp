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
	this->initRects();
	this->addDialogue("INIT");
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
void Npcs::update(sf::FloatRect playerPos, sf::Vector2f playerVelocity)
{
	this->updateAnimations();
	this->moveNpcWithMap(playerVelocity);
	this->detectInteract(playerPos);
}

void Npcs::render(sf::RenderTarget* target)
{
	target->draw(this->npc);
	this->renderRects(target);
}

void Npcs::moveNpcWithMap(sf::Vector2f playerVelocity)
{
	this->npc.setPosition(x += playerVelocity.x, y += playerVelocity.y);
}

//Detection Functions
void Npcs::detectInteract(sf::FloatRect playerPos)
{
	if (this->npc.getGlobalBounds().intersects(playerPos)) {
		this->dialogueElapsed = this->dialogueTimer.getElapsedTime();
		this->rectangles["INTERACT_BOX"]->setShown();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && this->dialogueElapsed.asSeconds() >= 0.5) {
			this->rectangles["DIALOGUE"]->setShown();
			this->rectangles["INTERACT_BOX"]->setHidden();
			this->displayDialogue();
			this->dialogueTimer.restart();
		}
	}
	else {
		this->rectangles["DIALOGUE"]->setHidden();
		this->rectangles["INTERACT_BOX"]->setHidden();
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

//Rectangle Functions
void Npcs::updateRects()
{
	
}

void Npcs::initRects()
{
	this->rectangles["DIALOGUE"] = new Rectangle(x, y, 400, 100, sf::Color::Black, sf::Color::White, 1.f, "Test from init", 16.f, true);
	this->rectangles["INTERACT_BOX"] = new Rectangle(10, 10, 150.f, 25.f, sf::Color::Black, sf::Color::White, 1.f, "[E] INTERACT", 16.f, true);
}

void Npcs::renderRects(sf::RenderTarget* target)
{
	for (auto& it : this->rectangles) {
		it.second->render(target);
	}
}

//Dialogue Functions
void Npcs::addDialogue(std::string text)
{
	this->dialogue.push(text);
}

void Npcs::displayDialogue()
{
	if (!this->dialogue.empty()) {  // Check if the dialogue stack is not empty
		this->dialogue.pop();
		if (!this->dialogue.empty()) {  // Check again to ensure there's still content after popping
			this->rectangles["DIALOGUE"]->setString(this->dialogue.top());
		}
	}
}