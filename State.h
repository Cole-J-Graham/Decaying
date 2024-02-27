#ifndef STATE_H
#define STATE_H

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
#include<string>

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>

class State
{
public:
	//Constructors and Destructors
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	virtual void endState() = 0;
	virtual void updateMousePositions();

	//Pure Virtual Functions
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	//Getters
	sf::Vector2f getMousePosView() { return this->mousePosView; };

	sf::RenderWindow* window;
	std::stack<State*>* states;

private:
	std::vector<sf::Texture> textures;
	bool quit;

	//Mouse Position
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
};

#endif