#pragma once
#include<SFML/Graphics.hpp>

class Rectangle : sf::RectangleShape
{
public:
	//Constructors and Destructors
	Rectangle(float x, float y, float width, float height, sf::Color color,
		sf::Color border_color, float border_thickness, bool hidden);
	Rectangle(float x, float y, float width, float height, sf::Color color,
		sf::Color border_color, float border_thickness, std::string text, 
		float text_size, bool hidden);
	Rectangle(float x, float y, float width, float height, sf::Color color,
		sf::Color border_color, float border_thickness, std::string text,
		float text_size, bool hidden, int status);
	~Rectangle();

	//Core Functions
	void render(sf::RenderTarget* target = nullptr);
	void update(int& status);

	//Modifiers
	void setString(std::string input);
	void updateStatusBar(int& status);
	void setPosition(float x, float y);
	void setSize(float width, float height);
	void setOrientation(float x, float y, float width, float height);

	//Getters
	bool& getHidden() { return this->hidden; };

	//Setters
	bool& setHidden() { return this->hidden = true; };
	bool& setShown() { return this->hidden = false; };
	sf::FloatRect getGlobalBounds()& { return this->shape.getGlobalBounds(); };

private:

	sf::RectangleShape shape;
	sf::RectangleShape fillShape;
	sf::Text text;
	sf::Font font;

	float width;
	float height;
	bool hidden;
	float text_size;
};