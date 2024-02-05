#pragma once
#include<SFML/Graphics.hpp>

class Rectangle
{
public:
	//Constructors and Destructors
	Rectangle(float x, float y, float width, float height, sf::Color color,
		sf::Color border_color, float z, bool hidden);
	~Rectangle();

	//Core Functions
	void render(sf::RenderTarget* target = nullptr);

	//Getters
	bool& getHidden() { return this->hidden; };

	//Setters
	bool& setHidden() { return this->hidden = true; };
	bool& setShown() { return this->hidden = false; };

private:
	bool hidden;
	sf::RectangleShape shape;
};