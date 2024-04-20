#include"Game.h"
//Constructor and Destructors
Game::Game()
{
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::endApplication()
{
	std::cout << "Ending Application!" << "\n";
}

//Initialization (Private Functions)
void Game::initWindow()
{
	std::string title = "None";
	sf::VideoMode window_bounds(1920, 1080);
	bool vertical_sync_enabled = false;

	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	this->states.push(new GameState(window, &states));
	this->states.push(new DungeonState(window, &states));
}

//Update
void Game::update()
{
	//Update Events
	this->updateSFMLEvents();
	//Update the states while not empty
	if (!this->states.empty()) {
		this->states.top()->update(this->dt);
		//If getQuit is called in the top stack, delete the top of the stack and cleanup
		if (this->states.top()->getQuit()) {
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else {
		//Closes game because game is dependent on window being open
		this->endApplication();
		this->window->close();
	}
}

void Game::updateDt()
{
	/*Updates the dt variable with the time it takes to update and render one frame.*/

	this->dt = this->dtClock.restart().asMilliseconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent)) {
		if (this->sfEvent.type == sf::Event::Closed) {
			this->window->close();
		}
	}
}

//Render
void Game::render()
{
	this->window->clear();

	//Render Items
	if (!this->states.empty()) {
		this->states.top()->render(this->window);
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}