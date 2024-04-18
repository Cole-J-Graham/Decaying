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

Rectangle::Rectangle(float x, float y, float width, float height, sf::Color color,
	sf::Color border_color, float border_thickness, std::string text, float text_size,
	bool hidden, int status)
{
	this->width = width;
	this->height = height;
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(color);
	this->shape.setPosition(x, y);
	this->shape.setOutlineColor(border_color);
	this->shape.setOutlineThickness(border_thickness);
	this->fillShape.setSize(sf::Vector2f(width, height));
	this->fillShape.setPosition(x, y);
	this->fillShape.setFillColor(sf::Color::White);

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
		target->draw(this->fillShape);
		target->draw(this->text);
	}
}

void Rectangle::update(int& status)
{
	this->updateStatusBar(status);
}

//Modifiers
void Rectangle::setString(std::string input)
{
	this->text.setString(input);
}

void Rectangle::updateStatusBar(int& status)
{
	this->fillShape.setSize(sf::Vector2f(status, this->height));
}

void Rectangle::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
	this->text.setPosition(x, y);
}

void Rectangle::setSize(float width, float height)
{
	this->shape.setSize(sf::Vector2f(width, height));
}

void Rectangle::setOrientation(float x, float y, float width, float height)
{
	this->shape.setPosition(x, y);
	this->shape.setSize(sf::Vector2f(width, height));
	this->text.setPosition(x, y);
}