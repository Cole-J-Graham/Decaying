#include "Weapon.h"
//Constructors and Destructors
Weapon::Weapon(float x, float y, std::string item_name, std::string item_description,
	std::string texture_input, float damage, float attack_speed)
{
	this->item = new Item(x, y, item_name, item_description, texture_input, false, false, WEAPON, COMMON);
	this->item->setMapPosition(position);
	this->damage = damage;
	this->attack_speed = attack_speed;
}

Weapon::~Weapon()
{
	delete this->item;
}

//Core Functions

//Item Functions
void Weapon::render(sf::RenderTarget* target)
{
	this->item->render(target);
}

void Weapon::moveItem(sf::Vector2f move)
{
	this->item->moveItem(move);
}

void Weapon::update(const sf::Sprite sprite, const sf::Vector2f mousePos)
{
	this->item->update(sprite, mousePos);
}

void Weapon::setMapPosition(sf::Vector2f position)
{
	item->setMapPosition(position);
}