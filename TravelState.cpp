#include "TravelState.h"
//Constructors and Destructors
TravelState::TravelState()
{
	//Core Variables
	this->gridSizeF = 64.f;
	this->col = 16;
	this->row = 16;

	//Assets
	zinWalkDown.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkSpriteSheet.png");
	zinWalkLeft.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkLeftSpriteSheet.png");
	zinWalkRight.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkRightSpriteSheet.png");
	zinWalkUp.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/zinWalkUpSpriteSheet.png");

	//Tilemap
	this->forestTile1.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/Sprite-0001.png");
	this->forestTile2.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/Sprite-0002.png");
	this->forestTile3.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/Sprite-0003.png");
	this->forestTile4.loadFromFile("C:/Users/Cole/source/repos/Decaying/Assets/SpriteSheets/Sprite-0004.png");

	//Animation Variables
	this->movementSpeed = 1.5f;
	this->animationFrame = -1;

	this->sheetX;
	this->sheetY;

	this->velocity.x = 0.f;
	this->velocity.y = 0.f;

	this->frame = 0;
	this->frameInit = false;

	this->setAssets();
}

TravelState::~TravelState()
{

}

void TravelState::endState()
{

}

//Core Travel Functions
void TravelState::loadingOnTile(std::vector<std::vector<sf::Sprite>>& inSprite, std::vector<std::vector<int>> tiles, sf::Texture& tex1, sf::Texture& tex2, sf::Texture& tex3, sf::Texture& tex4)
{
	//Draw a specific set texture tile based on which input is recieved from a tilemap vector
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			if (tiles[x][y] == 0) {
				inSprite[x][y].setTexture(tex1);
			}
			else if (tiles[x][y] == 1) {
				inSprite[x][y].setTexture(tex2);
			}
			else if (tiles[x][y] == 2) {
				inSprite[x][y].setTexture(tex3);
			}
			else if (tiles[x][y] == 3) {
				inSprite[x][y].setTexture(tex4);
			}
		}
	}
}

void TravelState::checkForMovement()
{
	//Animate walk cycle
	if (this->playerMoving) {
		this->animateTimer();
		switch (this->animationFrame) {
		case -1:
			sheetX = 0;
			sheetY = 0;
			break;
		case 0:
			sheetX = 16;
			sheetY = 0;
			break;
		case 1:
			sheetX = 32;
			sheetY = 0;
			break;
		case 2:
			sheetX = 48;
			sheetY = 0;
			break;
		}
	}
	//Set basic attributes for sprite
	zinPixelSprite.setScale(4.0f, 4.0f);
	zinPixelSprite.setTextureRect(sf::IntRect(sheetX, sheetY, 16, 16));
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;

	//Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		velocity.y += -movementSpeed;
		this->playerMoving = true;
		zinPixelSprite.setTexture(zinWalkUp);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y += movementSpeed;
		this->playerMoving = true;
		zinPixelSprite.setTexture(zinWalkDown);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x += -movementSpeed;
		this->playerMoving = true;
		zinPixelSprite.setTexture(zinWalkLeft);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocity.x += movementSpeed;
		this->playerMoving = true;
		zinPixelSprite.setTexture(zinWalkRight);
	}
	zinPixelSprite.move(velocity);

	//Character stops moving
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sheetX = 0;
		sheetY = 0;
		this->playerMoving = false;
	}
}

void TravelState::loadMap(sf::RenderWindow& window)
{
	//Create Level
	std::vector<std::vector<int>> level{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 3, 3, 0, 0, 0, 1},
		{1, 1, 1, 0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 0, 3, 1},
		{1, 1, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 1},
		{1, 0, 3, 3, 3, 0, 2, 0, 0, 0, 3, 3, 0, 3, 0, 1},
		{1, 0, 0, 3, 3, 0, 0, 0, 3, 3, 3, 3, 0, 3, 3, 1},
		{1, 0, 3, 2, 0, 3, 0, 3, 3, 3, 0, 0, 3, 0, 0, 1},
		{1, 0, 3, 0, 2, 0, 0, 3, 3, 0, 0, 3, 0, 3, 0, 1},
		{1, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 0, 3, 0, 0, 1},
		{1, 0, 0, 0, 3, 3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1},
		{1, 3, 0, 3, 3, 0, 3, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 3, 3, 1},
		{1, 1, 0, 0, 3, 3, 0, 3, 0, 0, 3, 0, 0, 0, 3, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 3, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	//Resize the 2d vector to rows and columns of a specific size
	tileMap.resize(row, std::vector<sf::Sprite>(col));
	//Set attributes for the 2d vector
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			tileMap[x][y].setScale(sf::Vector2f(0.4f, 0.4f));
			tileMap[x][y].setPosition(x * gridSizeF + 440, y * gridSizeF);
			loadingOnTile(tileMap, level, forestTile1, forestTile2, forestTile3, forestTile4);
		}
	}
	//Draw the 2d vector aka tilemap
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			window.draw(tileMap[x][y]);
		}
	}
}

