#include "Item.h"
//Constructors and Destructors
Item::Item()
{
	this->item_state = ITM_IDLE;

    this->loadAssets();
}

Item::~Item()
{

}

//Core Functions
void Item::render(sf::RenderTarget* target)
{
    target->draw(this->item);
}

void Item::update(const sf::Vector2f player_pos)
{
    /*Update the booleans for the item state*/

    //Idle
    this->item_state = ITM_IDLE;
    if (this->item.getGlobalBounds().contains(player_pos)) {
        //Hover
        this->item_state = ITM_COLLIDING;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            //Pressed
            this->item_state = ITM_INTERACTED;
        }
    }

    switch (this->item_state) {
    case ITM_IDLE:
        std::cout << "Item Idle..." << "\n";
        break;
    case ITM_COLLIDING:
        std::cout << "Item colliding..." << "\n";
        break;
    case ITM_INTERACTED:
        std::cout << "Item Interacted with" << "\n";
        break;
    default:
        break;
    }
}

//Accessors
const bool Item::isInteracted() const
{
    if (this->item_state == ITM_INTERACTED)
        return true;

    return false;
}

const bool Item::isColliding() const
{
    if (this->item_state == ITM_COLLIDING)
        return true;

    return false;
}

//Assets
void Item::loadAssets()
{

}