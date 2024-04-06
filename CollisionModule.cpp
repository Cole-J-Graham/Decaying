#include "CollisionModule.h"
//Constructors and Destructors
CollisionModule::CollisionModule()
{

}

CollisionModule::~CollisionModule()
{

}

//Core Functions
void CollisionModule::setMapCollision(sf::Sprite& character, std::vector<std::vector<sf::Sprite>>& map, 
	std::vector<std::vector<int>> mapdata, sf::FloatRect area, int col, int row)
{
	//Collision Function
	for (int x = 0; x < map.size(); x++) {
		for (int y = 0; y < map.size(); y++) {
			if (mapdata[x][y] == 0) {
				if (map[x][y].getGlobalBounds().intersects(character.getGlobalBounds(), area))
				{
					// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
					if (area.width > area.height)
					{
						if (area.contains({ area.left, map[x][y].getPosition().y }))
						{
							//Down side crash
							for (int x = 0; x < col; x++) {
								for (int y = 0; y < row; y++) {
									map[x][y].setPosition({ map[x][y].getPosition().x, map[x][y].getPosition().y + area.height });
								}
							}
						}
						else
						{
							//Up side crash
							for (int x = 0; x < col; x++) {
								for (int y = 0; y < row; y++) {
									map[x][y].setPosition({ map[x][y].getPosition().x, map[x][y].getPosition().y - area.height });
								}
							}
						}
					}
					else if (area.width < area.height)
					{
						if (area.contains({ map[x][y].getPosition().x + map[x][y].getGlobalBounds().width - 1.f, area.top + 1.f }))
						{
							//Left side crash
							for (int x = 0; x < col; x++) {
								for (int y = 0; y < row; y++) {
									map[x][y].setPosition({ map[x][y].getPosition().x - area.width, map[x][y].getPosition().y });
								}
							}
						}
						else
						{
							//Right side crash
							for (int x = 0; x < col; x++) {
								for (int y = 0; y < row; y++) {
									map[x][y].setPosition({ map[x][y].getPosition().x + area.width, map[x][y].getPosition().y });
								}
							}
						}
					}
				}
			}
		}
	}
}

void CollisionModule::addItemToMapCollision(int& x, int& y, Sprite& sprite)
{
	sprite.setPosition(x += mapPosition.x, y += mapPosition.y);
}