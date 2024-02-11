#include "Item.h"
//Constructors and Destructors
Item::Item(float x, float y, std::string item_name, std::string item_description, 
    std::string texture_input, bool hidden, bool in_inventory)
{
	this->item_state = ITM_UNTOUCHED;
    this->item_inv_state = ITM_IDLE;
    this->x = x;
    this->y = y;
    this->texture_input = texture_input;
    this->item_name = item_name;
    this->item_description = item_description;
    this->item.setScale(3.f, 3.f);
    this->item.setPosition(x, y);
    this->hidden = hidden;

    this->loadAsset();
    this->initRects();
}

Item::~Item()
{
    //Deconstruct Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
}

//Core Functions
void Item::render(sf::RenderTarget* target)
{
    if (!this->hidden) {
        target->draw(this->item);
        this->renderRects(target);
    }
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
        this->rectangles["POP_BOX"]->setHidden();
        this->item.setColor(sf::Color(255, 255, 255, 255));
        break;
    case ITM_HOVER:
        this->rectangles["POP_BOX"]->setShown();
        this->item.setColor(sf::Color(255, 255, 255, 155));
        break;
    case ITM_ACTIVE:
        std::cout << "Item Active in inventory..." << "\n";
        break;
    default:
        break;
    }
}

//Modifiers
void Item::setPosition(float x, float y)
{
    this->item.setPosition(x, y);
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

//Rectangle Functions
void Item::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}

void Item::initRects()
{
    this->rectangles["POP_BOX"] = new Rectangle(this->x + 425, this->y, 250.f, 400.f, sf::Color::Black, sf::Color::White, 1.f, this->item_name + "\n\n" + this->item_description, 16.f, true);
}

//Assets
void Item::loadAsset()
{
    this->item_texture.loadFromFile(texture_input);
    this->item.setTexture(item_texture);
}