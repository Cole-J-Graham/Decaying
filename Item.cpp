#include "Item.h"
//Constructors and Destructors
Item::Item(std::string item_name, std::string texture_input, bool hidden)
{
	this->item_state = ITM_UNTOUCHED;
    this->item_inv_state = ITM_IDLE;
    this->texture_input = texture_input;
    this->item.setScale(3.f, 3.f);
    this->item.setPosition(100, 100);
    this->hidden = hidden;

    this->loadAsset();
}

Item::~Item()
{

}

//Core Functions
void Item::render(sf::RenderTarget* target)
{
    if(!this->hidden)
    target->draw(this->item);
}

void Item::update(const sf::Vector2f player_pos)
{
    /*Update the booleans for the item state*/

    //Idle
    this->item_state = ITM_UNTOUCHED;
    if (this->item.getGlobalBounds().contains(player_pos)) {
        //Hover
        this->item_state = ITM_COLLIDING;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            //Pressed
            this->item_state = ITM_INTERACTED;
        }
    }

    switch (this->item_state) {
    case ITM_UNTOUCHED:
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

void Item::updateInventory(sf::Vector2f mousePos)
{
    /*Update the booleans for inventory item state */

    //Idle
    this->item_inv_state = ITM_IDLE;
    if (this->item.getGlobalBounds().contains(mousePos)) {
        //Hover
        this->item_inv_state = ITM_HOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //Pressed
            this->item_inv_state = ITM_ACTIVE;
        }
    }

    switch (this->item_inv_state) {
    case ITM_IDLE:
        std::cout << "Item Idle in inventory..." << "\n";
        break;
    case ITM_HOVER:
        std::cout << "Item Hovering in inventory..." << "\n";
        break;
    case ITM_ACTIVE:
        std::cout << "Item Active in inventory..." << "\n";
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

const bool Item::isPressed() const
{
    if (this->item_inv_state == ITM_ACTIVE)
        return true;

    return false;
}

const bool Item::isHovered() const
{
    if (this->item_inv_state == ITM_HOVER)
        return true;

    return false;
}

//Assets
void Item::loadAsset()
{
    this->item_texture.loadFromFile(texture_input);
    this->item.setTexture(item_texture);
}