#pragma once
#include<SFML/Graphics.hpp>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
public:
	//Constructors and Destructors
	Button(float x, float y, float width, float height, sf::Font font,
		std::string text, sf::Color idleColor, sf::Color hoverColor, 
		sf::Color activeColor, bool hidden);
	~Button();

	//Core Functions
	void render(sf::RenderTarget* target = nullptr);
	void update(const sf::Vector2f mousePos);

	//Accessors
	const bool isPressed() const;
	const bool isHovered() const;

	//Getters
	bool& getHidden() { return this->hidden; };

	//Setters
	bool& setHidden() { return this->hidden = true; };
	bool& setShown() { return this->hidden = false; };

	//Sfx Functions
	void initSounds();

private:
	//Core Booleans
	short unsigned buttonState;
	bool hidden;

	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

};

