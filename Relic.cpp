#include "Relic.h"
//Constructors and Destructors
Relic::Relic(float x, float y, std::string item_name, std::string item_description,
	std::string texture_input, float modifiers)
{
	this->item = new Item(x, y, item_name, item_description, texture_input, false, false, WEAPON, COMMON);
	this->item->setMapPosition(position);
	this->modifiers = modifiers;
}

Relic::~Relic()
{
	delete this->item;
}

//Core Functions

//Item Functions
void Relic::initRelic()
{

}

void Relic::render(sf::RenderTarget* target)
{
	this->item->render(target);
}

void Relic::moveItem(sf::Vector2f move)
{
	this->item->moveItem(move);
}

void Relic::update(const sf::Sprite sprite, const sf::Vector2f mousePos)
{
	this->item->update(sprite, mousePos);
}

void Relic::setMapPosition(sf::Vector2f position)
{
	item->setMapPosition(position);
}