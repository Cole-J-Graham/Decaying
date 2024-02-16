#include "Rectangle.h"
//Constructors and Destructors
Rectangle::Rectangle(float x, float y, float width, float height, sf::Color color,
	sf::Color border_color, float border_thickness, bool hidden)
{
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(color);
	this->shape.setPosition(x, y);
	this->shape.setOutlineColor(border_color);
	this->shape.setOutlineThickness(border_thickness);

	this->hidden = hidden;
}

Rectangle::Rectangle(float x, float y, float width, float height, sf::Color color,
	sf::Color border_color, float border_thickness, std::string text,
	float text_size, bool hidden)
{
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(color);
	this->shape.setPosition(x, y);
	this->shape.setOutlineColor(border_color);
	this->shape.setOutlineThickness(border_thickness);

	this->font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(text_size);
	this->text.setPosition(x, y);

	this->hidden = hidden;
}

Rectangle::~Rectangle()
{

}

//Core Functions
void Rectangle::render(sf::RenderTarget* target)
{
	if (!this->hidden) {
		target->draw(this->shape);
		target->draw(this->text);
	}
}

//Modifiers
void Rectangle::setString(std::string input)
{
	this->text.setString(input);
}