void TravelState::loadCollisionMap(sf::RenderWindow& window)
{
	//Create Collisions
	std::vector<std::vector<int>> collisionData{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	//Resize the 2d vector to rows and columns of a specific size
	collisionMap.resize(row, std::vector<sf::RectangleShape>(col));
	//Set attributes for the 2d vector
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			collisionMap[x][y].setScale(sf::Vector2f(0.4f, 0.4f));
			collisionMap[x][y].setPosition(x * gridSizeF + 440, y * gridSizeF);
			//loadingOnTile(tileMap, level, forestTile1, forestTile2, forestTile3, forestTile4);
		}
	}
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			collisionMap[x][y].setSize(sf::Vector2f(160.f, 160.f));
			if (collisionData[x][y] == 0) {
				collisionMap[x][y].setFillColor(sf::Color::Transparent);
			}
			else if (collisionData[x][y] == 1) {
				collisionMap[x][y].setFillColor(sf::Color::Transparent);
			}
		}
	}
	for (int x = 0; x < collisionMap.size(); x++) {
		for (int y = 0; y < collisionMap.size(); y++) {
			if (zinPixelSprite.getGlobalBounds().intersects(collisionMap[x][y].getGlobalBounds())) {
				if (collisionData[x][y] == 1) {
					sf::FloatRect playerBounds = zinPixelSprite.getGlobalBounds();
					sf::FloatRect wallBounds = collisionMap[x][y].getGlobalBounds();

					sf::FloatRect area;
					if (zinPixelSprite.getGlobalBounds().intersects(collisionMap[x][y].getGlobalBounds(), area))
					{
						// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
						if (area.width > area.height)
						{
							if (area.contains({ area.left, zinPixelSprite.getPosition().y }))
							{
								// Up side crash
								zinPixelSprite.setPosition({ zinPixelSprite.getPosition().x, zinPixelSprite.getPosition().y + area.height });
							}
							else
							{
								// Down side crash
								zinPixelSprite.setPosition({ zinPixelSprite.getPosition().x, zinPixelSprite.getPosition().y - area.height });
							}
						}
						else if (area.width < area.height)
						{
							if (area.contains({ zinPixelSprite.getPosition().x + zinPixelSprite.getGlobalBounds().width - 1.f, area.top + 1.f }))
							{
								//Right side crash
								zinPixelSprite.setPosition({ zinPixelSprite.getPosition().x - area.width, zinPixelSprite.getPosition().y });
							}
							else
							{
								//Left side crash
								zinPixelSprite.setPosition({ zinPixelSprite.getPosition().x + area.width, zinPixelSprite.getPosition().y });
							}
						}
					}
				}
			}
		}
	}
	//Draw the 2d vector aka tilemap
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			window.draw(collisionMap[x][y]);
		}
	}
}

//State Functions
void TravelState::updateKeybinds(const float& dt)
{
	this->checkForMovement();
	this->checkForQuit();
}

void TravelState::update(const float& dt)
{
	this->updateKeybinds(dt);
}

void TravelState::render(sf::RenderTarget* target)
{
	target->draw(zinPixelSprite);
}

//Assets
void TravelState::setAssets()
{
	mapImage.loadFromFile("Assets/Wallpapers/Forest/forest1.jpeg");
	mapSprite.setTexture(mapImage);
}

void TravelState::animateTimer()
{
	elapsed = timer.getElapsedTime();
	if (elapsed.asSeconds() >= 0.2f) {
		if (this->animationFrame == -1) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 0) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 1) {
			this->animationFrame++;
			timer.restart();
		}
		else if (this->animationFrame == 2) {
			this->animationFrame = -1;
			timer.restart();
		}
	}
}

void TravelState::animateFourFrames(sf::Sprite& inSprite, int xOffset, float posX, float posY)
{
	inSprite.setTextureRect(sf::IntRect(sheetX, sheetY, xOffset, xOffset));
	inSprite.setPosition(posX, posY);
	this->animateTimer();
	switch (this->animationFrame) {
	case -1:
		sheetX = 0;
		sheetY = 0;
		break;
	case 0:
		sheetX = xOffset;
		sheetY = 0;
		break;
	case 1:
		sheetX = xOffset * 2;
		sheetY = 0;
		break;
	case 2:
		sheetX = xOffset * 3;
		sheetY = 0;
		break;
	}
}