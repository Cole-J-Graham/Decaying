#include "TavernState.h"
//Constructors and Destructors
TavernState::TavernState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	//State
	this->window = window;

	//Core Variables
	this->location = 0;

	//Initialization
	this->initTileMaps();

	//Assets
	this->loadAssets();
	this->combat = new CombatComponent();
	this->initNpcs();
}

TavernState::~TavernState()
{
	delete this->combat;
	
	//Deconstruct TileMaps
	auto it = this->tile_maps.begin();
	for (it = this->tile_maps.begin(); it != this->tile_maps.end(); ++it) {
		delete it->second;
	}

	//Deconstruct Npcs
	auto in = this->npcs.begin();
	for (in = this->npcs.begin(); in != this->npcs.end(); ++in) {
		delete in->second;
	}
}

void TavernState::endState()
{

}

//Core Tavern Functions
void TavernState::enterDungeon()
{
	this->states->push(new DungeonState(this->window, this->states));
}

//State Functions
void TavernState::updateKeybinds(const float& dt)
{
	this->updateMousePositions();
	this->checkForQuit();
}

void TavernState::update(const float& dt)
{
	this->updateNpcs();
	this->combat->update(this->getMousePosView());
	this->updateKeybinds(dt);
	this->tile_maps["TAVERN"]->detectMap(this->combat->playerCombat->character, this->combat, this->combat->playerCombat->rectangles["PLAYERCOLLISION"]->getGlobalBounds());
	if (this->tile_maps["TAVERN"]->getCollidingEntrance()) { this->enterDungeon(); };
}

void TavernState::render(sf::RenderTarget* target)
{
	this->renderTileMaps(target);
	this->combat->render(target);
	this->renderNpcs(target);
}

//Npc Functions
void TavernState::updateNpcs()
{
	for (auto& it : this->npcs) {
		it.second->update(this->combat->playerCombat->character->player->getPosition(), this->combat->playerCombat->character->getVelocity());
	}
}

void TavernState::initNpcs()
{
	this->npcs["ZIN"] = new Npcs(900, 500, "Assets/SpriteSheets/ZinIdleAnimation.png");
}

void TavernState::renderNpcs(sf::RenderTarget* target)
{
	for (auto& it : this->npcs) {
		it.second->render(target);
	}
}

//TileMap Functions
void TavernState::initTileMaps()
{
	this->tile_maps["TAVERN"] = new TileMap(0.f, 0.f, 30, 30, 64.f, tavern_sheet, "Assets/SpriteData/dungeon.txt");
}

void TavernState::renderTileMaps(sf::RenderTarget* target)
{
	for (auto& it : this->tile_maps) {
		it.second->render(target);
	}
}

//Asset Functions
void TavernState::loadAssets()
{
	this->tavern_sheet.loadFromFile("Assets/SpriteSheets/TavernTileSheet.png");
}