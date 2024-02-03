#pragma once
#include<SFML/Graphics.hpp>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
public:
	//Constructors and Destructors
	Button(float x, float y, float width, float height, sf::Font font,
		std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target = nullptr);

	//Accessors
	const bool isPressed() const;
	const bool isHovered() const;

	//Sfx Functions
	void initSounds();

private:
	//Core Booleans
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

};

