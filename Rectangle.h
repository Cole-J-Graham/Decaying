#pragma once
#include<SFML/Graphics.hpp>

class Rectangle
{
public:
	//Constructors and Destructors
	Rectangle(float x, float y, float width, float height, sf::Color color,
		sf::Color border_color, float border_thickness, bool hidden);
	Rectangle(float x, float y, float width, float height, sf::Color color,
		sf::Color border_color, float border_thickness, std::string text, 
		float text_size, bool hidden);
	~Rectangle();

	//Core Functions
	void render(sf::RenderTarget* target = nullptr);

	//Getters
	bool& getHidden() { return this->hidden; };

	//Setters
	bool& setHidden() { return this->hidden = true; };
	bool& setShown() { return this->hidden = false; };

private:

	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;

	bool hidden;
	float text_size;
};