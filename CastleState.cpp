#include "CastleState.h"

CastleState::CastleState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->window = window;

	//Initialization
	this->initTileMaps();
}

CastleState::~CastleState()
{

}

//TileMap Functions
void CastleState::initTileMaps()
{
	this->tile_maps["CASTLE"] = new TileMap(0.f, 0.f, 30, 30, 64.f, castle_sheet, "Assets/SpriteData/castle.txt");
}

void CastleState::renderTileMaps(sf::RenderTarget* target)
{

}